#include "Grid.h"
#include <iostream>

Grid::Grid(size_t sizeInput)
	:board{ sizeInput, std::vector<Resources*>(sizeInput, nullptr) } , nOfBone{3*sizeInput*sizeInput/25},
	nOfTrap{ 2 * sizeInput * sizeInput / 25 }, nOfFood{ 3 * sizeInput * sizeInput / 25 },
	nOfWater{ 2 * sizeInput * sizeInput / 25 }, nOfMedicalSupply{ sizeInput * sizeInput / 25 },
	boneVector{nOfBone, nullptr}, trapVector{nOfTrap, nullptr}, foodVector{nOfFood, nullptr}, 
	waterVector{nOfWater, nullptr}, medicalSupplyVector{nOfMedicalSupply, nullptr}

{
	initializeResourceVectors();
	deployResources();
}

std::vector<std::vector<Resources*>>& Grid::getBoard()
{
	return board;
}

std::vector<size_t>& Grid::getClaimedCells()
{
	return claimedCells;
}

void Grid::initializeResourceVectors()
{
	//to randomize the numbers
	std::random_device r1;
	std::mt19937 gen1(r1());
	std::uniform_int_distribution<size_t> dis1(0, 2);

	for (size_t i = 0; i < nOfBone; i++)
	{
		boneVector.at(i) = new Bone(static_cast<BoneType>(dis1(gen1)));
	}
	for (size_t i = 0; i < nOfTrap; i++)
	{
		trapVector.at(i) = new Trap();
	}
	for (size_t i = 0; i < nOfFood; i++)
	{
		foodVector.at(i) = new Food(static_cast<FoodType>(dis1(gen1)));
	}
	for (size_t i = 0; i < nOfWater; i++)
	{
		waterVector.at(i) = new Water();
	}
	for (size_t i = 0; i < nOfMedicalSupply; i++)
	{
		medicalSupplyVector.at(i) = new MedicalSupplies();
	}
}

