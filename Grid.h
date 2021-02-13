#pragma once
#include "Resources.h"
#include "Food.h"
#include "Bone.h"
#include "MedicalSupplies.h"
#include "Trap.h"
#include "Water.h"
#include "Archeologist.h"

//Headers Used For Generating Unique Random Numbers
#include <algorithm>
#include <chrono>
#include <random>

class Grid
{
	std::vector<std::vector<Resources*>> board;
	size_t nOfBone;
	size_t nOfTrap;
	size_t nOfFood;
	size_t nOfWater;
	size_t nOfMedicalSupply;

	std::vector<Bone*> boneVector;
	std::vector<Trap*> trapVector;
	std::vector<Food*> foodVector;
	std::vector<Water*> waterVector;
	std::vector<MedicalSupplies*> medicalSupplyVector;
	
	std::vector<size_t> claimedCells;

public:
	//Constructor
	Grid(size_t sizeInput);

	//Getter
	std::vector<std::vector<Resources*>>& getBoard();
	std::vector<size_t>& getClaimedCells();

	//Other Methods
	void initializeResourceVectors();
	void deployResources();
	void displayGrid();
	friend std::ostream& operator<< (std::ostream& os, const Grid& obj);
	size_t getMaxScore();

private:
	bool checkLeft(size_t r, size_t c);
	bool checkLeftBottom(size_t r, size_t c);
	bool checkBottom(size_t r, size_t c);
	bool checkRight(size_t r, size_t c);
	bool checkRightTop(size_t r, size_t c);
	bool checkTop(size_t r, size_t c);
	bool checkInner(size_t r, size_t c);

	void handleLeft(size_t r, size_t c, Resources* ptr);
	void handleLeftBottom(size_t r, size_t c, Resources* ptr);
	void handleBottom(size_t r, size_t c, Resources* ptr);
	void handleRight(size_t r, size_t c, Resources* ptr);
	void handleRightTop(size_t r, size_t c, Resources* ptr);
	void handleTop(size_t r, size_t c, Resources* ptr);
	void handleInner(size_t r, size_t c, Resources* ptr);
};

