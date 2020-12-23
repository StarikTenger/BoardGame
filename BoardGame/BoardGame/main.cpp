#include "Control.h"
#include "Evolution.h"
#include <iostream>

int main(int, char**){
	random::start();
	
	// This code is for game
	Control control;
	while (!control.stop) {
		control.step();
	}

	// This code is for evolution
	//Evolution ev;
	/*std::cout << ev.comp(
		{80, 80, 80, 10, 10 ,10 },
		{100,  100,  100,  10, 10, 10 }
	);*/
	//ev.generate();
	return 0;
}