#pragma once

#include <vector>

class entity
{
public:
	static std::vector<entity*> all_entities;

	entity();
	~entity();

	static void setLife(char pid, char plife);
	static char getLife(char pid);
	static void setDmg(char pid, char pdmg);
	static char getDmg(char pid);
	static void print();
	char id;
private:
	char life;
	char dmg;
	static char id_incr;
};

