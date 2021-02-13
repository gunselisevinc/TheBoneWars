#include "Resources.h"

void Resources::setSize(size_t sizeInput)
{
	size = sizeInput;
}

void Resources::setBoardChar(char boardCharInput)
{
	boardChar = boardCharInput;
}

void Resources::setClaimed(bool claimedInput)
{
	claimed = claimedInput;
}

size_t Resources::getSize()
{
	return size;
}

char Resources::getBoardChar()
{
	return boardChar;
}

bool Resources::getClaimed()
{
	return claimed;
}
