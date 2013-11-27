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

/**
 This class represents a row of information in the csv file
 */
class CSVRow{
private:
    vector<string> myData;
    
    //Remove all the spaces in the front of /behind a string
    string trim(string& str){
        str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
        str.erase(str.find_last_not_of(' ')+1);         //surfixing spaces
        return trimQuote(str);
    }
    
    //Remove the quotes of a string
    string trimQuote(string& str){
        str.erase(0, str.find_first_not_of('"'));       //prefixing spaces
        str.erase(str.find_last_not_of('"')+1);         //surfixing spaces
        return str;

    }
    
    //Parse a row in the csv file
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
    
    //Get the specific element in the row
    string getData(int index){
        return myData[index];
    }
    
    //Get the number of elements in the row
    int getColCount(){
        return (int) myData.size();
    }
    
    
};

#endif
