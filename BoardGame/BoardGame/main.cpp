#include "Control.h"
#include "Evolution.h"
#include <iostream>

int main(int, char**){
	random::start();
	
	Control control;
	while (!control.stop) {
		control.step();
	}

	/*Evolution ev;
	std::cout << ev.comp(
		{ 1000, 1010, 1020, 10, 11 ,12 },
		{100, 100, 100, 10, 10, 10 }
	);
	ev.generate();*/
	return 0;
}