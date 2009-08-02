/*
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2008 The swgANH Team

---------------------------------------------------------------------------------------
*/

#include "ChatMessageLib.h"
#include "Common/MessageDispatch.h"
#include "Common/MessageFactory.h"
#include "Common/Message.h"
#include "Common/DispatchClient.h"
#include "Common/atMacroString.h"
#include "GroupObject.h"
#include "CSROpcodes.h"



bool			ChatMessageLib::mInsFlag    = false;
ChatMessageLib*	ChatMessageLib::mSingleton  = NULL;

ChatMessageLib*	ChatMessageLib::Init(DispatchClient* client)
{
	if(!mInsFlag)
	{
		mSingleton = new ChatMessageLib(client);
		mInsFlag = true;
		
		return mSingleton;
	}
	else
		return mSingleton;
}
ChatMessageLib::ChatMessageLib(DispatchClient* client)
{
	mClient = client;
}

//======================================================================================================================

void ChatMessageLib::sendSceneCreateObjectByCrc(uint64 objectId, uint32 objectCrc, Player* player)
{
	Message*		message;

	gMessageFactory->StartMessage();
	gMessageFactory->addUint32(opSceneCreateObjectByCrc); 
	gMessageFactory->addUint64(objectId);
	gMessageFactory->addUint32(0);
	gMessageFactory->addUint32(0);
	gMessageFactory->addUint32(0);
	gMessageFactory->addUint32(1);
	gMessageFactory->addUint32(0);     
	gMessageFactory->addUint32(0);       
	gMessageFactory->addUint32(0);     
	gMessageFactory->addUint32(objectCrc);
	gMessageFactory->addUint8(0);     
	message = gMessageFactory->EndMessage();
	player->getClient()->SendChannelA(message, player->getClient()->getAccountId(), CR_Client, 5, false);	
}

//======================================================================================================================

void ChatMessageLib::sendSceneDestroyObject(uint64 objectId, Player* player)
{
	Message*		message;

	gMessageFactory->StartMessage();
	gMessageFactory->addUint32(opSceneDestroyObject); 
	gMessageFactory->addUint64(objectId);
	gMessageFactory->addUint8(0);
	message = gMessageFactory->EndMessage();

	player->getClient()->SendChannelA(message, player->getClient()->getAccountId(), CR_Client, 5, false);		
}
//======================================================================================================================

void ChatMessageLib::sendSceneEndBaselines(uint64 objectId, Player* player)
{
	Message*		message;

	gMessageFactory->StartMessage();
	gMessageFactory->addUint32(opSceneEndBaselines); 
	gMessageFactory->addUint64(objectId);   
	message = gMessageFactory->EndMessage();

	player->getClient()->SendChannelA(message, player->getClient()->getAccountId(), CR_Client, 5, false);	
}
//======================================================================================================================



////////////////////////////////////////////////////////////////////////////////////////////
//sends the zone the necessary information to create a waypoint for a friend
////////////////////////////////////////////////////////////////////////////////////////////
void ChatMessageLib::sendFindFriendCreateWaypoint(DispatchClient* client, Player* player, Player* friendPlayer)
{
	gMessageFactory->StartMessage();
	gMessageFactory->addUint32(opFindFriendCreateWaypoint);
	gMessageFactory->addUint64(player->getCharId());
	gMessageFactory->addString(friendPlayer->getName());
	gMessageFactory->addUint32(friendPlayer->getPlanetId());
	gMessageFactory->addFloat(friendPlayer->getPositionX());
	gMessageFactory->addFloat(friendPlayer->getPositionZ());
	Message* newMessage = gMessageFactory->EndMessage();
	//planetID+8 is the zones ID 
	client->SendChannelA(newMessage, client->getAccountId(),player->getPlanetId()+8, 6, false);

}

////////////////////////////////////////////////////////////////////////////////////////////
//requests the position of a char for a friend from the chatserver
////////////////////////////////////////////////////////////////////////////////////////////
void ChatMessageLib::sendFindFriendRequestPosition(DispatchClient* client, Player* playersFriend, Player* player)
{
	gMessageFactory->StartMessage();
	gMessageFactory->addUint32(opFindFriendRequestPosition);

	gMessageFactory->addUint64(playersFriend->getCharId());
	gMessageFactory->addUint64(player->getCharId());
	
	Message* newMessage = gMessageFactory->EndMessage();
	//planetID+8 is the zones ID 
	client->SendChannelA(newMessage, client->getAccountId(), playersFriend->getPlanetId()+8, 6, false);

}

//======================================================================================================================

