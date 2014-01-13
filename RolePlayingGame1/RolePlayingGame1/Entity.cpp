#include "Entity.h"

#include <random>

Entity::Entity(char* name, int currentHealth, char* weaponName, int maxAttackPower) :
	mName(name),
	mCurrentHealth(currentHealth),
	mWeaponName(weaponName),
	mMaxAttackPower(maxAttackPower)
{
}

char* Entity::getName()
{
	return mName;
}

void Entity::attack(Entity* enemy)
{
	int attackPower = rand() % (mMaxAttackPower + 1);
	printf("%s attacks %s with %s!\n", mName, enemy->getName(), mWeaponName);

	if (attackPower == 0)
	{
		printf("  It misses!\n\n");
	}
	else
	{
		enemy->giveDamage(attackPower);
	}
}

void Entity::giveDamage(int attackPower)
{
	mCurrentHealth -= attackPower;

	printf("  %s took %d damage and ", mName, attackPower);

	if (isAlive())
	{
		printf("has %d health left!\n\n", mCurrentHealth);
	}
	else
	{
		printf("was slain!\n\n");
	}
}

bool Entity::isAlive()
{
	return mCurrentHealth > 0;
}