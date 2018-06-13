#include "entity.h"
#include "vm.h"

#include <iostream>
#include <string>

vm::vm()
{
}

vm::~vm()
{
}

std::string vm::getCodeValue(int16_t code) {
	switch (code) {
	case START: return std::string("start");  break;
	case PUSH:  return std::string("push");	  break;
	case JMPIF: return std::string("jumpif"); break;
	case JMPZ:  return std::string("jmpz");   break;
	case COMP:  return std::string("comp");	  break;
	case NOT:	return std::string("not");	  break;
	case AND:	return std::string("and");	  break;
	case OR:	return std::string("or");	  break;
	case XOR:	return std::string("xor");	  break;
	case GRT:	return std::string("grt");	  break;
	case ADD:	return std::string("add");	  break;
	case SUB:	return std::string("sub");	  break;
	case MUL:	return std::string("mul");	  break;
	case DIV:	return std::string("div");	  break;
	case GLIFE: return std::string("glife");  break;
	case SLIFE: return std::string("slife");  break;
	case GDMG:	return std::string("gdmg");	  break;
	case SDMG:	return std::string("sdmg");	  break;
	case END:	return std::string("end");	  break;
	}
}

void vm::flush()
{
	while (stack.size() > 0)stack.pop();
}

void vm::execute(Doul program, bool verbose)
{
	flush();

	bool started = false;
	int16_t a, b;
	int16_t* curr = program.prog;
	if (!curr) return;

	if (verbose)std::cout << "Start interpreter:\n";

	if (program.pre_load_stack.size() > 0) {
		if (verbose)std::cout << " preload stack:";
		std::stack<int16_t> order_stack(program.pre_load_stack);
		std::stack<int16_t> reverse_stack;
		int size = order_stack.size();
		for (int i = 0; i < size; ++i) {
			reverse_stack.push(order_stack.top());
			order_stack.pop();
		}
		for (int i = 0; i < size; ++i) {
			push(reverse_stack.top());

			if (verbose)std::cout << " " << reverse_stack.top();

			reverse_stack.pop();
		}
		if (verbose) std::cout << "\n;";
	}
	else 
		if (verbose)std::cout << " No preload stack\n";


	for(int i = 0; i < program.nb; ++i) {

		if (verbose) std::cout << " inst: " << std::to_string(i) << "->" << getCodeValue(*curr) << std::dec << "\n";
		
		if (*curr == START)
			started = true;

		if(started)
			switch(*curr) {
			case PUSH: push(*++curr); ++i; break;
			case JMPIF: if (pop())while(*++curr != JMPZ) ++i;
			case COMP: a = pop(); b = pop(); push(a == b); break;
			case NOT: a = pop(); push( a == 0x00 ? 0x01 : 0x00 ); break;
			case AND: a = pop(); b = pop(); push( a!=0x00 && b!=0x00 ? 0x01 : 0x00 ); break;
			case OR: a = pop(); b = pop(); push( a != 0x00 || b != 0x00 ? 0x01 : 0x00 ); break;
			case XOR: a = pop(); b = pop(); push(a != 0x00 && b == 0x00 || b != 0x00 && a == 0x00 ? 0x01 : 0x00); break;
			case GRT: a = pop(); b = pop(); push( a > b ? 0x01 : 0x00); break;
			case ADD: a = pop(); b = pop(); push(b + a); break;
			case SUB: a = pop(); b = pop(); push(b - a); break;
			case MUL: a = pop(); b = pop(); push(b * a); break;
			case DIV: a = pop(); b = pop(); push(b / a); break;
			case GLIFE: a = pop(); push(entity::getLife(a)); break;
			case SLIFE: a = pop(); b = pop(); entity::setLife(b, a); break;
			case GDMG: a = pop(); push(entity::getDmg(a)); break;
			case SDMG: a = pop(); b = pop(); entity::setDmg(b, a); break;
			case END: return;
			}

		if (verbose) {
			std::cout << "   stack:";
			std::stack<int16_t> temp; int size = stack.size();
			for (int debug = 0; debug<size; ++debug) { int16_t a = pop(); temp.push(a);}
			for (int debug = 0; debug<size; ++debug) { int16_t a = temp.top(); temp.pop(); push(a); std::cout << " " << int(a);
			}
			std::cout << "\n";
		}

		++curr;
	}
}

int16_t vm::getTop()
{
	_ASSERT_EXPR( stack.size() > 0,L"Calling TOP on empty stack");
	return stack.top();
}


std::string vm::getProgramString(Doul program)
{
	std::string s;
	bool started = false;
	int16_t* curr = program.prog;
	for (int i = 0; i < program.nb; ++i,++curr) {
		if (*curr == PUSH) {
			s += "[" + getCodeValue(*curr);
			s += ":" + int(*++curr);
			s += "]";
			++i;
		}
		else
			s += "[" + getCodeValue(*curr)+"]";
	}
	s += "\n";
	return s;
}


int16_t vm::pop()
{
	if (stack.size() == 0) {
		__debugbreak();
	};
	int16_t a = stack.top();
	stack.pop();
	return a;
}

void vm::push(int16_t a)
{
	stack.push(a);
}
