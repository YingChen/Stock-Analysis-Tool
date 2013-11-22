//
//  Stock.h
//  Stock
//
//  
//
//

#ifndef Stock_Stock_h
#define Stock_Stock_h

#include <iostream>
#include <string>
#include <vector>

#include "SingleDayStock.h"
#include "CSVParser.h"

using namespace std;

class Stock{
private:
    string name;
    vector<SingleDayStock*> history;
    CSVParser* myParser;
    
    void createHistory(){
        int numberOfDays = myParser->getRowCount();
        for (int i=0; i<numberOfDays; i++) {
            history.push_back(new SingleDayStock(name,myParser,i));
        }
    }
    
public:
    Stock(string name , string filePath){
        this->name = name;
        myParser = new CSVParser(filePath);
        createHistory();
    }
    
    void printInfo(){
        cout<<"********************"<<endl;
        cout<<name<<endl;
        for(int j=0; j<history.size(); j++){
            cout<<history[j]->toString();
        }
        cout<<"********************"<<endl;

    }
    
    string getName(){
        return name;
    }
    
    vector<double> getPriceTable(){
        vector<double> table;
        for(int i=0; i<history.size(); i++){
            table.push_back(history[i]->getClosePrice());
        }
        return table;
        
    }
    
    
};


#endif
