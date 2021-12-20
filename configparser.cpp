#include "configparser.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>

ConfigParser::ConfigParser(Airport *_airport, QObject *parent) : QObject(parent){
    airport=_airport;
}

bool ConfigParser::readObjects(std::string filename){
    std::istringstream iStream;
    std::string Line;

    if(!preprocess(iStream, filename))
        return false;

    size_t start = 0;
    std::string fromStream(iStream.str());
    while ((start = fromStream.find("\n", start)) != std::string::npos) {
        fromStream.replace(start, strlen("\n"), " ");
    }
    iStream.str(fromStream);

    std::vector<std::string> words;

    while (std::getline(iStream, Line, ' ')){
        words.push_back(Line);
    }
    bool found;

    for(unsigned int i=0;i<words.size();++i){
        if(i%3==0){
            found=false;
            for(std::string keyword : keywords){
                if(words[i]==keyword) {
                    emitSignal(keyword);
                    found=true;
                }
            }
            if(found==false){
                  std::cerr<<"Config error: No such command: \""<<words[i]<<"\", file "<<filename<<std::endl;
            }

        }
    }
    return true;
}

bool ConfigParser::preprocess(std::istringstream& _iStream, std::string _filename){
    std::string preprocessed = "cpp -P ";
    char Line[LINE_SIZE];
    std::ostringstream oTmpStrm;
    preprocessed += _filename;
    FILE* pProc = popen(preprocessed.c_str(),"r");

    if (!pProc) return false;

    while (fgets(Line,LINE_SIZE,pProc)) {
        oTmpStrm << Line;
    }

    _iStream.str(oTmpStrm.str());
    return pclose(pProc) == 0;
}

void ConfigParser::emitSignal(std::string _indicator){
    //{"postalplane", "passengerplane", "rampstairs", "bus", "gateway", "runway"}
    if(_indicator=="postalplane"){
        emit createPostalPlane();
    }
    else if(_indicator=="passengerplane"){
        emit createPassangerPlane();
    }
    else if(_indicator=="rampstairs"){
        emit createRampstairs();
    }
    else if(_indicator=="bus"){
        emit createBus();
    }
    else if(_indicator=="gateway"){
        emit createGateway();
    }
    else if(_indicator=="runway"){
        emit createRunway();
    }
    else{
        std::cerr<<"Error: the programmer forget to add "<<_indicator<<"command to ConfigParser::emitSignal function"<<std::endl;
    }
}