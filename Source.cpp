#include "Grid.h"
#include <iostream>

bool continuePlaying(const Archeologist& ar1, const Archeologist& ar2, size_t maxScore);
void handleDice1(Grid& grid, size_t row, size_t column, Archeologist& ar);
void handleDice6(Grid& grid, size_t row, size_t column, Archeologist& ar);
void handleDiceRest(Grid& grid, size_t row, size_t column, Archeologist& ar);

//Helper Functions for dice 6 and object position
void handleLeft(Grid& grid, size_t r, size_t c, Archeologist& ar);
void handleLeftBottom(Grid& grid, size_t r, size_t c, Archeologist& ar);
void handleBottom(Grid& grid, size_t r, size_t c, Archeologist& ar);
void handleRight(Grid& grid, size_t r, size_t c, Archeologist& ar);
void handleRightTop(Grid& grid, size_t r, size_t c, Archeologist& ar);
void handleTop(Grid& grid, size_t r, size_t c, Archeologist& ar);
void handleInner(Grid& grid, size_t r, size_t c, Archeologist& ar);

int main()
{
	std::cout << "|========= The Bone Wars - A Primitive Board Game =========|" << std::endl;
	std::cout << "|                          Notes                           |" << std::endl;
	std::cout << "|    . Cells labeled with - indicate undiscovered region   |" << std::endl;
	std::cout << "|==========================================================|" << std::endl;

	//Getting board size from user
	size_t boardSize{ 0 };
	while (boardSize < 5)
	{
		std::cout << "Board size is set to: ";
		std::cin >> boardSize;
		if (boardSize < 5)
		{
			std::cout << "Please an integer greater than on equal to 5" << std::endl;
		}
	}

	//Creating and initializing two archeologists
	Archeologist cope("Cope");
	Archeologist marsh("Marsh");

	std::cout << "Rolling the dice to set initial energy of players..." << std::endl;
	std::random_device r1;
	std::mt19937 gen1(r1());
	std::uniform_int_distribution<size_t> dis1(boardSize, 2 * boardSize);
	size_t initialHealth = static_cast<size_t>(dis1(gen1));

	cope.setEnergy(static_cast<double>(initialHealth));
	marsh.setEnergy(static_cast<double>(initialHealth));

	std::cout << "Initial energies are set to " << initialHealth << "!" << std::endl;
	std::cout << "Good luck!\n";

	Grid grid(boardSize);
	
	//grid.displayGrid();       //Uncomment to display the current grid
	std::cout << "\n";

	//Playing Game
	std::uniform_int_distribution<size_t> dis2(1, 6);
	size_t diceEffect = 0;
	size_t rCope=0, cCope=0, rMarsh=0, cMarsh=0;
	
	while (continuePlaying(cope, marsh, grid.getMaxScore()))
	{
		std::cout << grid;

		//Randomly determining the dice effect and its consequences
		diceEffect = static_cast<size_t>(dis2(gen1));
		if (diceEffect == 1)
		{
			std::cout << std::endl;
			std::cout << "Rolled 1! If a player lands on a trap, effect of it will be disregarded!" << std::endl;
		}
		else if (diceEffect == 6)
		{
			std::cout << std::endl;
			std::cout << "Rolled 6! All the neighbours of target location will be revealed!" << std::endl;
		}
		else
		{
			std::cout << std::endl;
			std::cout << "Rolled " << diceEffect << "! No special actions will be performed this round!" << std::endl;
		}

		//Getting Destination Coordinates for Cope
		std::cout << "Cope, Enter your destination coordinates (r c): ";
		std::cin >> rCope >> cCope;
		std::vector<size_t>::iterator it = std::find(grid.getClaimedCells().begin(), grid.getClaimedCells().end(),
			rCope * boardSize + cCope);
		while (rCope >= boardSize || cCope >= boardSize || it != grid.getClaimedCells().end() 
			|| (rCope == 0 && cCope == 0) || (rCope == boardSize - 1 && cCope == boardSize - 1))
		{
			if (rCope >= boardSize || cCope >= boardSize)
			{
				std::cout << "The Coordinates are out of board size!" << std::endl;
			}
			else if ((rCope == 0 && cCope==0) || (rCope == boardSize-1 && cCope == boardSize-1))
			{
				std::cout << "This place is reserved for archeologists." <<std:: endl;
			}
			else if (it != grid.getClaimedCells().end())
			{
				std::cout << "Target has already been claimed." << std::endl;
			}
			std::cout << "Enter valid destination coordinates (r c): ";
			std::cin >> rCope >> cCope;
			it = std::find(grid.getClaimedCells().begin(), grid.getClaimedCells().end(),
				rCope * boardSize + cCope);
		}
		grid.getClaimedCells().push_back(rCope * boardSize + cCope);

		//Handling Dices
		if (diceEffect == 1)
			handleDice1(grid, rCope, cCope, cope);
		else if (diceEffect == 6)
			handleDice6(grid, rCope, cCope, cope);
		else
			handleDiceRest(grid, rCope, cCope, cope);

		//Getting Destination Coordinates for Marsh
		std::cout << "Marsh, Enter your destination coordinates (r c): ";
		std::cin >> rMarsh >> cMarsh;
		std::vector<size_t>::iterator it2 = std::find(grid.getClaimedCells().begin(), grid.getClaimedCells().end(),
			rMarsh * boardSize + cMarsh);
		while (rMarsh >= boardSize || cMarsh >= boardSize || it2 != grid.getClaimedCells().end() 
			|| (rMarsh == 0 && cMarsh == 0) || (rMarsh == boardSize - 1 && cMarsh == boardSize - 1))
		{
			if (rMarsh >= boardSize || cMarsh >= boardSize)
			{
				std::cout << "The Coordinates are out of board size!" << std::endl;
			}
			else if ((rMarsh == 0 && cMarsh == 0) || (rMarsh == boardSize - 1 && cMarsh == boardSize - 1))
			{
				std::cout << "This place is reserved for archeologists."<< std::endl;
			}
			else if (it2 != grid.getClaimedCells().end())
			{
				std::cout << "Target has already been claimed." << std::endl;
			}
			std::cout << "Enter valid destination coordinates (r c): ";
			std::cin >> rMarsh >> cMarsh;
			it2 = std::find(grid.getClaimedCells().begin(), grid.getClaimedCells().end(),
				rMarsh * boardSize + cMarsh);
		}
		grid.getClaimedCells().push_back(rMarsh * boardSize + cMarsh);
		
		//Handling Dices
		if (diceEffect == 1)
			handleDice1(grid, rMarsh, cMarsh, marsh);
		else if (diceEffect == 6)
			handleDice6(grid, rMarsh, cMarsh, marsh);
		else
			handleDiceRest(grid, rMarsh, cMarsh, marsh);
		
		//Decrementing Player Energies
		if (marsh.getTrap())
		{
			marsh.modifyEnergy(-1.25);
		}
		else
		{
			marsh.modifyEnergy(-1.0);
		}
		if (cope.getTrap())
		{
			cope.modifyEnergy(-1.25);
		}
		else
		{
			cope.modifyEnergy(-1.0);
		}
		//Displaying Energy and Scores
		std::cout << "\n==Cope==" << std::endl;
		std::cout << "Energy: " << cope.getEnergy() << std::endl;
		std::cout << "Score: " << cope.getScore() << std::endl;
		std::cout << "==Marsh==" << std::endl;
		std::cout << "Energy: " << marsh.getEnergy() << std::endl;
		std::cout << "Score: " << marsh.getScore() << "\n" << std::endl;
	}
	//Displaying the Game Winner
	std::cout << "|==========================================================|" << std::endl;
	std::cout << "|                    THE WINNER ==";
	if (marsh.getScore() > cope.getScore())
	{
		std::cout << " MARSH";
	}
	else if (marsh.getScore() < cope.getScore())
	{
		std::cout << " COPE ";
	}
	else
	{
		std::cout << " DRAW";
	}
	std::cout << "                   |" << std::endl;
	std::cout << "|==========================================================|" << std::endl;

	//Displaying the Inventories
	std::cout << "\n";
	std::cout << "Marsh Inventory: ";
	std::cout << "- ";
	for (size_t i = 0; i < marsh.getInventory().size(); i++)
	{
		std::cout << marsh.getInventory().at(i)->getBoardChar() << " - ";
	}
	std::cout << "\n";
	std::cout << "Cope Inventory: ";
	std::cout << "- ";
	for (size_t i = 0; i < cope.getInventory().size(); i++)
	{
		std::cout << cope.getInventory().at(i)->getBoardChar() << " - ";
	}

	//Deallocate memory
	for (size_t i = 0; i < marsh.getInventory().size(); i++)
	{
		delete marsh.getInventory().at(i);
	}
	for (size_t i = 0; i < cope.getInventory().size(); i++)
	{
		delete cope.getInventory().at(i);
	}

	return 0;
}

