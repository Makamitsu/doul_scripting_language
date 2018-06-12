#include "vm.h"
#include <iostream>
#include <string>
#include "entity.h"
vm::vm()
{
}

vm::~vm()
{
}

std::string getCodeValue(char code) {
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
void vm::run(char* cmd, char nb, bool verbose)
{
	bool started = false;
	char a, b;
	char* curr = cmd;
	if (!curr) return;

	if (verbose)std::cout << "Start interpreter:\n";

	for(int i = 0;i < nb;++i) {

		if (verbose) std::cout << " inst: " << i << "->" << getCodeValue(*curr) << std::dec << "\n";
		
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
			case ADD:  a = pop(); b = pop(); push(b + a); break;
			case SUB:  a = pop(); b = pop(); push(b - a); break;
			case MUL:  a = pop(); b = pop(); push(b * a); break;
			case DIV:  a = pop(); b = pop(); push(b / a); break;
			case GLIFE: a = pop(); push(entity::getLife(a)); break;
			case SLIFE: a = pop(); b = pop(); entity::setLife(b, a); break;
			case GDMG: a = pop(); push(entity::getDmg(a)); break;
			case SDMG: a = pop(); b = pop(); entity::setDmg(b, a); break;
			case END: return;
			}


		if (verbose) {
			std::cout << "   stack:";
			std::stack<char> temp; int size = stack.size();
			for (int debug = 0; debug<size; ++debug) { char a = pop(); temp.push(a);}
			for (int debug = 0; debug<size; ++debug) { char a = temp.top(); temp.pop(); push(a); std::cout << " " << int(a);
			}
			std::cout << "\n";
		}

		++curr;
	}
}

char vm::getTop()
{
	return stack.top();
}


std::string vm::printProgram(char * p, int size)
{
	std::string s;
	bool started = false;
	char* curr = p;
	for (int i = 0; i < size; ++i,++curr) {
		if (*curr == PUSH) {
			s += "[" + getCodeValue(*curr);
			s += ":" + int(*++curr);
			s += "]";
			++i;
		}
		else
			s += "[" + getCodeValue(*curr)+"]";
	}
	return s;
}


inline char vm::pop()
{
	if (stack.size() == 0) {
		__debugbreak();
	};
	char a = stack.top();
	stack.pop();
	return a;
}

inline void vm::push(char a)
{
	stack.push(a);
}
