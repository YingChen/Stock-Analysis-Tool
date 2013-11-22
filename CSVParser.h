//
//  CSVParser.h
//  Stock
//
// 
//
//

#ifndef Stock_CSVParser_h
#define Stock_CSVParser_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "CSVRow.h"

using namespace std;

class CSVParser{
private:
    vector<CSVRow*> myRows;
    
    void readFile(string filePath){

        ifstream file(filePath.c_str());
        string str;
        if (!file.is_open()){
            perror("error while opening file");
        }
 
        //Get rid of the first row
        getline(file,str);
        
        while(getline(file,str)){
            //cout<<"line from file is "<<str<<endl;
            CSVRow* newRow = new CSVRow(str);
            myRows.push_back(newRow);
        }
    }
    

public:
    CSVParser(string filePath){
        readFile(filePath);
    }
    
    string getElement(int row, int col){
        CSVRow* currentRow = myRows[row];
        return currentRow->getData(col);
    }
    
    int getRowCount(){
        return (int) myRows.size();
    }
    
};



#endif
