#pragma once

#include <iostream>
#include <stack>

struct Doul {
	int16_t nb;
	int16_t* prog;

	Doul();
	Doul& operator[](int16_t nb);
	std::stack<int16_t> pre_load_stack;

};