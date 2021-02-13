#pragma once
#include "Resources.h"
class MedicalSupplies :
	public Resources
{
public:
	//COntructor
	MedicalSupplies();

	//Other Methods
	virtual void effect(Archeologist& player) override;
};

