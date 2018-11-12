#pragma once
#include "ConsoleGL\IEventHandler.h"

class IInput;
class IDispatcher;

class ConsoleEventHandler : public ConsoleGL::IEventHandler
{
public:
	ConsoleEventHandler(IInput *inputHandler, IDispatcher *dispatcher);
	void Handle(const INPUT_RECORD *message) override;

private:
	IInput *inputHandler;
    IDispatcher *dispatcher;
};
