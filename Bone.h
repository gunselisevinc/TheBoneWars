#pragma once
#include "Resources.h"

enum class BoneType {FullBody, Skull, Ordinary};

class Bone :
	public Resources
{
protected:
	BoneType boneType;
	size_t score;

public:
	//Constructor
	Bone(BoneType boneTypeInput);	

	//Setter & Getter
	void setBoneType(BoneType typeInput);
	BoneType getBoneType();
	size_t getScore();

	//Other Methods
	virtual void effect(Archeologist& player) override;
};