void Grid::deployResources()
{
	//to randomize the numbers
	std::random_device r1;
	std::mt19937 gen1(r1());
	std::uniform_int_distribution<size_t> dis1(0, board.size()-1);

	std::vector<size_t> numbersBoard;
	for (size_t i = 1; i < (board.size() * board.size())-1; i++)
	{
		numbersBoard.push_back(i);
	}

	//to shuffle the numbersBoard vector
	size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(numbersBoard.begin(), numbersBoard.end(), std::default_random_engine(seed));

	size_t counter = 0;
	size_t r=0, c=0;    //row and column
	size_t i = 0;
	//deploying bones
	while(i < nOfBone)
	{
		r = numbersBoard.at(counter) / board.size();
		c = numbersBoard.at(counter) % board.size();

		while (board.at(r).at(c) != nullptr)
		{
			if (counter + 1 != board.size() * board.size())
				counter++;
			else
				counter = 0;

			r = numbersBoard.at(counter) / board.size();
			c = numbersBoard.at(counter) % board.size();
		}

		if (boneVector.at(i)->getSize() == 1)
		{
			board.at(r).at(c) = boneVector.at(i);
			i++;
		}
		else
		{
			if (c == 0 && r < board.size() - 1 && r > 0)
			{
				if (checkLeft(r, c))
				{
					board.at(r).at(c) = boneVector.at(i);
					handleLeft(r, c, boneVector.at(i));
					i++;
				}
			}
			else if (c == 0 && r == board.size() - 1)
			{
				if (checkLeftBottom(r, c))
				{
					board.at(r).at(c) = boneVector.at(i);
					handleLeftBottom(r, c, boneVector.at(i));
					i++;
				}
					
			}
			else if (c < board.size() - 1 && r == board.size() - 1 && c > 0)
			{
				if (checkBottom(r, c))
				{
					board.at(r).at(c) = boneVector.at(i);
					handleBottom(r, c, boneVector.at(i));
					i++;
				}
					
			}
			else if (c == board.size() - 1 && r > 0 && r < board.size() - 1)
			{
				if (checkRight(r, c))
				{
					board.at(r).at(c) = boneVector.at(i);
					handleRight(r, c, boneVector.at(i));
					i++;
				}
					
			}
			else if (c == board.size() - 1 && r == 0)
			{
				if (checkRightTop(r, c))
				{
					board.at(r).at(c) = boneVector.at(i);
					handleRightTop(r, c, boneVector.at(i));
					i++;
				}
					
			}
			else if (c > 0 && c < board.size() - 1 && r == 0)
			{
				if (checkTop(r, c))
				{
					board.at(r).at(c) = boneVector.at(i);
					handleTop(r, c, boneVector.at(i));
					i++;
				}
			}
			else
			{
				if (checkInner(r, c))
				{
					board.at(r).at(c) = boneVector.at(i);
					handleInner(r, c, boneVector.at(i));
					i++;
				}
			}
		}
			
		if (counter + 1 != board.size() * board.size())
			counter++;
		else
			counter = 0;
	}

	//deploying traps
	for (size_t i = 0; i < nOfTrap; i++)
	{
		r = numbersBoard.at(counter) / board.size();
		c = numbersBoard.at(counter) % board.size();

		while (board.at(r).at(c) != nullptr)
		{
			if (counter + 1 != board.size() * board.size())
				counter++;
			else
				counter = 0;

			r = numbersBoard.at(counter) / board.size();
			c = numbersBoard.at(counter) % board.size();
		}

		board.at(r).at(c) = trapVector.at(i);

		if (counter + 1 != board.size() * board.size())
			counter++;
		else
			counter = 0;
	}

	//deploying foods
	for (size_t i = 0; i < nOfFood; i++)
	{
		r = numbersBoard.at(counter) / board.size();
		c = numbersBoard.at(counter) % board.size();

		while (board.at(r).at(c) != nullptr)
		{
			if (counter + 1 != board.size() * board.size())
				counter++;
			else
				counter = 0;

			r = numbersBoard.at(counter) / board.size();
			c = numbersBoard.at(counter) % board.size();
		}

		if (foodVector.at(i)->getSize() == 1)
		{
			board.at(r).at(c) = foodVector.at(i);
		}
		else
		{
			if (c == 0 && r < board.size() - 1 && r > 0)
			{
				if (checkLeft(r, c))
				{
					board.at(r).at(c) = foodVector.at(i);
					handleLeft(r, c, foodVector.at(i));
					i++;
				}
			}
			else if (c == 0 && r == board.size() - 1)
			{
				if (checkLeftBottom(r, c))
				{
					board.at(r).at(c) = foodVector.at(i);
					handleLeftBottom(r, c, foodVector.at(i));
					i++;
				}

			}
			else if (c < board.size() - 1 && r == board.size() - 1 && c > 0)
			{
				if (checkBottom(r, c))
				{
					board.at(r).at(c) = foodVector.at(i);
					handleBottom(r, c, foodVector.at(i));
					i++;
				}

			}
			else if (c == board.size() - 1 && r > 0 && r < board.size() - 1)
			{
				if (checkRight(r, c))
				{
					board.at(r).at(c) = foodVector.at(i);
					handleRight(r, c, foodVector.at(i));
					i++;
				}

			}
			else if (c == board.size() - 1 && r == 0)
			{
				if (checkRightTop(r, c))
				{
					board.at(r).at(c) = foodVector.at(i);
					handleRightTop(r, c, foodVector.at(i));
					i++;
				}

			}
			else if (c > 0 && c < board.size() - 1 && r == 0)
			{
				if (checkTop(r, c))
				{
					board.at(r).at(c) = foodVector.at(i);
					handleTop(r, c, foodVector.at(i));
					i++;
				}
			}
			else
			{
				if (checkInner(r, c))
				{
					board.at(r).at(c) = foodVector.at(i);
					handleInner(r, c, foodVector.at(i));
					i++;
				}
			}
		}

		if (counter + 1 != board.size() * board.size())
			counter++;
		else
			counter = 0;
	}

	//deploying waters
	for (size_t i = 0; i < nOfWater; i++)
	{
		r = numbersBoard.at(counter) / board.size();
		c = numbersBoard.at(counter) % board.size();

		while (board.at(r).at(c) != nullptr)
		{
			if (counter + 1 != board.size() * board.size())
				counter++;
			else
				counter = 0;

			r = numbersBoard.at(counter) / board.size();
			c = numbersBoard.at(counter) % board.size();
		}

		board.at(r).at(c) = waterVector.at(i);

		if (counter + 1 != board.size() * board.size())
			counter++;
		else
			counter = 0;
	}

	//deploying medical supplies
	for (size_t i = 0; i < nOfMedicalSupply ; i++)
	{
		r = numbersBoard.at(counter) / board.size();
		c = numbersBoard.at(counter) % board.size();

		while (board.at(r).at(c) != nullptr)
		{
			if (counter + 1 != board.size() * board.size())
				counter++;
			else
				counter = 0;

			r = numbersBoard.at(counter) / board.size();
			c = numbersBoard.at(counter) % board.size();
		}
		
		board.at(r).at(c) = medicalSupplyVector.at(i);
	
		if (counter + 1 != board.size() * board.size())
			counter++;
		else
			counter = 0;
	}

	
}

