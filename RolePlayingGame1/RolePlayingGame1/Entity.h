#pragma once

// represents a monster in the game or the player
class Entity
{
public:
	// constructs the Entity instance
	Entity(char* name, int startingHealth, char* weaponName, int maxAttackPower);

	// returns the Entity's name
	char* getName();

	// causes this Entity to attack an enemy Entity
	void attack(Entity* enemy);

	// damages this Entity
	void giveDamage(int attackPower);

	// returns true if the Entity is alive, false if not
	bool isAlive();

private:
	char* mName;         // the Entity's name
	int mCurrentHealth;  // how much health the Entity has
	char* mWeaponName;   // the name of the weapon the Entity will attack with
	int mMaxAttackPower; // how hard the Entity can hit in an attack
};
