/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2012 kbegine Software Ltd
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
same license as the rest of the engine.
*/
#ifndef __ENTITY_MAILBOX_BASE_H__
#define __ENTITY_MAILBOX_BASE_H__
	
// common include	
#include "cstdkbe/cstdkbe.hpp"
//#include "network/channel.hpp"
#include "pyscript/scriptobject.hpp"
#include "entitydef/common.hpp"

//#define NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>	
#include <map>	
#include <vector>	
// windows include	
#if KBE_PLATFORM == PLATFORM_WIN32
#include <time.h> 
#else
// linux include
#include <errno.h>
#endif
	
namespace KBEngine{

namespace Mercury
{
class Channel;
}

class EntityMailboxAbstract : public script::ScriptObject
{
	/** 子类化 将一些py操作填充进派生类 */
	INSTANCE_SCRIPT_HREADER(EntityMailboxAbstract, ScriptObject)
public:
	EntityMailboxAbstract(PyTypeObject* scriptType, Mercury::Channel* pChannel, COMPONENT_ID componentID, 
	ENTITY_ID eid, uint16 utype, ENTITY_MAILBOX_TYPE type);
	virtual ~EntityMailboxAbstract();

	/** 获取entityID */
	ENTITY_ID getID()const{ return m_id_; }
	void setID(int id){ m_id_ = id; }
	static PyObject* pyGetID(PyObject *self, void *closure){ return PyLong_FromLong(static_cast<EntityMailboxAbstract*>(self)->getID()); }

	/** 获得组件ID */
	COMPONENT_ID getComponentID(void)const{ return m_componentID_; }

	/** 获得utype */
	uint16 getUType(void)const{ return m_utype_; }

	/** 获得type */
	ENTITY_MAILBOX_TYPE getType(void)const{ return m_type_; }
	
	/** 发送一个数据流到entity所在机器上 */
//	virtual SocketPacket* createStream(Opcodes code);
//	virtual SocketPacket* createMail(MAIL_TYPE mailType);
//	virtual void post(Packet* sp);

	/** 支持pickler 方法 */
	static PyObject* __reduce_ex__(PyObject* self, PyObject* protocol);
	
	/** 设置这个mailbox所关联的socket频道 在proxy进行giveClientTo操作时， 允许被设置为NULL*/
	void setChannel(Mercury::Channel* lpChannel){ m_channelPtr_ = lpChannel; };
	Mercury::Channel* getChannel(void)const{ return m_channelPtr_; }
protected:
	Mercury::Channel*						m_channelPtr_;			// 该mailbox所关联的远端机器通信通道
	COMPONENT_ID							m_componentID_;			// 远端机器组件的ID
	ENTITY_MAILBOX_TYPE						m_type_;				// 该mailbox的类型
	ENTITY_ID								m_id_;					// entityID
	uint16									m_utype_;				// entity的utype  按照entities.xml中的定义顺序
};

}
#endif
