#include "Food.h"
#include "Archeologist.h"

Food::Food(FoodType foodTypeInput)
	:foodType{foodTypeInput}, energy{0}
{
	claimed = false;
	switch (foodType)
	{
	case FoodType::Burger:
		size = 2;
		boardChar = 'B';
		energy = 4.0;
		break;
	case FoodType::Nuggets:
		size = 2;
		boardChar = 'N';
		energy = 3.0;
		break;
	case FoodType::Chips:
		size = 1;
		boardChar = 'C';
		energy = 2.0;
		break;
	default:
		break;
	}
}

void Food::setFoodType(FoodType foodTypeInput)
{
	foodType = foodTypeInput;
}

FoodType Food::getFoodType()
{
	return foodType;
}

void Food::effect(Archeologist& player)
{
	player.modifyEnergy(energy);
}
