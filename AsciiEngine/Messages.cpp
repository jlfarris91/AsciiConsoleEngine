#include "Messages.h"
#include "Time.h"

extern Dispatcher *gDispatcher = new Dispatcher();

//------------------------------------------------------ Message Data Buffer
//**************************************************************************
size_t MessageDataBuffer::allocate(size_t size)
{
	size_t index = _buff.size();
	_buff.resize(index + size);
	return index;
}

//**************************************************************************
void *MessageDataBuffer::operator[](size_t offset)
{
	return &_buff[offset];
}

//**************************************************************************
const void *MessageDataBuffer::operator[](size_t offset) const
{
	return &_buff[offset];
}

//**************************************************************************
void MessageDataBuffer::clear()
{
	_buff.clear();
}

//------------------------------------------------------- Message Dispatcher
//**************************************************************************
void Dispatcher::Update()
{
	// dispatch queued events
	while (!queue.empty())
	{
		auto &&data = queue.front();
		auto &&message = (Message*)data.Data[0];
		Dispatch(message);
		queue.pop();
	}

	// send delayed
	i_sendDelayed(delayedDispatchMap, false);
	i_sendDelayed(delayedBroadcastMap, true);
}

//**************************************************************************
void Dispatcher::Dispatch(Message *message)
{
	i_dispatch(message, message->Id);
}

//**************************************************************************
void Dispatcher::Broadcast(Message *message)
{
	i_broadcast(message);
}

//**************************************************************************
void Dispatcher::Register(MessageId id, ReceiveFuncT func)
{
	using std::placeholders::_1;
	auto &&handler = func;
	handlerMap[id].push_back(handler);
}

//**************************************************************************
void Dispatcher::Unregister(MessageId id, ReceiveFuncT func)
{
	//using std::placeholders::_1;
	//auto &&handler = MessageHandler(func);
	//handlerMap[id].erase(handler);
}

//**************************************************************************
void Dispatcher::i_dispatch(Message *message, MessageId id)
{
	auto &&handlerList = handlerMap.find(id);
	if (handlerList != handlerMap.end())
	{
		for (auto &&handler : handlerList->second)
		{
			handler(message);
		}
	}
}

//**************************************************************************
void Dispatcher::i_broadcast(Message *message)
{
	// dispatch to all spaces
	//for (auto &&handlerPair : handlerMap)
	//{
	//	i_dispatch(message, handlerPair.first);
	//}
}

//**************************************************************************
void Dispatcher::i_sendDelayed(DelayedEventMap &delayed, bool broadcast)
{
	typedef void(*FuncT)(Dispatcher *dispatcher, DelayData &data);

	static const FuncT dispatchFn = [](Dispatcher *dispatcher, DelayData &data) {
		Message *message = (Message*)data.Data[0];
		dispatcher->Dispatch(message);
	};
	static const FuncT broadcastFn = [](Dispatcher *dispatcher, DelayData &data) {
		Message *message = (Message*)data.Data[0];
		dispatcher->Broadcast(message);
	};

	FuncT fn = (broadcast) ? broadcastFn : dispatchFn;

	DelayedEventMap temp = delayed;
	for (auto &&pair : temp)
	{
		// if the time has elapsed
		if (pair.first <= Time::elapsedTime)
		{
			auto &&queue = pair.second;
			// send each event in the queue
			while (!queue.empty())
			{
				auto &&data = queue.front();
				queue.pop();
				fn(this, data);
			}
		}
	}
}