#pragma once
#include <ctime>
#include <algorithm>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "keys.h"
#include "DrawSystem.h"
#include "random.h"
#include "geometry.h"
#include "Mouse.h"
#include "Gamepad.h"
#include "Board.h"

enum controlMode {
	MENU, GAME
};

class Control{
public:
	controlMode mode = MENU;

	DrawSystem drawSys;
	Mouse mouse;
	Mouse mousePrev;
	Gamepad joystick;

	std::vector<bool> keys = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	std::vector<std::vector<int> > keyMatches;

	Board board;

	//time
	int dt = 20;
	int timePrev = 0;
	bool stop = 0;
	int iteration = 0;


	Control();
	~Control();

	void events();	
	void step();
	Vector2d getCursorPos();
	std::string configParametersAdress = "parameters.conf";
	void loadConfig();
	void saveConfig();

	std::pair<int, int> bot();
};

