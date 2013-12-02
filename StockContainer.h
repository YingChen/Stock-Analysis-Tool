//
//  StockContainer.h
//  Stock
//
//  
//
//

#ifndef Stock_StockContainer_h
#define Stock_StockContainer_h

#include <vector>
#include "Stock.h"
#include "Pair.h"

using namespace std;

/**
 This is the class that constantly stores all the parsed stock information
 */
class StockContainer{
private:
    vector<Stock*> stocks;

public:
    //Add a stock object
    void saveStock(Stock* input){
        stocks.push_back(input);
    }
    
    //Get the stock object according to its stock symbol
    Stock* getStock(string symbol){
        for (int i=0; i<stocks.size(); i++) {
            if(stocks[i]->getName().compare(symbol) == 0)
                return stocks[i];
        }
        return NULL;
    }
    
    //Remove a stock object
    //The stock is specified by its stock symbol
    void removeStock(string symbol){
        for(int i=0; i< stocks.size(); i++){
            if(stocks[i]->getName().compare(symbol) == 0){
                stocks.erase(stocks.begin() + i);
                return;
            }
        }
        cout<<"Unable to delete the stock "<<symbol<<" Could not find it in the stock container"<<endl;
    }
    
    //Print all the stocks
    void printAllStocks(){
        for(int i=0; i<stocks.size(); i++){
            stocks[i]->printInfo();
            cout<<"###################"<<endl;
        }
    }
    
    //Return a vector where each item is the close price in history
    vector<double> getPriceTable(string symbol){
        vector<double> emptyResult;
        Stock* stock = this->getStock(symbol);
        if(stock != NULL){
            return stock->getPriceTable();
        }
        else
            return emptyResult;
    }
    
    //The date should be in mm-dd-yy format
    //Like 1-4-2013
    //If either the symbol or date is invalid, then return -1
    double getPriceOfDay(string symbol, string date){
        Stock* stock = this->getStock(symbol);
        if(stock != NULL)
            return stock->getPriceOfTheDay(date);
        return -1;
    }
    
    double getVolumnOfDay(string symbol, string date){
        Stock* stock = this->getStock(symbol);
        if(stock != NULL)
            return stock->getVolumeOfTheDay(date);
        return -1;
    }
    
    double getOpenPriceOfDay(string symbol, string date){
        Stock* stock = this->getStock(symbol);
        if(stock != NULL)
            return stock->getOpenPriceOfTheDay(date);
        return -1;
    }
    
    double getClosePriceOfDay(string symbol, string date){
        Stock* stock = this->getStock(symbol);
        if(stock != NULL)
            return stock->getClosePriceOfTheDay(date);
        return -1;
    }
    
    double getHighPriceOfDay(string symbol, string date){
        Stock* stock = this->getStock(symbol);
        if(stock != NULL)
            return stock->getHighPriceOfTheDay(date);
        return -1;
    }
    
    double getLowPriceOfDay(string symbol, string date){
        Stock* stock = this->getStock(symbol);
        if(stock != NULL)
            return stock->getLowPriceOfTheDay(date);
        return -1;
    }

    vector<Pair*> getStockHistory(string symbol){
        Stock* stock = this->getStock(symbol);
        return stock->getStockHistory();
    }
    
};

#endif
