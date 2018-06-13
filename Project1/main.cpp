#include <iostream>
#include <string>

#include "entity.h"
#include "vm.h"
#include "doul.h"




int main() {
	std::cout << "Start!\n";

	vm VirtualMachine;
	
	entity player;
	entity ennemy;

	Doul programAtk,testIfDead;
	programAtk[START][PUSH][player.id][PUSH][player.id][GLIFE][PUSH][ennemy.id][GDMG][SUB][SLIFE][END];
	testIfDead[START][PUSH][0][PUSH][player.id][GRT][END];

	VirtualMachine.execute(programAtk, true);

	std::cin.get();
}