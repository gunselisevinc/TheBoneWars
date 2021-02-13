#pragma once
#include "Resources.h"
class Water :
	public Resources
{
public:
	//COnstructor
	Water();

	//Other Methods
	virtual void effect(Archeologist& player) override;
};

