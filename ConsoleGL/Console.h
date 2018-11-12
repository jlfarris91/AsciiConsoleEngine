#pragma once
#include "palette.h"
#include "Math/Int2.h"
#include <thread>
#include "Buffer.h"
#include "Math/Rect.h"

typedef COLORREF Palette[16];

namespace ConsoleGL
{

class Buffer;
class IEventHandler;

class Console
{
public:
    Console(IEventHandler *eventHandler = nullptr);
    ~Console();

    void Initialize();
    void SetPalette(Palette palette);
    void Resize(Size newSize);
    void WriteBuffer(const Buffer *buffer);
    void FillBuffer(Buffer *buffer);
    void SwapBuffers();

    Int2 ToConsole(Int2 point);
    Int2 ToScreen(Int2 point);

    void Update();

    void(*ResizedCallback)();

    Getter(Rect, WindowRect);
    PropertyR(Rect, WindowRect);

    Getter(Size, BufferSize);
    PropertyR(Size, BufferSize);

    Getter(Size, CharSize);
    PropertyR(Size, CharSize);

    void Run();
private:
    void HandleWinEvents();

    float checkForChangesTimer;
    void CheckForWindowChanges();

    CONSOLE_INFO info;
    CONSOLE_INFO prevInfo;
    HANDLE wHnd, rHnd;
    HWND windowHandle;
    SMALL_RECT rawWindowSize;
    uint area;

    Rect windowRect;
    Size bufferSize;
    Size charSize;

    Buffer buffer1, buffer2;
    Buffer *frontBuffer, *backBuffer;

    bool writing;

    IEventHandler *eventHandler;
    INPUT_RECORD inputRecords[128];
    std::thread renderThread;
    bool swapBuffers = false;
};

}

extern ConsoleGL::Console *gConsole;