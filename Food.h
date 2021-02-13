#pragma once
#include "Resources.h"

enum class FoodType {Burger, Nuggets, Chips};

class Food :
	public Resources
{
protected:
	FoodType foodType;
	double energy;
	
public:
	//Constructor
	Food(FoodType foodTypeInput);

	//Setter & Getter
	void setFoodType(FoodType);
	FoodType getFoodType();

	//Other Methods
	virtual void effect(Archeologist& player) override;
};