void Grid::displayGrid()
{
	for (size_t i = 0; i < board.size(); i++) //Row
	{
		for (size_t j = 0; j < board[i].size(); j++) //Column 
		{
			if (board.at(i).at(j) != nullptr)
			{
				std::cout << board.at(i).at(j)->getBoardChar() << "\t";
			}
			else
			{
				std::cout << "-\t";
			}
		}
		std::cout << std::endl;
	}
}

size_t Grid::getMaxScore()
{
	size_t score = 0;

	for (size_t i = 0; i < foodVector.size(); i++)
	{
		score += boneVector.at(i)->getScore();
	}

	return score;
}

bool Grid::checkLeft(size_t r, size_t c)
{
	/*
	- 0
	x 1
	3 2
	*/

	bool check = false;

	for (size_t i = 0; i < 4; i++)
	{
		if (board.at(r-1).at(c+1) == nullptr)
		{
			check = true;
		}
		else if (board.at(r).at(c + 1) == nullptr)
		{
			check = true;
		}
		else if (board.at(r+1).at(c + 1) == nullptr)
		{
			check = true;
		}
		else if (board.at(r+1).at(c) == nullptr)
		{
			check = true;
		}
	}
	return check;
}

bool Grid::checkLeftBottom(size_t r, size_t c)
{
	/*
	0 1 
	x 2
	*/

	bool check = false;

	for (size_t i = 0; i < 4; i++)
	{
		if (board.at(r - 1).at(c) == nullptr)
		{
			check = true;
		}
		else if (board.at(r - 1).at(c + 1) == nullptr)
		{
			check = true;
		}
		else if (board.at(r).at(c + 1) == nullptr)
		{
			check = true;
		}
	}
	return check;
}

bool Grid::checkBottom(size_t r, size_t c)
{
	/*
	1 2 3 
	0 x -
	*/

	bool check = false;

	for (size_t i = 0; i < 4; i++)
	{
		if (board.at(r).at(c - 1) == nullptr)
		{
			check = true;
		}
		else if (board.at(r-1).at(c - 1) == nullptr)
		{
			check = true;
		}
		else if (board.at(r - 1).at(c) == nullptr)
		{
			check = true;
		}
		else if (board.at(r - 1).at(c + 1) == nullptr)
		{
			check = true;
		}
	}
	return check;
}

bool Grid::checkRight(size_t r, size_t c)
{
	/*
	2 3
	1 x
	0 -
	*/

	bool check = false;

	for (size_t i = 0; i < 4; i++)
	{
		if (board.at(r + 1).at(c - 1) == nullptr)
		{
			check = true;
		}
		else if (board.at(r).at(c - 1) == nullptr)
		{
			check = true;
		}
		else if (board.at(r - 1).at(c - 1) == nullptr)
		{
			check = true;
		}
		else if (board.at(r - 1).at(c) == nullptr)
		{
			check = true;
		}
	}
	return check;
}

bool Grid::checkRightTop(size_t r, size_t c)
{
	/*
	0 x
	1 2
	*/

	bool check = false;

	for (size_t i = 0; i < 4; i++)
	{
		if (board.at(r).at(c - 1) == nullptr)
		{
			check = true;
		}
		else if (board.at(r + 1).at(c - 1) == nullptr)
		{
			check = true;
		}
		else if (board.at(r + 1).at(c) == nullptr)
		{
			check = true;
		}
	}
	return check;
}

