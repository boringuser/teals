#include "Room.h"

#include <stdlib.h>

Room::Room(char* description, bool isFinalRoom) :
	mDescription(description),
	mIsFinalRoom(isFinalRoom),
	mNorthRoom(NULL),
	mSouthRoom(NULL),
	mEastRoom(NULL),
	mWestRoom(NULL),
	mMonster(NULL)
{
}

char* Room::getDescription()
{
	return mDescription;
}

Room* Room::getExit(Direction direction)
{
	switch (direction)
	{
	case NORTH:
		return mNorthRoom;
	case SOUTH:
		return mSouthRoom;
	case EAST:
		return mEastRoom;
	case WEST:
		return mWestRoom;
	}
}

void Room::setExit(Direction direction, Room* room)
{
	switch (direction)
	{
	case NORTH:
		mNorthRoom = room;
		break;
	case SOUTH:
		mSouthRoom = room;
		break;
	case EAST:
		mEastRoom = room;
		break;
	case WEST:
		mWestRoom = room;
		break;
	}
}

bool Room::hasExit(Direction direction)
{
	return getExit(direction) != NULL;
}

void Room::setMonster(Entity* monster)
{
	mMonster = monster;
}

Entity* Room::getMonster()
{
	return mMonster;
}

bool Room::hasMonster()
{
	return mMonster != NULL;
}

bool Room::isFinalRoom()
{
	return mIsFinalRoom;
}
