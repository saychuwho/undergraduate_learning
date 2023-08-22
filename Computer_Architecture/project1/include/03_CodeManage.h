#ifndef CODEMANAGE
#define CODEMANAGE

#include <vector>
#include <map>
#include <string>

using namespace std;

extern const unsigned int TEXT_START_ADDR;
extern const unsigned int DATA_START_ADDR;

extern vector<string> data_hex_form;
extern vector<string> text_hex_form;
extern map<string, string> data_label_addr;
extern map<string, string> text_label_addr;

void DataLabeling(vector<vector<string>> data);

void TextLabeling(vector<vector<string>> text);

void DataSave(vector<vector<string>> data);

void InstrSave(vector<vector<string>> instr);

#endif