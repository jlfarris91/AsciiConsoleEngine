#pragma once
#include <functional>
#include <vector>
#include <queue>
#include <unordered_map>
#include "IDispatcher.h"

typedef std::vector<size_t> MessageQueue;

enum class MessageId : unsigned
{
	Unspecified = 0,
	WindowResized,
	KeyDown,
	KeyUp,
	KeyTriggered,
	MouseDown,
	MouseUp,
	MouseTriggered,
	MouseMove,
};

//----------------------------------------------------------------- IMessage
struct Message
{
	MessageId Id = MessageId::Unspecified;
	bool Handled = false;
};

typedef void(ReceiveFuncT)(Message *);
typedef std::function<ReceiveFuncT> MessageHandler;
typedef std::vector<MessageHandler> MessageHandlerList;
typedef std::unordered_map<MessageId, MessageHandlerList> MessageHandlerMap;

//------------------------------------------------------ Message Data Buffer
struct MessageDataBuffer
{
public:
	size_t allocate(size_t size);
	void *operator[](size_t offset);
	const void *operator[](size_t offset) const;
	void clear();
private:
	std::vector<byte> _buff;
};

//------------------------------------------------------- Message Dispatcher
class Dispatcher : public IDispatcher
{
public:
	/// Dispatches a message to a specific space
	void Dispatch(Message *message);

	/// Dispatches an event after an amount of time.
	template <typename T>
	void DispatchAfter(const T &message, float seconds);

	/// Broadcasts a message to all spaces. Deferred.
	void Broadcast(Message *message);

	/// Broadcasts an event after an amount of time.
	template <typename T>
	void BroadcastAfter(const T &message, float seconds);

	/// Queues a message to be dispatched at the beginning of the next frame.
	template <typename T>
	void Queue(const T &message);

	/// Registers a handler function with the dispatcher.
	void Register(MessageId id, ReceiveFuncT func);

	/// Registers a handler function with the dispatcher.
	template <typename Class>
	void Register(MessageId id, void(Class::*func)(Message *), Class *object);

	/// Registers a handler function with the dispatcher.
	void Unregister(MessageId id, ReceiveFuncT);

	/// Unregisters a handler function with the dispatcher.
	template <typename Class>
	void Unregister(MessageId id, void(Class::*func)(Message *), Class *object);

	/// Update the EventDispatcher flipping the event queues.
	void Update();

private:
	struct DelayData
	{
		MessageDataBuffer Data;
	};

	typedef std::queue<DelayData> DelayDataList;
	typedef std::unordered_map<float, DelayDataList> DelayedEventMap;

	DelayDataList queue;
	DelayedEventMap delayedDispatchMap;
	DelayedEventMap delayedBroadcastMap;
	MessageHandlerMap handlerMap;

	void i_dispatch(Message *message, MessageId id);
	void i_broadcast(Message *message);
	void i_sendDelayed(DelayedEventMap &delayed, bool broadcast);

	/// Moves an event object into the given buffer. 
	template <typename T>
	static size_t i_move(MessageDataBuffer &buff, const T &message);
};

extern Dispatcher *gDispatcher;

#include "Messages.inl"