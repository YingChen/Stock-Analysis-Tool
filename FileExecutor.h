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

using namespace std;

class FileExecutor{
private:
    //string BaseFilePath = "/Users/larry/Documents/Stock/Stock/Stock/";
    string BaseUrl;
    
public:
    FileExecutor(){
        BaseUrl = "http://www.google.com/finance/historical?output=csv&q=";
    }
    
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
