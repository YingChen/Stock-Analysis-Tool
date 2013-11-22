//
//  CSVRow.h
//  Stock
//
//  
//
//

#ifndef Stock_CSVRow_h
#define Stock_CSVRow_h

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class CSVRow{
private:
    vector<string> myData;
    
    string trim(string& str){
        str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
        str.erase(str.find_last_not_of(' ')+1);         //surfixing spaces
        return trimQuote(str);
    }
    
    string trimQuote(string& str){
        str.erase(0, str.find_first_not_of('"'));       //prefixing spaces
        str.erase(str.find_last_not_of('"')+1);         //surfixing spaces
        return str;

    }
    
    void parseRow(string line){
        istringstream ss(line);
        string token;
        
        while(getline(ss, token, ',')) {
            myData.push_back(trim(token));
        }
    }
    
public:
    CSVRow(string line){
        init(line);
    }
    
    void init(string line){
        parseRow(line);
    }
    
    
    string getData(int index){
        return myData[index];
    }
    
    int getColCount(){
        return (int) myData.size();
    }
    
    
};

#endif
