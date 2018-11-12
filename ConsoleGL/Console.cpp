#include "Console.h"
#include "Math/Int2.h"
#include "Buffer.h"
#include <vector>
#include "IEventHandler.h"
#include <Windows.h>

ConsoleGL::Console *gConsole = nullptr;

namespace ConsoleGL
{

uint sFontWidth = 4;
uint sFontHeight = 6;
wchar_t *sFontName = L"Raster Fonts";

Console::Console(IEventHandler *eventHandler)
	: eventHandler(eventHandler)
{
	checkForChangesTimer = 0.0f;
	ResizedCallback = NULL;
    rawWindowSize = SMALL_RECT{ 0, 220, 0, 160 };
    charSize = Size(sFontWidth, sFontHeight);
}

Console::~Console()
{
	renderThread.join();
}

void Console::Initialize()
{
	SetConsoleTitle("Wildcard Search");
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    windowHandle = GetConsoleWindow();
    GetConsoleSizeInfo(&info, wHnd);
    prevInfo = info;
	writing = false;

    // Enable the window and mouse input events
    SetConsoleMode(rHnd, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

    backBuffer = &buffer1;
    frontBuffer = &buffer2;

	//renderThread = std::thread(&Console::Run);

	CheckForWindowChanges();
}

void Console::HandleWinEvents()
{
    if (!eventHandler)
    {
        return;
    }

    DWORD numRead = 0, i = 0;

    // Get the number of console events
    GetNumberOfConsoleInputEvents(rHnd, &numRead);
    
    if (numRead == 0)
    {
        return;
    }

    //if (ReadConsoleInput(rHnd, inputRecords, 128, &numRead))
    if (PeekConsoleInput(rHnd, inputRecords, 128, &numRead))
    {
        for (; i < numRead; ++i)
        {
            eventHandler->Handle(&inputRecords[i]);
        }
        FlushConsoleInputBuffer(rHnd);
    }
}

void Console::SetPalette(Palette palette)
{
    SetConsolePalette(palette, sFontWidth, sFontHeight, sFontName);
}

void Console::Resize(Size newSize)
{
    bufferSize = Size(newSize.x, newSize.y);
    area = bufferSize.x * bufferSize.y;

    SetConsoleWindowInfo(wHnd, TRUE, &rawWindowSize);
    SetConsoleScreenBufferSize(wHnd, ToCoord(bufferSize));
    //ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);
}

void Console::WriteBuffer(const Buffer *buffer)
{
	if (buffer == nullptr || buffer->data == nullptr)
		return;

    COORD charPos = { 0, 0 };
    SMALL_RECT consoleWriteArea = { 0, 0, (SHORT)bufferSize.x - 1, (SHORT)bufferSize.y - 1 };

    auto result = WriteConsoleOutputA(wHnd, buffer->data, ToCoord(bufferSize), charPos, &consoleWriteArea);
    if (result == 0)
    {
        HandleLastError();
    }
}

Int2 Console::ToConsole(Int2 point)
{
    point.x -= (int)windowRect.left;
    point.y -= (int)windowRect.top;
    return point / charSize;
}

Int2 Console::ToScreen(Int2 point)
{
    point *= charSize;
    point.x += (int)windowRect.left;
    point.y += (int)windowRect.top;
    return point;
}

void Console::CheckForWindowChanges()
{
    prevInfo = info;
    GetConsoleSizeInfo(&info, wHnd);

    if (info.WindowSize.X != prevInfo.WindowSize.X ||
        info.WindowSize.Y != prevInfo.WindowSize.Y ||
        info.ScreenBufferSize.X != prevInfo.ScreenBufferSize.X ||
        info.ScreenBufferSize.Y != prevInfo.ScreenBufferSize.Y)
    {
        RECT currentRect;
        GetWindowRect(windowHandle, &currentRect);

        windowRect.left = (SHORT) currentRect.left;
        windowRect.right = (SHORT) currentRect.right;

        // flip bottom and top
        windowRect.top = (SHORT) currentRect.bottom;
        windowRect.bottom = (SHORT) currentRect.top;

        Resize(ToSize(info.WindowSize));
        if (ResizedCallback)
        {
            ResizedCallback();
        }
    }
}

void Console::FillBuffer(Buffer *buffer)
{
    if (backBuffer->width != buffer->width || backBuffer->height != buffer->height)
    {
        backBuffer->Resize(buffer->width, buffer->height);
    }
    size_t size = sizeof(CharInfo) * buffer->width*buffer->height;
    memcpy(backBuffer->data, buffer->data, size);
}

void Console::SwapBuffers()
{
	swapBuffers = true;
}

void Console::Update()
{
	checkForChangesTimer += 0.0167f;
	if (checkForChangesTimer > 0.05f)
	{
		CheckForWindowChanges();
		checkForChangesTimer = 0.0f;
	}

    HandleWinEvents();
}

Getter(Rect, Console::WindowRect)
{
    return windowRect;
}

Getter(Size, Console::BufferSize)
{
    return bufferSize;
}

Getter(Size, Console::CharSize)
{
    return charSize;
}

void Console::Run()
{
	//while (true)
	//{
		gConsole->writing = true;
		if (gConsole->swapBuffers)
		{
			gConsole->swapBuffers = false;
			swap(gConsole->frontBuffer, gConsole->backBuffer);
		}		
		gConsole->WriteBuffer(gConsole->frontBuffer);
		gConsole->writing = false;
		//Sleep(100);
	//}
}

}