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
#include "Time.h"
#include "Pair.h"

using namespace std;

/**
 This class contains all the information of one stock
 */
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
    
    //Split a string by 'token'
    vector<string> split(string input, const char token){
        string str;
        vector<string> result;
        istringstream iss(input);
        while (getline(iss,str,token)) {
            result.push_back(str);
        }
        return result;
    }
    
    Time* parseTime(string input){
        vector<string> splittedDateInfo = split(input, '-');
        int month = atoi(splittedDateInfo[0].c_str());
        int day = atoi(splittedDateInfo[1].c_str());
        int year = atoi(splittedDateInfo[2].c_str());
        Time* date = new Time(year,month,day);
        return date;
    }

public:
    Stock(string name , string filePath){
        this->name = name;
        myParser = new CSVParser(filePath);
        createHistory();
    }
    
    //Get the last day time
    Time* getLastTimeInHistory(){
        //int len = (int) history.size();
        return history[0]->getTime();
    }
    
    //Print all the information of the current stock
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
    
    //Return the vector representing the historical prices of the stock
    vector<double> getPriceTable(){
        vector<double> table;
        for(int i=0; i<history.size(); i++){
            table.push_back(history[i]->getClosePrice());
        }
        return table;
    }
    
    //The format of the date should be like mm-dd-yy
    //For example: 1-4-14
    //If no such date is found, then return -1.
    double getPriceOfTheDay(string dateInfo){
        Time* date = parseTime(dateInfo);
        
        for(int i=0; i<history.size(); i++){
                if(history[i]->getTime()->equalTo(date))
                    return history[i]->getClosePrice();
        }
        return -1;
    }
    
    double getVolumeOfTheDay(string dateInfo){
        Time* date = parseTime(dateInfo);
        
        for(int i=0; i<history.size(); i++){
            if(history[i]->getTime()->equalTo(date))
                return history[i]->getVolume();
        }
        return -1;
    }
    
    double getOpenPriceOfTheDay(string dateInfo){
        Time* date = parseTime(dateInfo);
        
        for(int i=0; i<history.size(); i++){
            if(history[i]->getTime()->equalTo(date))
                return history[i]->getOpenPrice();
        }
        return -1;
    }
    
    double getClosePriceOfTheDay(string dateInfo){
        Time* date = parseTime(dateInfo);
        
        for(int i=0; i<history.size(); i++){
            if(history[i]->getTime()->equalTo(date))
                return history[i]->getClosePrice();
        }
        return -1;
    }
    
    double getHighPriceOfTheDay(string dateInfo){
        Time* date = parseTime(dateInfo);
        
        for(int i=0; i<history.size(); i++){
            if(history[i]->getTime()->equalTo(date))
                return history[i]->getHighPrice();
        }
        return -1;
    }
    
    double getLowPriceOfTheDay(string dateInfo){
        Time* date = parseTime(dateInfo);
        
        for(int i=0; i<history.size(); i++){
            if(history[i]->getTime()->equalTo(date))
                return history[i]->getLowPrice();
        }
        return -1;
    }
    
    
    vector<Pair*> getStockHistory(){
        vector<Pair*> result;
        for(int i=0; i<history.size(); i++){
            SingleDayStock* singleDayStock = history[i];
            result.push_back(new Pair(singleDayStock->getTime(), singleDayStock->getClosePrice()));
        }
        return result;
    }
};


#endif
