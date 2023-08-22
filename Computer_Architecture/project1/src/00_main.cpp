#include "01_DataManage.h"
#include "02_InstructionConvert.h"
#include "03_CodeManage.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char** argv){
    // 프로그램이 시작되면, 어셈블리 소스코드를 한줄씩 vector에 저장한다.
    // 받은 argument가 하나 이상이면 프로그램을 종료한다.
    if(argc != 2){
        cerr << "Error : Invalid argument number." << endl;
        exit(1);
    }
    // 어셈블리 소스코드를 연다.
    string assembly_FileName = argv[1];
    ifstream assembly_SourceCode(assembly_FileName);
    // 어셈블리 코드를 열 수 없다면, 프로그램을 종료한다.
    if(!assembly_SourceCode){
        cerr << "Error : Cannot open the file." << endl;
        exit(1);
    }

    // vector 속에 어셈블리 코드를 라인별로 집어넣는다.
    // 여기서 명령어들 속 요소들을 SplitLine 함수를 통해 분리해서 vector에 저장한다. 
    vector<vector<string>> assembly_codeline_data;
    vector<vector<string>> assembly_codeline_text;
    string templine;
    bool is_data = true;
    while(getline(assembly_SourceCode, templine)){
        if(templine == "") continue; // 아무것도 없는 빈 라인의 경우 여기에서 걸러진다.
        vector<string> temp_vector = SplitLine(templine, ' ');
        // 다음부터 들어오는 라인이 .data 아래에 있는지, .text 아래에 있는지 판별하는 곳.
        if(temp_vector.at(0) == ".data"){
            is_data = true;
            continue;
        }
        if(temp_vector.at(0) == ".text"){
            is_data = false;
            continue;
        }
        if(is_data)
            assembly_codeline_data.push_back(temp_vector);
        else   
            assembly_codeline_text.push_back(temp_vector);
    }
    // 어셈블리 소스코드를 닫는다.
    assembly_SourceCode.close();

    // 이 아래는 실제 최종 결과물에 들어가야 하는 코드다.
    // label들의 주소를 map에 저장한다.
    DataLabeling(assembly_codeline_data);
    TextLabeling(assembly_codeline_text);

    // 실제 코드를 번역해 vector에 라인별로 저장한다.
    DataSave(assembly_codeline_data);
    InstrSave(assembly_codeline_text);
    
    // binary file로 만들어서 내보내는 곳
    fstream output;
    // file 이름에 directory까지 들어가있어서, 지금 구현된 코드는 *.s 와 같은 위치에 .o가 생성된다.
    string output_FileName = assembly_FileName.substr(0, assembly_FileName.length()-2) + ".o";
    output.open(output_FileName, ios::out | ios::binary);
    
    if(output.is_open()){
        // text size가 먼저 와야 하고 data size가 나중에 와야 한다. 
        unsigned int temp_text_section_size = text_hex_form.size();
        temp_text_section_size *= 4;
        string text_section_size = DecimalToHex(temp_text_section_size);
        output.write(text_section_size.c_str(), text_section_size.size());
        output.write("\n", 1);
        unsigned int temp_data_section_size = data_hex_form.size();
        temp_data_section_size *= 4;
        string data_section_size = DecimalToHex(temp_data_section_size);
        output.write(data_section_size.c_str(), data_section_size.size());
        output.write("\n", 1);

        for(vector<string>::iterator i=text_hex_form.begin();i!=text_hex_form.end();i++){
            output.write((*i).c_str(), (*i).size());
            output.write("\n", 1);
        }
        for(vector<string>::iterator i=data_hex_form.begin();i!=data_hex_form.end();i++){
            output.write((*i).c_str(), (*i).size());
            output.write("\n", 1);
        }
    }
    output.close();
}