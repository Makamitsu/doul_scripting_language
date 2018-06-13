#pragma once

#include <vector>

class entity
{
public:
	static std::vector<entity*> all_entities;

	entity();
	~entity();

	static void setLife(int16_t pid, int16_t plife);
	static int16_t getLife(int16_t pid);
	static void setDmg(int16_t pid, int16_t pdmg);
	static int16_t getDmg(int16_t pid);
	static std::string getInfo();
	int16_t id;
private:
	int16_t life;
	int16_t dmg;
	static int16_t id_incr;
};

