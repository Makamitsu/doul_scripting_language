#include <iostream>
#include <string>

#include "entity.h"
#include "vm.h"

#define DOUL(x) doul[sh++] = x

struct doul {
	char nb;
	char* prog;
};


doul DOUL_attack(entity attacker, entity defenser) {
	doul p{0, new char[255]};
	p.prog[p.nb++] = START;
	p.prog[p.nb++] = PUSH;
	p.prog[p.nb++] = defenser.id;
	p.prog[p.nb++] = PUSH;
	p.prog[p.nb++] = defenser.id;
	p.prog[p.nb++] = GLIFE;
	p.prog[p.nb++] = PUSH;
	p.prog[p.nb++] = attacker.id;
	p.prog[p.nb++] = GDMG;
	p.prog[p.nb++] = SUB;
	p.prog[p.nb++] = SLIFE;
	p.prog[p.nb++] = END;
	return p;
}

doul DOUL_isDead(entity e) {
	doul p{ 0, new char[255] };
	p.prog[p.nb++] = START;
	p.prog[p.nb++] = PUSH;
	p.prog[p.nb++] = e.id;
	p.prog[p.nb++] = GLIFE;
	p.prog[p.nb++] = PUSH;
	p.prog[p.nb++] = 0;
	p.prog[p.nb++] = GRT;
	p.prog[p.nb++] = END;
	return p;
}

int main() {
	std::cout << "Start!\n";

	vm VirtualMachine;


	entity player;
	entity ennemy;

	doul programAtk = DOUL_attack(player, ennemy);
	doul testIfDead = DOUL_isDead(ennemy);
	
	do {
		entity::print();
		std::cout << "player attacks ennemy" << "\n";
		VirtualMachine.run(programAtk.prog, programAtk.nb, false);
		VirtualMachine.run(testIfDead.prog, testIfDead.nb, false);
		std::cout << "is ennemy dead? " << bool(VirtualMachine.getTop()) << "\n";
		std::cin.get();
	} while (!VirtualMachine.getTop());

}