bool Grid::checkTop(size_t r, size_t c)
{
	/*
	- x 0
	3 2 1
	*/

	bool check = false;

	for (size_t i = 0; i < 4; i++)
	{
		if (board.at(r).at(c + 1) == nullptr)
		{
			check = true;
		}
		else if (board.at(r + 1).at(c + 1) == nullptr)
		{
			check = true;
		}
		else if (board.at(r + 1).at(c) == nullptr)
		{
			check = true;
		}
		else if (board.at(r + 1).at(c - 1) == nullptr)
		{
			check = true;
		}
	}
	return check;
}

bool Grid::checkInner(size_t r, size_t c)
{
	/*
	- 0 1
	5 x 2
	4 3 -
	*/

	bool check = false;

	for (size_t i = 0; i < 4; i++)
	{
		if (board.at(r - 1).at(c) == nullptr)
		{
			check = true;
		}
		else if (board.at(r - 1).at(c + 1) == nullptr)
		{
			check = true;
		}
		else if (board.at(r).at(c + 1) == nullptr)
		{
			check = true;
		}
		else if (board.at(r + 1).at(c) == nullptr)
		{
			check = true;
		}
		else if (board.at(r + 1).at(c - 1) == nullptr)
		{
			check = true;
		}
		else if (board.at(r).at(c - 1) == nullptr)
		{
			check = true;
		}
	}
	return check;
}

void Grid::handleLeft(size_t r, size_t c, Resources* ptr)
{
	/*
	- 0
	x 1
	3 2
	*/

	std::vector<size_t> numbers;
	for (size_t i = 0; i < 4; i++)
	{
		numbers.push_back(i);
	}

	//to shuffle the numbers vector
	size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

	size_t check = 0;
	size_t i = 0;

	while (check != 1)
	{
		if (numbers.at(i) == 0 && board.at(r - 1).at(c + 1) == nullptr)
		{
			board.at(r - 1).at(c + 1) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 1 && board.at(r).at(c + 1) == nullptr)
		{
			board.at(r).at(c + 1) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 2 && board.at(r + 1).at(c + 1) == nullptr)
		{
			board.at(r + 1).at(c + 1) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 3 && board.at(r + 1).at(c) == nullptr)
		{
			board.at(r + 1).at(c) = ptr;
			check = 1;
		}
		i++;
	}
}

void Grid::handleLeftBottom(size_t r, size_t c, Resources* ptr)
{
	/*
	0 1
	x 2
	*/

	std::vector<size_t> numbers;
	for (size_t i = 0; i < 3; i++)
	{
		numbers.push_back(i);
	}

	//to shuffle the numbers vector
	size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

	size_t check = 0;
	size_t i = 0;

	while(check != 1)
	{
		if (numbers.at(i) == 0 && board.at(r - 1).at(c) == nullptr)
		{
			board.at(r - 1).at(c) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 1 && board.at(r - 1).at(c + 1) == nullptr)
		{
			board.at(r - 1).at(c + 1) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 2 && board.at(r).at(c + 1) == nullptr)
		{
			board.at(r).at(c + 1) = ptr;
			check = 1;
		}
		i++;
	}
}

void Grid::handleBottom(size_t r, size_t c, Resources* ptr)
{
	/*
	1 2 3
	0 x -
	*/

	std::vector<size_t> numbers;
	for (size_t i = 0; i < 4; i++)
	{
		numbers.push_back(i);
	}

	//to shuffle the numbers vector
	size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

	size_t check = 0;
	size_t i = 0;

	while(check != 1)
	{
		if (numbers.at(i) == 0 && board.at(r).at(c - 1) == nullptr)
		{
			board.at(r).at(c - 1) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 1 && board.at(r - 1).at(c - 1) == nullptr)
		{
			board.at(r - 1).at(c - 1) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 2 && board.at(r - 1).at(c) == nullptr)
		{
			board.at(r - 1).at(c) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 3 && board.at(r - 1).at(c + 1) == nullptr)
		{
			board.at(r - 1).at(c + 1) = ptr;
			check = 1;
		}
		i++;
	}
}

