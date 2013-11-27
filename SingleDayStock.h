//
//  SingleDayStock.h
//  Stock
//
//  
//
//

#ifndef Stock_SingleDayStock_h
#define Stock_SingleDayStock_h

#include <iostream>
#include <string>
#include <vector>

#include "Time.h"
#include "CSVParser.h"

using namespace std;


/**
 This object represents the single-day price of one specific stock
 */
class SingleDayStock{
private:
    string stockName;
    Time* time;
    double openPrice;
    double closePrice;
    double highPrice;
    double lowPrice;
    long volume;
    

public:
    SingleDayStock(string name, CSVParser* parser, int row){
        this->stockName = name;
        this->time = new Time(parser->getElement(row,0));
        this->openPrice = atof(parser->getElement(row,1).c_str());
        this->highPrice = atof(parser->getElement(row,2).c_str());
        this->lowPrice = atof(parser->getElement(row,3).c_str());
        this->closePrice = atof(parser->getElement(row,4).c_str());
        this->volume = atol(parser->getElement(row,5).c_str());
    }
    
    Time* getTime(){
        return this->time;
    }
    
    double getOpenPrice(){
        return this->openPrice;
    }
    
    double getClosePrice(){
        return this->closePrice;
    }
    
    double getHighPrice(){
        return this->highPrice;
    }
    
    double getLowPrice(){
        return this->lowPrice;
    }
    
    long getVolume(){
        return this->volume;
    }
    
    string toString(){
        string result = this->time->toString();
        result.append(" ");
        result.append(to_string(this->openPrice));
        result.append(" ");
        result.append(to_string(this->closePrice));
        result.append(" ");
        result.append(to_string(this->highPrice));
        result.append(" ");
        result.append(to_string(this->lowPrice));
        result.append(" ");
        result.append(to_string(this->volume));
        result.append("\n");
        return result;
    }
};




#endif
