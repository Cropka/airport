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

    for(unsigned int i=0;i<words.size();++i){
        if(keyword2arg(words[i])){//if command is a one that needs 2 args
            emitSignal(words[i], words[i+1]);
            i+=1;
        }
        else if(keyword3arg(words[i])){//if command is a one that needs 3 args
            emitSignal(words[i], words[i+1], words[i+2]);
            i+=2;
        }
        else{
            i+=1;
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

void ConfigParser::emitSignal(std::string _indicator, std::string _place, std::string _priority){
    int place = std::stoi(_place);
    int priority = std::stoi(_priority);
    //{"postalplane", "passengerplane", "rampstairs", "bus", "gateway", "runway"}
    if(_indicator=="postalplane"){
        emit createPostalPlane(place, priority);
    }
    else if(_indicator=="passengerplane"){
        emit createPassangerPlane(place, priority);
    }
    else if(_indicator=="rampstairs"){
        emit createRampstairs(place, priority);
    }
    else if(_indicator=="bus"){
        emit createBus(place, priority);
    }
    else if(_indicator=="gateway"){
        emit createGateway(place);
    }
    else if(_indicator=="runway"){
        emit createRunway(place);
    }
    else{
        std::cerr<<"Error: the programmer forgot to add "<<_indicator<<"command to ConfigParser::emitSignal function"<<std::endl;
    }
}

bool ConfigParser::keyword2arg(std::string keyword){
    for(std::string key : keywords2){
        if(key==keyword){
            return true;
        }
    }
    return false;
}

bool ConfigParser::keyword3arg(std::string keyword){
    for(std::string key : keywords3){
        if(key==keyword){
            return true;
        }
    }
    return false;
}
