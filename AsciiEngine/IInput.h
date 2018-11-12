#pragma once
#include "Keys.h"
#include "Math/Int2.h"
#include "MouseButtons.h"

class IInput
{
public:
    virtual ~IInput() = default;

    virtual bool IsMouseButtonDown(MouseButtons button) = 0;
	virtual bool IsMouseButtonUp(MouseButtons button) = 0;
	virtual bool IsMouseButtonTriggered(MouseButtons button) = 0;
	virtual bool WasMouseButtonDown(MouseButtons button) = 0;
	virtual bool WasMouseButtonUp(MouseButtons button) = 0;
	virtual void HandleMouse(Int2 pos, MouseButtons button, bool down, int delta) = 0;

	virtual bool IsKeyDown(Keys key) = 0;
	virtual bool IsKeyUp(Keys key) = 0;
	virtual bool IsKeyTriggered(Keys key) = 0;
	virtual bool WasKeyDown(Keys key) = 0;
	virtual bool WasKeyUp(Keys key) = 0;
	virtual void HandleKey(Keys key, bool down) = 0;

    IGetter(bool, ShowMouse);
    ISetter(bool, ShowMouse);
    PropertyRW(bool, ShowMouse);

    IGetter(Int2, MousePosition);
    virtual void MousePosition_set(const Int2 &value) = 0;
    PropertyRW(Int2, MousePosition);
};