bool continuePlaying(const Archeologist& ar1, const Archeologist& ar2, size_t maxScore)
{
	if (ar1.getScore() >maxScore/2 || ar2.getScore() > maxScore/2)
	{
		return false;
	}
	else if (ar1.getEnergy() <= 0 && ar1.getScore() < ar2.getScore())
	{
		return false;
	}
	else if (ar2.getEnergy() <= 0 && ar2.getScore() < ar1.getScore())
	{
		return false;
	}
	else
	{
		return true;
	}
}
void handleDice1(Grid& grid, size_t row, size_t column, Archeologist& ar)
{
	if (grid.getBoard().at(row).at(column) != nullptr && !(grid.getBoard().at(row).at(column)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(row).at(column));
		grid.getBoard().at(row).at(column)->setClaimed(true);
		std::cout << grid.getBoard().at(row).at(column)->getBoardChar() << " claimed!" << std::endl;
		for (size_t i = 0; i < grid.getBoard().size(); i++)
		{
			for (size_t j = 0; j < grid.getBoard().at(i).size(); j++)
			{
				if (grid.getBoard().at(i).at(j) == grid.getBoard().at(row).at(column) && 
					(i != row || j != column))
				{
					grid.getClaimedCells().push_back(i * grid.getBoard().size() + j);
				}
			}
		}
	}
	else if (grid.getBoard().at(row).at(column) != nullptr &&  grid.getBoard().at(row).at(column)->getClaimed())
	{
		std::cout << "Target has already been claimed." << std::endl;
	}
	else
	{
		std::cout << "No Resources" << std::endl;
	}
	ar.setTrap(false);
}
void handleDice6(Grid& grid, size_t row, size_t column, Archeologist& ar)
{
	if (grid.getBoard().at(row).at(column) != nullptr && !(grid.getBoard().at(row).at(column)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(row).at(column));
		grid.getBoard().at(row).at(column)->setClaimed(true);
		std::cout << "All resources neighbouring to "<<grid.getBoard().at(row).at(column)->getBoardChar()
			<< " are gathered!" << std::endl;
		for (size_t i = 0; i < grid.getBoard().size(); i++)
		{
			for (size_t j = 0; j < grid.getBoard().at(i).size(); j++)
			{
				if (grid.getBoard().at(i).at(j) == grid.getBoard().at(row).at(column) &&
					(i != row || j != column))
				{
					grid.getClaimedCells().push_back(i * grid.getBoard().size() + j);
				}
			}
		}
	}
	else if (grid.getBoard().at(row).at(column) != nullptr && grid.getBoard().at(row).at(column)->getClaimed())
	{
		std::cout << "Target has already been claimed." << std::endl;
	}
	else
	{
		std::cout << "No Resources" << std::endl;
	}

	//Figuring out the position of resource
	if (column == 0 && row < grid.getBoard().size() - 1 && row > 0)
	{
		handleLeft(grid, row, column, ar);
	}
	else if (column == 0 && row == grid.getBoard().size() - 1)
	{
		handleLeftBottom(grid, row, column, ar);
	}
	else if (column < grid.getBoard().size() - 1 && row == grid.getBoard().size() - 1 && column > 0)
	{
		handleBottom(grid, row, column, ar);
	}
	else if (column == grid.getBoard().size() - 1 && row > 0 && row < grid.getBoard().size() - 1)
	{
		handleRight(grid, row, column, ar);
	}
	else if (column == grid.getBoard().size() - 1 && row == 0)
	{
		handleRightTop(grid, row, column, ar);
	}
	else if (column > 0 && column < grid.getBoard().size() - 1 && row == 0)
	{
		handleTop(grid, row, column, ar);
	}
	else
	{
		handleInner(grid, row, column, ar);
	}
	ar.setTrap(false);
}
void handleDiceRest(Grid& grid, size_t row, size_t column, Archeologist& ar)
{
	if (grid.getBoard().at(row).at(column) != nullptr && !(grid.getBoard().at(row).at(column)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(row).at(column));
		grid.getBoard().at(row).at(column)->setClaimed(true);
		std::cout << grid.getBoard().at(row).at(column)->getBoardChar() << " claimed!" << std::endl;
		for (size_t i = 0; i < grid.getBoard().size(); i++)
		{
			for (size_t j = 0; j < grid.getBoard().at(i).size(); j++)
			{
				if (grid.getBoard().at(i).at(j) == grid.getBoard().at(row).at(column) &&
					(i != row || j != column))
				{
					grid.getClaimedCells().push_back(i * grid.getBoard().size() + j);
				}
			}
		}
	}
	else if (grid.getBoard().at(row).at(column) != nullptr && grid.getBoard().at(row).at(column)->getClaimed())
	{
		std::cout << "Target has already been claimed." << std::endl;
	}
	else
	{
		std::cout << "No Resources" << std::endl;
	}
}
void handleLeft(Grid& grid, size_t r, size_t c, Archeologist& ar)
{
	/*
	4 0
	x 1
	3 2
	*/

	if (grid.getBoard().at(r - 1).at(c + 1) != nullptr && !(grid.getBoard().at(r - 1).at(c + 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r - 1).at(c + 1));
		grid.getBoard().at(r - 1).at(c + 1)->setClaimed(true);
		grid.getClaimedCells().push_back((r-1) * grid.getBoard().size() + (c+1));
	}
	if (grid.getBoard().at(r).at(c + 1) != nullptr && !(grid.getBoard().at(r).at(c + 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r).at(c + 1));
		grid.getBoard().at(r).at(c + 1)->setClaimed(true);
		grid.getClaimedCells().push_back(r * grid.getBoard().size() + (c+1));
	}
	if (grid.getBoard().at(r + 1).at(c + 1) != nullptr && !(grid.getBoard().at(r + 1).at(c + 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r + 1).at(c + 1));
		grid.getBoard().at(r + 1).at(c + 1)->setClaimed(true);
		grid.getClaimedCells().push_back((r+1) * grid.getBoard().size() + (c+1));
	}
	if (grid.getBoard().at(r + 1).at(c) != nullptr && !(grid.getBoard().at(r + 1).at(c)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r + 1).at(c));
		grid.getBoard().at(r + 1).at(c)->setClaimed(true);
		grid.getClaimedCells().push_back((r+1) * grid.getBoard().size() + c);
	}
	if (grid.getBoard().at(r - 1).at(c) != nullptr && !(grid.getBoard().at(r - 1).at(c)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r + 1).at(c));
		grid.getBoard().at(r - 1).at(c)->setClaimed(true);
		grid.getClaimedCells().push_back((r - 1) * grid.getBoard().size() + c);
	}
}
void handleLeftBottom(Grid& grid, size_t r, size_t c, Archeologist& ar)
{
	/*
	0 1
	x 2
	*/
	if (grid.getBoard().at(r - 1).at(c) != nullptr && !(grid.getBoard().at(r - 1).at(c)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r - 1).at(c));
		grid.getBoard().at(r - 1).at(c)->setClaimed(true);
		grid.getClaimedCells().push_back((r - 1) * grid.getBoard().size() + c);
	}
	if (grid.getBoard().at(r - 1).at(c + 1) != nullptr && !(grid.getBoard().at(r - 1).at(c + 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r - 1).at(c + 1));
		grid.getBoard().at(r - 1).at(c + 1)->setClaimed(true);
		grid.getClaimedCells().push_back((r - 1) * grid.getBoard().size() + (c + 1));
	}
	if (grid.getBoard().at(r).at(c + 1) != nullptr && !(grid.getBoard().at(r).at(c + 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r).at(c + 1));
		grid.getBoard().at(r).at(c + 1)->setClaimed(true);
		grid.getClaimedCells().push_back(r * grid.getBoard().size() + (c + 1));
	}
}
void handleBottom(Grid& grid, size_t r, size_t c, Archeologist& ar)
{
	/*
	1 2 3
	0 x 4
	*/
	if (grid.getBoard().at(r).at(c - 1) != nullptr && !(grid.getBoard().at(r).at(c - 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r).at(c - 1));
		grid.getBoard().at(r).at(c - 1)->setClaimed(true);
		grid.getClaimedCells().push_back(r * grid.getBoard().size() + (c - 1));
	}
	if (grid.getBoard().at(r - 1).at(c - 1) != nullptr && !(grid.getBoard().at(r - 1).at(c - 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r - 1).at(c - 1));
		grid.getBoard().at(r - 1).at(c - 1)->setClaimed(true);
		grid.getClaimedCells().push_back((r - 1) * grid.getBoard().size() + (c - 1));
	}
	if (grid.getBoard().at(r - 1).at(c) != nullptr && !(grid.getBoard().at(r - 1).at(c)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r - 1).at(c));
		grid.getBoard().at(r - 1).at(c)->setClaimed(true);
		grid.getClaimedCells().push_back((r - 1) * grid.getBoard().size() + c);
	}
	if (grid.getBoard().at(r - 1).at(c + 1) != nullptr && !(grid.getBoard().at(r - 1).at(c + 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r - 1).at(c + 1));
		grid.getBoard().at(r - 1).at(c + 1)->setClaimed(true);
		grid.getClaimedCells().push_back((r - 1) * grid.getBoard().size() + (c + 1));
	}
	if (grid.getBoard().at(r).at(c + 1) != nullptr && !(grid.getBoard().at(r).at(c + 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r).at(c + 1));
		grid.getBoard().at(r).at(c + 1)->setClaimed(true);
		grid.getClaimedCells().push_back((r) * grid.getBoard().size() + (c + 1));
	}
}
void handleRight(Grid& grid, size_t r, size_t c, Archeologist& ar)
{
	/*
	2 3
	1 x
	0 4
	*/
	if (grid.getBoard().at(r + 1).at(c - 1) != nullptr && !(grid.getBoard().at(r + 1).at(c - 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r + 1).at(c - 1));
		grid.getBoard().at(r + 1).at(c - 1)->setClaimed(true);
		grid.getClaimedCells().push_back((r + 1) * grid.getBoard().size() + (c - 1));
	}
	if (grid.getBoard().at(r).at(c - 1) != nullptr && !(grid.getBoard().at(r).at(c - 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r).at(c - 1));
		grid.getBoard().at(r).at(c - 1)->setClaimed(true);
		grid.getClaimedCells().push_back(r * grid.getBoard().size() + (c - 1));
	}
	if (grid.getBoard().at(r - 1).at(c - 1) != nullptr && !(grid.getBoard().at(r - 1).at(c - 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r - 1).at(c - 1));
		grid.getBoard().at(r - 1).at(c - 1)->setClaimed(true);
		grid.getClaimedCells().push_back((r - 1) * grid.getBoard().size() + (c - 1));
	}
	if (grid.getBoard().at(r - 1).at(c) != nullptr && !(grid.getBoard().at(r - 1).at(c)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r - 1).at(c));
		grid.getBoard().at(r - 1).at(c)->setClaimed(true);
		grid.getClaimedCells().push_back((r - 1) * grid.getBoard().size() + c );
	}
	if (grid.getBoard().at(r + 1).at(c) != nullptr && !(grid.getBoard().at(r + 1).at(c)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r - 1).at(c));
		grid.getBoard().at(r + 1).at(c)->setClaimed(true);
		grid.getClaimedCells().push_back((r + 1) * grid.getBoard().size() + c);
	}
}
void handleRightTop(Grid& grid, size_t r, size_t c, Archeologist& ar)
{
	/*
	0 x
	1 2
	*/
	if (grid.getBoard().at(r).at(c - 1) != nullptr && !(grid.getBoard().at(r).at(c - 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r).at(c - 1));
		grid.getBoard().at(r).at(c - 1)->setClaimed(true);
		grid.getClaimedCells().push_back(r * grid.getBoard().size() + (c - 1));
	}
	if (grid.getBoard().at(r + 1).at(c - 1) != nullptr && !(grid.getBoard().at(r + 1).at(c - 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r + 1).at(c - 1));
		grid.getBoard().at(r + 1).at(c - 1)->setClaimed(true);
		grid.getClaimedCells().push_back((r + 1) * grid.getBoard().size() + (c - 1));
	}
	if (grid.getBoard().at(r + 1).at(c) != nullptr && !(grid.getBoard().at(r + 1).at(c)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r + 1).at(c));
		grid.getBoard().at(r + 1).at(c)->setClaimed(true);
		grid.getClaimedCells().push_back((r + 1) * grid.getBoard().size() + c);
	}
}
void handleTop(Grid& grid, size_t r, size_t c, Archeologist& ar)
{
	/*
	4 x 0
	3 2 1
	*/
	if (grid.getBoard().at(r).at(c + 1) != nullptr && !(grid.getBoard().at(r).at(c + 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r).at(c + 1));
		grid.getBoard().at(r).at(c + 1)->setClaimed(true);
		grid.getClaimedCells().push_back(r * grid.getBoard().size() + (c + 1));
	}
	if (grid.getBoard().at(r + 1).at(c + 1) != nullptr && !(grid.getBoard().at(r + 1).at(c + 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r + 1).at(c + 1));
		grid.getBoard().at(r + 1).at(c + 1)->setClaimed(true);
		grid.getClaimedCells().push_back((r + 1) * grid.getBoard().size() + (c + 1));
	}
	if (grid.getBoard().at(r + 1).at(c) != nullptr && !(grid.getBoard().at(r + 1).at(c)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r + 1).at(c));
		grid.getBoard().at(r + 1).at(c)->setClaimed(true);
		grid.getClaimedCells().push_back((r + 1) * grid.getBoard().size() + c);
	}
	 if (grid.getBoard().at(r + 1).at(c - 1) != nullptr && !(grid.getBoard().at(r + 1).at(c - 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r + 1).at(c - 1));
		grid.getBoard().at(r + 1).at(c - 1)->setClaimed(true);
		grid.getClaimedCells().push_back((r + 1) * grid.getBoard().size() + (c - 1));
	}
	 if (grid.getBoard().at(r).at(c - 1) != nullptr && !(grid.getBoard().at(r).at(c - 1)->getClaimed()))
	 {
		 ar.addResource(grid.getBoard().at(r).at(c - 1));
		 grid.getBoard().at(r).at(c - 1)->setClaimed(true);
		 grid.getClaimedCells().push_back((r) * grid.getBoard().size() + (c - 1));
	 }
}
void handleInner(Grid& grid, size_t r, size_t c, Archeologist& ar)
{
	/*
	6 0 1
	5 x 2
	4 3 7
	*/
	if (grid.getBoard().at(r - 1).at(c) != nullptr && !(grid.getBoard().at(r - 1).at(c)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r - 1).at(c));
		grid.getBoard().at(r - 1).at(c)->setClaimed(true);
		grid.getClaimedCells().push_back((r - 1) * grid.getBoard().size() + c);
	}
	if (grid.getBoard().at(r - 1).at(c + 1) != nullptr && !(grid.getBoard().at(r - 1).at(c + 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r - 1).at(c+1));
		grid.getBoard().at(r - 1).at(c + 1)->setClaimed(true);
		grid.getClaimedCells().push_back((r - 1) * grid.getBoard().size() + (c + 1));
	}
	if (grid.getBoard().at(r).at(c + 1) != nullptr && !(grid.getBoard().at(r).at(c + 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r).at(c + 1));
		grid.getBoard().at(r).at(c + 1)->setClaimed(true);
		grid.getClaimedCells().push_back(r * grid.getBoard().size() + (c + 1));
	}
	if (grid.getBoard().at(r + 1).at(c) != nullptr && !(grid.getBoard().at(r + 1).at(c)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r + 1).at(c));
		grid.getBoard().at(r + 1).at(c)->setClaimed(true);
		grid.getClaimedCells().push_back((r + 1) * grid.getBoard().size() + c);
	}
	if (grid.getBoard().at(r + 1).at(c - 1) != nullptr && !(grid.getBoard().at(r + 1).at(c - 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r + 1).at(c - 1));
		grid.getBoard().at(r + 1).at(c - 1)->setClaimed(true);
		grid.getClaimedCells().push_back((r + 1) * grid.getBoard().size() + (c - 1));
	}
	if (grid.getBoard().at(r).at(c - 1) != nullptr && !(grid.getBoard().at(r).at(c - 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r).at(c - 1));
		grid.getBoard().at(r).at(c - 1)->setClaimed(true);
		grid.getClaimedCells().push_back(r * grid.getBoard().size() + (c - 1));
	}
	if (grid.getBoard().at(r-1).at(c - 1) != nullptr && !(grid.getBoard().at(r-1).at(c - 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r-1).at(c - 1));
		grid.getBoard().at(r-1).at(c - 1)->setClaimed(true);
		grid.getClaimedCells().push_back((r-1) * grid.getBoard().size() + (c - 1));
	}
	if (grid.getBoard().at(r + 1).at(c + 1) != nullptr && !(grid.getBoard().at(r + 1).at(c + 1)->getClaimed()))
	{
		ar.addResource(grid.getBoard().at(r + 1).at(c + 1));
		grid.getBoard().at(r + 1).at(c + 1)->setClaimed(true);
		grid.getClaimedCells().push_back((r + 1) * grid.getBoard().size() + (c + 1));
	}
}