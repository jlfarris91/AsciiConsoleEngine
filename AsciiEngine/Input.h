#pragma once
#include "IInput.h"
#include "Math\Int2.h"

class IDispatcher;

class Input : public IInput
{
public:
	Input(IDispatcher *dispatcher);

    bool IsMouseButtonDown(MouseButtons button) override;
	bool IsMouseButtonUp(MouseButtons button) override;
	bool IsMouseButtonTriggered(MouseButtons button) override;
	bool WasMouseButtonDown(MouseButtons button) override;
	bool WasMouseButtonUp(MouseButtons button) override;
	void HandleMouse(Int2 pos, MouseButtons button, bool down, int delta = 0) override;

	bool IsKeyDown(Keys key) override;
	bool IsKeyUp(Keys key) override;
	bool IsKeyTriggered(Keys key) override;
	bool WasKeyDown(Keys key) override;
	bool WasKeyUp(Keys key) override;
	void HandleKey(Keys key, bool down) override;

    GetSet(bool, ShowMouse);

    Getter(Int2, MousePosition) override;
    void MousePosition_set(const Int2 &value) override;

	void Update();

private:
	
    bool prevButtonStates[(uint) MouseButtons::Count];
    bool currButtonStates[(uint) MouseButtons::Count];

    bool prevKeyStates[Keys::Count];
    bool currKeyStates[Keys::Count];

    bool showMouse = true;
	Int2 mousePos;
	IDispatcher *dispatcher;
};

extern Input *gInput;
