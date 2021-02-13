#pragma once

class Archeologist;

class Resources
{
protected:
	size_t size;
	char boardChar;
	bool claimed;

public:
	//Setters & Getters
	void setSize(size_t sizeInput);
	void setBoardChar(char boardCharInput);
	void setClaimed(bool claimedInput);
	
	size_t getSize();
	char getBoardChar();
	bool getClaimed();
	
	//Other Methods
	virtual void effect(Archeologist& player) = 0;
};

