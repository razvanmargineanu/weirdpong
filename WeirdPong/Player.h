#pragma once

#include "model.h"

class Player
{
private:
	enum sides
	{
		leftSide,
		rightSide
	};
	
	Model playerModel;

	void loadModel(string objPath);

public:
	Player();
	void initPlayer(string objPath);
	void movePlayer();
	void setSide();
	


	~Player();
};

