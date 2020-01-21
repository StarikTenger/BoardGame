#include "Control.h"
#include "getMilliCount.h"
#include <iostream>
#include <fstream>
#include <sstream>

Control::Control() {
	for (int i = 0; i < 100; i++) {
		keyMatches.push_back({});
	}
	std::ifstream keys("keys.conf");
	while (keys) {
		std::string key;
		keys >> key;
		while (keys) {
			std::string key1;
			keys >> key1;
			if (key1 == "END")
				break;
			keyMatches[getKey(key1)].push_back(getKey(key));

		}
	}
}

Control::~Control() {

}

Vector2d Control::getCursorPos() {
	return mouse.pos;
}

void Control::loadConfig() {
	
}


void Control::saveConfig() {
	
}

void Control::step() {
	int timeMs = getMilliCount();
	if (timeMs - timePrev > dt) {
		timePrev = timeMs;

		
		events();
		drawSys.mouse = mouse;
		

		if (mouse.state && !mousePrev.state) {
			std::pair<int, int> pos = { mouse.pos.x, mouse.pos.y };
			int size = (int)drawSys.h / board.size;
			if (pos.first / size == board.pos.first && pos.second / size == board.pos.second) {
				pos.first %= (int)drawSys.w / board.size;
				pos.second %= (int)drawSys.h / board.size;
				pos.first /= (int)drawSys.w / board.size / board.size;
				pos.second /= (int)drawSys.h / board.size / board.size;
				board.step(pos);
			}
		}

		if (board.activePlayer == -1) {
			robot.type = 1;
			auto s = bot();
			drawSys.pos = {s.first + board.pos.first * board.size, s.second + board.pos.second*board.size };
			board.step(s);
		}

		drawSys.draw(board);
		drawSys.window->display();		
	}
}

std::pair<int, int> Control::bot() {
	return robot.step(board);
}
