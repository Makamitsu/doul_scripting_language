#include "entity.h"
#include <vector>
#include <iostream>
#include <string>

char entity::id_incr = 0;

std::vector<entity*> entity::all_entities;

entity::entity():id(++id_incr),life(10),dmg(2)
{
	all_entities.push_back(this);
}

entity::~entity()
{
}

void entity::setLife(char pid, char plife)
{
	for (auto ent : all_entities)
		if (ent->id == pid) {
			ent->life = plife;
			return;
		}
}

char entity::getLife(char pid)
{
	for (auto ent : all_entities)
		if (ent->id == pid)
			return ent->life;
	return -1;
}

void entity::setDmg(char pid, char pdmg)
{
	for (auto ent : all_entities)
		if (ent->id == pid) {
			ent->dmg = pdmg;
			return;
		}
}

char entity::getDmg(char pid)
{
	for (auto ent : all_entities)
		if (ent->id == pid)
			return ent->dmg;
	return -1;
}

void entity::print()
{
	std::cout << "List of entities:\n";
	for (entity* e : all_entities) {
		std::cout << "  - " << int(e->id) << " life:"<< int(e->life) <<"\n";
	}
}
