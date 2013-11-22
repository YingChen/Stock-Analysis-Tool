//
//  StockCenter.h
//  Stock
//
//  
//
//

#ifndef Stock_StockCenter_h
#define Stock_StockCenter_h

#include <iostream>
#include <string>
#include <string.h>
#include <vector>

#include "FileExecutor.h"
#include "LookUpTable.h"
#include "StockContainer.h"
#include "PriceEstimator.h"

using namespace std;

class StockCenter{
private:
    LookUpTable* table;
    FileExecutor* fileExecutor;
    StockContainer* container;
    PriceEstimator* estimator;
    
public:
    StockCenter(){
        table = new LookUpTable();
        fileExecutor = new FileExecutor();
        container = new StockContainer();
        estimator = new PriceEstimator(container);
    }
    
    //Get the valid stock symbol from the user input
    //Here implicit search is applied, which means users don't need to accurately input the fullName
    //Both stock symbol and company names can be recognized
    //Might return more than one matched symbols
    //@Parameter: input is the input from the user
    vector<string> getStockSymbols(string input){
        return table->getProximitySymbols(input);
    }
    
    //Download the csv file of the assgined stock from Internet
    //The csv file is downloaded to the current project directory
    //Internet connection is required here
    //The stock symbol must be valid!!
    //Return the fileName of the downloaded csv file
    //@Parameter: symbol is the valid stock symbol
    string openStock(string symbol){
        string filePath = fileExecutor->downloadFile(symbol);
        return filePath;
    }
    
    //Parse the stock csv file and store the historical stock statistics
    //@Parameter: symbol should be valid stock symbol
    //@Prameter: fileName should be the name of the assigned csv file
    void createStock(string symbol, string fileName){
        container->saveStock(new Stock(symbol,fileName));
    }
    
    //Print out the information of all saved stocks
    void printAllStocks(){
        container->printAllStocks();
    }
    
    //Get the estimated future prices of the assigned days
    //Return the prices in the vector, where the price of earlier day is in the front
    //@Parameter: stockSymbol is the valid stock symbol
    //@Parameter: numberOfDays is the number of future prices to estimate
    vector<double> getFuturePrices(string stockSymbol, int numberOfDays){
        return estimator->getFuturePrice(stockSymbol, numberOfDays);
    }
    
    //Return the suggestion for trading or keeping the assigned stock
    //@Parameter: stockSymbol is the valid stock symbol
    string getTradeSuggestion(string stockSymbol){
        return estimator->getTradeSuggestions(stockSymbol);
    }
    
};


#endif
