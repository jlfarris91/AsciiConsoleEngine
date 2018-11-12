#pragma once
#include "Messages.h"
#include "Time.h"
#include "Keys.h"
#include "Math/Int2.h"
#include "MouseButtons.h"

/// Dispatches an event after an amount of time.
template <typename T>
void Dispatcher::DispatchAfter(const T &message, float seconds)
{
	DelayData data;
	i_move(data.Data, message);
	float time = Time::elapsedTime + seconds;
	delayedDispatchMap[time].push(data);
}

/// Broadcasts an event after an amount of time.
template <typename T>
void Dispatcher::BroadcastAfter(const T &message, float seconds)
{
	DelayData data;
	i_move(data.Data, message);
	float time = Time::elapsedTime + seconds;
	delayedBroadcastMap[time].push(data);
}

/// Moves an event object into the given buffer. 
template <typename T>
size_t Dispatcher::i_move(MessageDataBuffer &buff, const T &event)
{
	size_t offset = buff.allocate(sizeof(T));
	T* pointer = reinterpret_cast<T*>(buff[offset]);
	new (pointer) T(event);
	return offset;
}

/// Queues a message to be dispatched at the beginning of the next frame.
template <typename T>
void Dispatcher::Queue(const T &message)
{
	DelayData data;
	i_move(data.Data, message);
	queue.push(data);
}

/// Registers a handler function with the dispatcher.
template <typename Class>
void Dispatcher::Register(MessageId id, void(Class::*func)(Message *), Class *object)
{
	using std::placeholders::_1;
	auto &&handler = std::bind(func, object, _1);
	handlerMap[id].push_back(handler);
}

/// Unregisters a handler function with the dispatcher.
template <typename Class>
void Dispatcher::Unregister(MessageId id, void(Class::*func)(Message *), Class *object)
{
	//using std::placeholders::_1;
	//auto &&handler = std::bind(func, object, _1);
	//handlerMap[id].remove(handler);
}

struct KeyboardMessage : Message
{
	Keys::Type Key = Keys::None;
	KeyState::Type State = KeyState::Up;
};

struct MouseMessage : Message
{
	Int2 MousePos = Int2::cZero;
	Int2 MouseDelta = Int2::cZero;
	int Delta = 0;
	MouseButtons Button = MouseButtons::Left;
	ButtonState State = ButtonState::Up;
};