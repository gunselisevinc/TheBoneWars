#pragma once
#include "Resources.h"
class Trap :
	public Resources
{
public:
	//Constructor
	Trap();

	//Other Methods
	virtual void effect(Archeologist& player) override;
};