void Grid::handleRight(size_t r, size_t c, Resources* ptr)
{
	/*
	2 3
	1 x
	0 -
	*/

	std::vector<size_t> numbers;
	for (size_t i = 0; i < 4; i++)
	{
		numbers.push_back(i);
	}

	//to shuffle the numbers vector
	size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

	size_t check = 0;
	size_t i = 0;

	while(check != 1)
	{
		if (numbers.at(i) == 0 && board.at(r + 1).at(c - 1) == nullptr)
		{
			board.at(r + 1).at(c - 1) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 1 && board.at(r).at(c - 1) == nullptr)
		{
			board.at(r).at(c - 1) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 2 && board.at(r - 1).at(c - 1) == nullptr)
		{
			board.at(r - 1).at(c - 1) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 3 && board.at(r - 1).at(c) == nullptr)
		{
			board.at(r - 1).at(c) = ptr;
			check = 1;
		}
		i++;
	}
}

void Grid::handleRightTop(size_t r, size_t c, Resources* ptr)
{
	/*
	0 x
	1 2
	*/

	std::vector<size_t> numbers;
	for (size_t i = 0; i < 3; i++)
	{
		numbers.push_back(i);
	}

	//to shuffle the numbers vector
	size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

	size_t check = 0;
	size_t i = 0;

	while(check != 1)
	{
		if (numbers.at(i) == 0 && board.at(r).at(c - 1) == nullptr)
		{
			board.at(r).at(c - 1) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 1 && board.at(r + 1).at(c - 1) == nullptr)
		{
			board.at(r + 1).at(c - 1) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 2 && board.at(r + 1).at(c) == nullptr)
		{
			board.at(r + 1).at(c) = ptr;
			check = 1;
		}
		i++;
	}
}

void Grid::handleTop(size_t r, size_t c, Resources* ptr)
{
	/*
	- x 0
	3 2 1
	*/

	std::vector<size_t> numbers;
	for (size_t i = 0; i < 4; i++)
	{
		numbers.push_back(i);
	}

	//to shuffle the numbers vector
	size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

	size_t check = 0;
	size_t i = 0;

	while (check != 1)
	{
		if (numbers.at(i) == 0 && board.at(r).at(c + 1) == nullptr)
		{
			board.at(r).at(c + 1) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 1 && board.at(r + 1).at(c + 1) == nullptr)
		{
			board.at(r + 1).at(c + 1) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 2 && board.at(r + 1).at(c) == nullptr)
		{
			board.at(r + 1).at(c) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 3 && board.at(r + 1).at(c - 1) == nullptr)
		{
			board.at(r + 1).at(c - 1) = ptr;
			check = 1;
		}
		i++;
	}
}

void Grid::handleInner(size_t r, size_t c, Resources* ptr)
{
	/*
	- 0 1
	5 x 2
	4 3 -
	*/

	std::vector<size_t> numbers;
	for (size_t i = 0; i < 6; i++)
	{
		numbers.push_back(i);
	}

	//to shuffle the numbers vector
	size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

	size_t check = 0;
	size_t i = 0;

	while (check != 1)
	{
		if (numbers.at(i) == 0 && board.at(r - 1).at(c) == nullptr)
		{
			board.at(r - 1).at(c) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 1 && board.at(r - 1).at(c + 1) == nullptr)
		{
			board.at(r - 1).at(c) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 2 && board.at(r).at(c + 1) == nullptr)
		{
			board.at(r).at(c + 1) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 3 && board.at(r + 1).at(c) == nullptr)
		{
			board.at(r + 1).at(c) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 4 && board.at(r + 1).at(c - 1) == nullptr)
		{
			board.at(r + 1).at(c - 1) = ptr;
			check = 1;
		}
		else if (numbers.at(i) == 5 && board.at(r).at(c - 1) == nullptr)
		{
			board.at(r).at(c - 1) = ptr;
			check = 1;
		}
		i++;
	}
}

std::ostream& operator<<(std::ostream& os, const Grid& obj)
{
	for (size_t i = 0; i < obj.board.size(); i++)
	{
		for (size_t j = 0; j < obj.board.at(i).size(); j++)
		{
			if (obj.board.at(i).at(j)!=nullptr && obj.board.at(i).at(j)->getClaimed())
			{
				std::cout << obj.board.at(i).at(j)->getBoardChar() << "\t";
			}
			else
			{
				std::cout << "-\t";
			}
		}
		std::cout << "\n";
	}
	return os;
}
