#include "Water.h"
#include "Archeologist.h"

Water::Water()
	
{
	claimed = false;
	size = 1;
	boardChar = 'W';
}

void Water::effect(Archeologist& player)
{
	player.modifyEnergy(1.0);
}
