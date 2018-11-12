#include "ConsoleEventHandler.h"
#include "Messages.h"
#include "Keys.h"
#include "IInput.h"

//#define KEYPADLO	0x47
//#define KEYPADHI	0x53
//
//#define PADKEYS 	(KEYPADHI - KEYPADLO + 1)
//#define iskeypad(x)	(KEYPADLO <= (x) && (x) <= KEYPADHI)

Keys::Type MapKey(KEY_EVENT_RECORD key)
{
	auto &&c = key.uChar.AsciiChar;

	// alphabet
	if (c >= 'A' && c <= 'F')
	{
		return Keys::Type(Keys::A + (c - 'A'));
	}

    if (c >= 'a' && c <= 'z')
    {
        return Keys::Type(Keys::A + (c - 'a'));
    }

	// numbers
	if (c >= '0' && c <= '9')
	{
		return Keys::Type((uchar)Keys::Zero + (c - '0'));
	}

	if (key.dwControlKeyState & LEFT_CTRL_PRESSED)
		return Keys::LeftControl;

	if (key.dwControlKeyState & LEFT_ALT_PRESSED)
		return Keys::LeftMenu;

	if (key.dwControlKeyState & RIGHT_CTRL_PRESSED)
		return Keys::RightContol;

	if (key.dwControlKeyState & RIGHT_ALT_PRESSED)
		return Keys::RightMenu;

	if (key.dwControlKeyState & SHIFT_PRESSED)
		return Keys::LeftShift;

	return (Keys::Type)c;
}

bool IsMouseButtonDown(MouseButtons button, uint buttonState)
{
    switch (button)
    {
    case MouseButtons::Left:
        return (buttonState & FROM_LEFT_1ST_BUTTON_PRESSED) != 0;
    case MouseButtons::Middle:
        return (buttonState & FROM_LEFT_2ND_BUTTON_PRESSED) != 0;
    case MouseButtons::Button4:
        return (buttonState & FROM_LEFT_3RD_BUTTON_PRESSED) != 0;
    case MouseButtons::Button5:
        return (buttonState & FROM_LEFT_4TH_BUTTON_PRESSED) != 0;
    case MouseButtons::Right:
        return (buttonState & RIGHTMOST_BUTTON_PRESSED) != 0;
    default:
        return false;
    }
}

ConsoleEventHandler::ConsoleEventHandler(IInput *inputHandler, IDispatcher *dispatcher)
	: inputHandler(inputHandler), dispatcher(dispatcher)
{
}

void ConsoleEventHandler::Handle(const INPUT_RECORD *record)
{
    switch (record->EventType)
    {
    case KEY_EVENT:
        {
		    auto key = MapKey(record->Event.KeyEvent);
		    inputHandler->HandleKey(key, record->Event.KeyEvent.bKeyDown != 0);
        }
        break;

    case MOUSE_EVENT:
        {
            auto mousePos = Int2(SPLIT2(record->Event.MouseEvent.dwMousePosition));
            auto buttons = record->Event.MouseEvent.dwButtonState;
            auto eventType = record->Event.MouseEvent.dwEventFlags;

            switch (eventType)
            {
            case 0:
                for (unsigned i = 0; i < (unsigned) MouseButtons::Count; ++i)
                {
                    MouseButtons button = (MouseButtons) i;
                    bool buttonIsDown = IsMouseButtonDown(button, buttons);
                    bool buttonWasDown = inputHandler->IsMouseButtonDown(button);

                    // Mouse down
                    if (!buttonWasDown && buttonIsDown)
                    {
                        inputHandler->HandleMouse(mousePos, button, true, 0);
                    }
                    // Mouse Up
                    else if (buttonWasDown && !buttonIsDown)
                    {
                        inputHandler->HandleMouse(mousePos, button, false, 0);
                    }
                }
                break;
            case MOUSE_MOVED:
                inputHandler->HandleMouse(mousePos, MouseButtons::None, false, 0);
                break;
            case DOUBLE_CLICK:
                //inputHandler->HandleMouse(mousePos, MouseButtons::None, false, 0);
                break;
            case MOUSE_WHEELED:
                //inputHandler->HandleMouse(mousePos, MouseButtons::None, false, 0);
                break;
            }
        }
        break;

    case WINDOW_BUFFER_SIZE_EVENT:
        Message message;
        message.Id = MessageId::WindowResized;
        dispatcher->Dispatch(&message);
        break;
    }
}