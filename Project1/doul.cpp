#include "doul.h"

Doul::Doul():nb(0),prog(new int16_t[sizeof(int16_t)] )
{}

Doul& Doul::operator[](int16_t cmd)
{
	prog[nb++] = cmd;
	return *this;
}
