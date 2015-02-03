/************************************************************************/
/*                                                                      */
/************************************************************************/


#ifndef __EVENT_MGR_H__
#define __EVENT_MGR_H__

#include "EventMsg.h"
#include "EventMsg_Test.h"
//////////////////////////////////////////////////////////////////////////
// ����ĳ�Ա����ֻ�������̵߳��ã�AddEvent���⣩

#define VIRTULE_HANDLE(MSGIMPL)\
	virtual void HandleMessage(MSGIMPL& rMsg) {}

class EventMgr
{
public:
	EventMgr();
	virtual ~EventMgr();
public:
	bool Init();
	void Update();		
	void AddEvent(GUID_t sender, EventMsgPtr Ptr);
	virtual void HandleMessage(EventMsg& rMsg);
private:
	TSList<EventMsgPtr>				m_listEventMsg;	
public:
	VIRTULE_HANDLE(JoinWolrd);
};

#endif // __EVENT_MGR_H__