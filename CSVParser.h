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

/**
 This object reads and parses a csv file representing the historical prices of a stock
 */
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
    
    //Return the specific element in the table
    //Represent by the row and column number
    string getElement(int row, int col){
        CSVRow* currentRow = myRows[row];
        return currentRow->getData(col);
    }
    
    //Return the number of rows in the csv file
    int getRowCount(){
        return (int) myRows.size();
    }
    
};



#endif
