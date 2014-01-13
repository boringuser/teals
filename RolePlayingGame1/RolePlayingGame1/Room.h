#pragma once

#include "Entity.h"

enum Direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

// represents a room in the game
class Room
{
public:
	// constructs the room instance
	Room(char* description, bool isFinalRoom);

	// gets a description for the room
	char* getDescription();

	// gets the next room in a particular direction, or NULL if there is no exit that way
	Room* getExit(Direction direction);	

	// creates an exit in this room leading to another room
	void setExit(Direction direction, Room* room);

	// returns true if there is an exit in the specified direction
	bool hasExit(Direction direction);

	// puts a monster in this room
	void setMonster(Entity* monster);

	// returns the monster in this room, or NULL if there isn't one here
	Entity* getMonster();

	// returns true if there is a monster in the room
	bool hasMonster();

	// returns true if this is the final room in the game
	bool isFinalRoom();

private:
	char* mDescription; // a description for the room
	Room* mNorthRoom;   // what lies to the north
	Room* mSouthRoom;   // what lies to the south
	Room* mEastRoom;    // what lies to the east
	Room* mWestRoom;    // what lies to the west
	Entity* mMonster;   // the monster in the room, if there is one
	bool mIsFinalRoom;  // true if this is the last room in the game
};