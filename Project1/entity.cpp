#include "entity.h"

#include <iostream>
#include <string>
#include <vector>

int16_t entity::id_incr = 0;

std::vector<entity*> entity::all_entities;

entity::entity():id(++id_incr),life(10),dmg(2)
{
	all_entities.push_back(this);
}

entity::~entity()
{
}

void entity::setLife(int16_t pid, int16_t plife)
{
	for (auto ent : all_entities)
		if (ent->id == pid) {
			ent->life = plife;
			return;
		}
}

int16_t entity::getLife(int16_t pid)
{
	for (auto ent : all_entities)
		if (ent->id == pid)
			return ent->life;
	return -1;
}

void entity::setDmg(int16_t pid, int16_t pdmg)
{
	for (auto ent : all_entities)
		if (ent->id == pid) {
			ent->dmg = pdmg;
			return;
		}
}

int16_t entity::getDmg(int16_t pid)
{
	for (auto ent : all_entities)
		if (ent->id == pid)
			return ent->dmg;
	return -1;
}

std::string entity::getInfo()
{
	std::string s;
	s += "List of entities:\n";
	for (entity* e : all_entities) {
		s += "  - id:";
		s += std::to_string(e->id);
		s += " life:";
		s += std::to_string(e->life);
		s += "\n";
	}
	return s;
}
