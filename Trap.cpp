#include "Trap.h"
#include "Archeologist.h"

Trap::Trap()
{
	claimed = false;
	size = 1;
	boardChar = 'T';
}

void Trap::effect(Archeologist& player)
{
	player.setTrap(true);
}
