#include "Input.h"
#include "Messages.h"
#include "ConsoleGL\Console.h"

#define cbutton (uchar)button

const unsigned cKeyCount = (uint) Keys::Count;
const unsigned cButtonCount = (uint) MouseButtons::Count;

Input *gInput = nullptr;

int y = 10;

Input::Input(IDispatcher *dispatcher)
	: dispatcher(dispatcher)
{
	Args::MustNotBeNull(dispatcher);
	memset(this->currKeyStates, 0, cKeyCount * sizeof(bool));
    memset(this->prevKeyStates, 0, cKeyCount * sizeof(bool));
    memset(this->currButtonStates, 0, cButtonCount * sizeof(bool));
    memset(this->prevButtonStates, 0, cButtonCount * sizeof(bool));
}

bool Input::IsKeyDown(Keys key)
{
	return this->currKeyStates[key];
}

bool Input::IsKeyUp(Keys key)
{
	return !this->currKeyStates[key];
}

bool Input::IsKeyTriggered(Keys key)
{
	return !this->currKeyStates[key] &&
		this->prevKeyStates[key];
}

bool Input::WasKeyDown(Keys key)
{
	return this->prevKeyStates[key];
}

bool Input::WasKeyUp(Keys key)
{
	return !this->prevKeyStates[key];
}

void Input::Update()
{
	// swap key state pointers
    //memcpy(this->prevKeyStates, this->currKeyStates, cKeyCount * sizeof(bool));
	//memset(this->currKeyStates, 0, cKeyCount * sizeof(bool));

    // swap button state pointers
    //memcpy(this->prevButtonStates, this->currButtonStates, cButtonCount * sizeof(bool));
    //memset(this->currButtonStates, 0, cButtonCount * sizeof(bool));

    y = 10;
}

void Input::HandleKey(Keys key, bool down)
{
    this->prevKeyStates[key] = this->currKeyStates[key];
	this->currKeyStates[key] = down;

    if (prevKeyStates[key] == currKeyStates[key])
    {
        return;
    }

	static KeyboardMessage msg;
	msg.Id = down ? MessageId::KeyDown : MessageId::KeyUp;
	msg.Key = key;
    msg.State = down ? KeyState::Down : KeyState::Up;
	this->dispatcher->Dispatch(&msg);

	// send the event again if triggered
	if (this->IsKeyTriggered(msg.Key))
	{
		msg.Id = MessageId::KeyTriggered;
		msg.State = KeyState::Triggered;
		this->dispatcher->Dispatch(&msg);
	}
}

bool Input::IsMouseButtonDown(MouseButtons button)
{
	return currButtonStates[cbutton];
}

bool Input::IsMouseButtonUp(MouseButtons button)
{
	return !currButtonStates[cbutton];
}

bool Input::IsMouseButtonTriggered(MouseButtons button)
{
	return !currButtonStates[cbutton] && 
		prevButtonStates[cbutton];
}

bool Input::WasMouseButtonDown(MouseButtons button)
{
	return prevButtonStates[cbutton];
}

bool Input::WasMouseButtonUp(MouseButtons button)
{
	return !prevButtonStates[cbutton];
}

Getter(Int2, Input::MousePosition)
{
	return mousePos;
}

void Input::MousePosition_set(const Int2 &value)
{
    if (mousePos != value)
    {
        mousePos = value;
        Int2 screenPos = gConsole->ToScreen(value);
        SetCursorPos(Split2(screenPos));
    }
}

Getter(bool, Input::ShowMouse)
{
    return showMouse;
}

Setter(bool, Input::ShowMouse)
{
    if (showMouse != value)
    {
        showMouse = value;
        ShowCursor((BOOL) value);
    }
}

void Input::HandleMouse(Int2, MouseButtons button, bool down, int delta)
{
    this->prevButtonStates[cbutton] = this->currButtonStates[cbutton];
	this->currButtonStates[cbutton] = down;

    POINT screenPos;
    GetCursorPos(&screenPos);

	auto prevPos = mousePos;
    mousePos = gConsole->ToConsole(Int2(screenPos.x, screenPos.y));

	MouseMessage msg;
	msg.Button = button;
	msg.MousePos = mousePos;
	msg.MouseDelta = mousePos - prevPos;
	msg.State = down ? ButtonState::Down : ButtonState::Up;
	msg.Delta = delta;
	
	if (button == MouseButtons::None)
	{
		msg.Id = MessageId::MouseMove;
        this->dispatcher->Dispatch(&msg);
	}
	else
	{
		msg.Id = down ? MessageId::MouseDown : MessageId::MouseUp;

        this->dispatcher->Dispatch(&msg);
        if (this->IsMouseButtonTriggered(button))
        {
            msg.Id = MessageId::MouseTriggered;
            msg.State = ButtonState::Triggered;
            this->dispatcher->Dispatch(&msg);
        }
	}
}
