//
//  FileExecutor.h
//  Stock
//
//  
//
//

#ifndef Stock_FileExecutor_h
#define Stock_FileExecutor_h

#include <string>
#include <iostream>
#include <stdio.h>

#include "Settings.h"

using namespace std;

/**
 This class helps to download a csv file from the target url
 */
class FileExecutor{
private:
    string BaseUrl;
    
public:
    FileExecutor(Settings* settings){
        BaseUrl = settings->getBaseurl();
    }
    
    //Download the file with script command
    string downloadFile(string symbol){
        string url = BaseUrl;
        url.append(symbol);
        string fileName = symbol;
        fileName.append(".csv");
        
        string command = "curl -o ";
        command.append(fileName.c_str());
        command.append(" '");
        command.append(url.c_str());
        command.append("'");
        cout<<"command is "<<command<<endl;
        
        system(command.c_str());
        
        return fileName;
    }

};

#endif
