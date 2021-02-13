#include "Bone.h"
#include "Archeologist.h"

Bone::Bone(BoneType boneTypeInput)
	:boneType{boneTypeInput}, score{0}
{
	claimed = false;
	switch (boneType)
	{
	case BoneType::FullBody:
		size = 2;
		boardChar = 'F';
		score = 100;
		break;
	case BoneType::Skull:
		size = 1;
		boardChar = 'S';
		score = 50;
		break;
	case BoneType::Ordinary:
		size = 1;
		boardChar = 'O';
		score = 20;
		break;
	default:
		break;
	}
}

void Bone::setBoneType(BoneType typeInput)
{
	boneType = typeInput;
}

BoneType Bone::getBoneType()
{
	return boneType;
}

size_t Bone::getScore()
{
	return score;
}

void Bone::effect(Archeologist& player)
{
	player.modifyScore(score);
}
