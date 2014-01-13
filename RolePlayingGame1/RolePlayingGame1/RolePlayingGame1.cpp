#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

#include "Entity.h"
#include "Room.h"

// determine where the player wants to go next
Room* getNextRoom(Room* currentRoom);

// fight an enemy
void combat(Entity* player, Entity* enemy);

int main()
{
	srand(time(NULL));

	// set up the maze...
	//
	//          -----
	//          | 3 |
	//          -----
	//            |
    //   -----  -----
    //   | 1 |--| 2 |
	//   -----  -----
	//            |
	//   -----  -----  -----  -----
	//   | 5 |--| 4 |--| 6 |--| 7 |
	//   -----  -----  -----  -----
	
	// create the rooms
	Room room1("You are in a dank, dark room.", false);
	Room room2("This room smells of salt. Lots and lots of salt.", false);
	Room room3("The ceiling in this room is dripping something slimy.", false);
	Room room4("This room smells like fresh baked poppyseed muffins.", false);
	Room room5("You are in a room with an uncomfortably low ceiling.", false);
	Room room6("This room gives you a bad feeling.", false);
	Room room7("You've found the exit!\n\nThere is a pot of gold and a stack of fresh sandwiches here!", true);

	// connect the rooms by creating exits
	room1.setExit(EAST, &room2);
	
	room2.setExit(NORTH, &room3);
	room2.setExit(SOUTH, &room4);
	room2.setExit(WEST, &room1);

	room3.setExit(SOUTH, &room2);

	room4.setExit(NORTH, &room2);
	room4.setExit(WEST, &room5);
	room4.setExit(EAST, &room6);

	room5.setExit(EAST, &room4);

	room6.setExit(WEST, &room4);
	room6.setExit(EAST, &room7);

	// add some monsters
	Entity orc("An Ugly Orc", 10, "a huge wooden club", 5);
	room3.setMonster(&orc);

	Entity troll("A Hideous Troll", 10, "a small, sharp axe", 3);
	room4.setMonster(&troll);

	Entity dragon("An Enormous, Fire-Breathing Dragon", 20, "Flamin' Hot Cheeto Breath", 10);
	room6.setMonster(&dragon);

	// introduce the maze...
	printf("Welcome to the maze...\n\n");
	printf("Please enter your name, IF YOU DARE: ");

	char playerName[80];

	scanf("%80s", &playerName);
	flushall();

	printf("\nHello, %s. Good luck...\n", playerName);

	// create the player entity
	Entity player(playerName, 50, "a golden sword", 10);

	// start the game loop
	bool gameOver = false;

	Room* currentRoom = &room1;

	while (!gameOver)
	{
		// show the player the room they are in
		printf("\n%s\n\n", currentRoom->getDescription());

		// if there is a living monster here the player must fight it
		if (currentRoom->hasMonster())
		{
			if (currentRoom->getMonster()->isAlive())
			{
				combat(&player, currentRoom->getMonster());
			}
			else
			{
				printf("You see the corpse of %s here.\n\n", currentRoom->getMonster()->getName());
			}
		}

		// if we're alive and not in the final room, figure out where to go next
		if (player.isAlive() && !currentRoom->isFinalRoom())
		{
			currentRoom = getNextRoom(currentRoom);
		}
		else
		{
			gameOver = true;
		}
	}

	printf("\n\n**** GAME OVER ****\n\n\n\nThanks for playing!\n\nPress any key to exit...\n");

	getch();
	return 0;
}

Room* getNextRoom(Room* currentRoom)
{
	Room* nextRoom = NULL;

	while (nextRoom == NULL)
	{
		printf("You see exits:\n");

		if (currentRoom->hasExit(NORTH)) printf("  N) North\n");
		if (currentRoom->hasExit(SOUTH)) printf("  S) South\n");
		if (currentRoom->hasExit(EAST))  printf("  E) East\n");
		if (currentRoom->hasExit(WEST))  printf("  W) West\n");

		printf("\nWhich way? ");

		char choice;
		scanf("%c", &choice);
		flushall();

		if (toupper(choice) == 'N' && currentRoom->hasExit(NORTH)) nextRoom = currentRoom->getExit(NORTH);
		if (toupper(choice) == 'S' && currentRoom->hasExit(SOUTH)) nextRoom = currentRoom->getExit(SOUTH);
		if (toupper(choice) == 'E' && currentRoom->hasExit(EAST))  nextRoom = currentRoom->getExit(EAST);
		if (toupper(choice) == 'W' && currentRoom->hasExit(WEST))  nextRoom = currentRoom->getExit(WEST);

		if (nextRoom == NULL) printf("There is no exit that way.\n");
	}

	return nextRoom;
}

void combat(Entity* player, Entity* enemy)
{
	printf("There is %s here! You must fight it!\n\n", enemy->getName());

	// this is a fight to the death
	while (player->isAlive() && enemy->isAlive())
	{
		printf("Press any key to attack!\n\n");
		getch();

		// the player gets to attack first
		player->attack(enemy);

		// if the enemy is still living, it gets to attack
		if (enemy->isAlive())
		{
			enemy->attack(player);
		}
	}
}