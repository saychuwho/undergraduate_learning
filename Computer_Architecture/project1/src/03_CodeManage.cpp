#include "01_DataManage.h"
#include "02_InstructionConvert.h"
#include "03_CodeManage.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>


const unsigned int TEXT_START_ADDR = 0x00400000;
const unsigned int DATA_START_ADDR = 0x10000000;

vector<string> data_hex_form;
vector<string> text_hex_form;

void DataLabeling(vector<vector<string>> data){
    unsigned int label_pos = 0;
    for(unsigned int i=0;i<data.size();i++){
        if(StrHaveChar(data.at(i).at(0),':')){
            unsigned int temp_addr = DATA_START_ADDR + 4*label_pos;
            data_label_addr[data.at(i).at(0).substr(0,data.at(i).at(0).length()-1)] = DecimalToHex(temp_addr);
        }
        if(data.at(i).size() != 1)
            label_pos += 1;
    }
}

// TextLabeling 과정에서 la의 크기에 따라서 label_pos를 메기자. la를 치환하는거는 InstrSave에서 처리하고
void TextLabeling(vector<vector<string>> text){
    unsigned int label_pos = 0;
    for(unsigned int i=0;i<text.size();i++){
        // label들에 주소를 매칭시키는 부분
        if(StrHaveChar(text.at(i).at(0),':')){
            unsigned int temp_addr = TEXT_START_ADDR + 4*label_pos;
            text_label_addr[text.at(i).at(0).substr(0,text.at(i).at(0).length()-1)] = DecimalToHex(temp_addr);
        }
        // la 명령어가 있을 때 이 명령어가 두개로 나눠지는지 하나로 나눠지는지 여부에 따라서 label_pos에 1을 더하거나 안더한다.
        else if((text.at(i).at(0) == "la") || (text.at(i).at(1) == "la")){
            unsigned int temp_index = 2;
            if(text.at(i).at(1) == "la")
                temp_index += 1;
            if(stoul(data_label_addr[text.at(i).at(temp_index)].substr(data_label_addr[text.at(i).at(temp_index)].length()-4,4), nullptr, 16) != 0x0000)
                label_pos += 1;
        }
        // label 말고도 instruction이 있어야 다음 순서로 넘어간다.
        if(text.at(i).size() != 1)
            label_pos += 1;
    }
}

void DataSave(vector<vector<string>> data){
    for(unsigned int i=0;i<data.size();i++){
        if(data.at(i).at(0) == ".word")
            data_hex_form.push_back(DecimalToHex(stoul(data.at(i).at(1),nullptr, 0)));
        if(data.at(i).at(0) != ".word" && data.at(i).at(1) == ".word")
            data_hex_form.push_back(DecimalToHex(stoul(data.at(i).at(2),nullptr, 0)));
    }
}

// 이 함수는 반드시 label 함수가 실행되고 나서 실행되어야 한다.
void InstrSave(vector<vector<string>> instr){
    // 현재 Instruction의 주소 : PC = TEXT_SATART_ADDR + currentAddrCounter * 4
    unsigned int PC = TEXT_START_ADDR-4;
    for(unsigned int i=0;i<instr.size();i++){
        vector<string> temp_vector; // label들이 실제 값을 가지도록 변환되는 곳
        unsigned int j_start = 0;
        // 보낼 PC를 초기화한다.
        // instruction line의 상태에 따라 temo_vector를 결정하는 곳
        // label만 있는 경우
        if(StrHaveChar(instr.at(i).at(0),':') && instr.at(i).size() == 1){
            continue;
        }
        // label 뒤에 명령어가 있는 경우
        else if(StrHaveChar(instr.at(i).at(0),':') && instr.at(i).size() != 1){
            j_start = 1;
        }
        // label이 없는 경우
        else{
            j_start = 0;
        }
        // Instruction을 해석하니 PC를 증가
        PC += 4;
        // temp_vector에 값을 집어넣다가 label이 나오면 이에 해당하는 주소로 치환한다. 
        for(unsigned int j=j_start;j<instr.at(i).size();j++){
            if (text_label_addr.find(instr.at(i).at(j)) != text_label_addr.end())
                temp_vector.push_back(text_label_addr[instr.at(i).at(j)]);
            else if (data_label_addr.find(instr.at(i).at(j)) != data_label_addr.end()){
                temp_vector.push_back(data_label_addr[instr.at(i).at(j)]);
            }
            else 
                temp_vector.push_back(instr.at(i).at(j));
        }
        // la instruction을 실제 instruction으로 바꾸어서 InstrConvert_Control에 넣는 곳.
        if(temp_vector.at(0) == "la"){
            vector<string> la_lui = {"lui", temp_vector.at(1), temp_vector.at(2).substr(0, temp_vector.at(2).length()-4)};
            vector<string> la_ori = {"ori", temp_vector.at(1), temp_vector.at(1), "0x" + temp_vector.at(2).substr(temp_vector.at(2).length()-4, 4)};
            text_hex_form.push_back(InstrConvert_Control(la_lui, PC));
            if (stoul(la_ori.at(3), nullptr, 16) != 0x0000){
                //명령어가 한번 더 실행되니 PC를 증가시킨 후 집어넣는다.
                PC += 4;
                text_hex_form.push_back(InstrConvert_Control(la_ori, PC));
            }
        }
        else
            text_hex_form.push_back(InstrConvert_Control(temp_vector, PC));
        
    }
}

