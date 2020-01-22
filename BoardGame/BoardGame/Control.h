#pragma once
#include <ctime>
#include <algorithm>
#include <fstream>
#include <deque>
#include <SFML/Graphics.hpp>

#include "keys.h"
#include "DrawSystem.h"
#include "random.h"
#include "geometry.h"
#include "Mouse.h"
#include "Gamepad.h"
#include "Board.h"
#include "Bot.h"

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
	std::vector<bool> keysPrev = keys;
	std::vector<std::vector<int> > keyMatches;

	Board board;
	Bot robot;
	

	std::deque<Board> steps;

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

