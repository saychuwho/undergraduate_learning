#ifndef DOINSTR
#define DOINSTR

#include <string>

using namespace std;

void doInstr_R(string rs, string rt, string rd, string shamt, string funct);

void doInstr_I(string op, string rs, string rt, string immOffset);

void doInstr_J(string op, string target);

#endif