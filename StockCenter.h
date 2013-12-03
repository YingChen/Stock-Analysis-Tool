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
#include "Settings.h"
#include "Pair.h"

using namespace std;

/**
 This is the main interfaces for back-end part of the project
 The UI should be able to accomplish all the functionalities by calling the public methods in this class
 */

class StockCenter{
private:
    LookUpTable* table;
    FileExecutor* fileExecutor;
    StockContainer* container;
    PriceEstimator* estimator;
    Settings* settings;
    
public:
    //Init a stockCenter if on setting file is assigned
    //Use default values
    StockCenter(){
        settings = new Settings();
        table = new LookUpTable(settings);
        fileExecutor = new FileExecutor(settings);
        container = new StockContainer();
        estimator = new PriceEstimator(container,settings);
    }
    
    //If a setting file is assigned, then use the values in the file
    StockCenter(string fileName){
        settings = new Settings(fileName);
        table = new LookUpTable(settings);
        fileExecutor = new FileExecutor(settings);
        container = new StockContainer();
        estimator = new PriceEstimator(container,settings);
    }
    
    //Change a setting file, will change all the setting values
    //@Parameter: fileName is the name of the new setting file
    void addSettingFile(string fileName){
        settings->setSettingsFile(fileName);
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
    string downloadStock(string symbol){
        string filePath = fileExecutor->downloadFile(symbol);
        return filePath;
    }
    
    //Parse the stock csv file and store the historical stock statistics
    //@Parameter: symbol should be valid stock symbol
    //@Prameter: fileName should be the name of the assigned csv file
    void createStock(string symbol, string fileName){
        container->saveStock(new Stock(symbol,fileName));
    }
    
    //This method does the following tasks:
    //1. Download the csv file online
    //2. Parse the csv file
    //3. Create a stock object and save it
    //@Parameter: symbol is the valid symbol of a stock
    void openStock(string symbol){
        string filePath = fileExecutor -> downloadFile(symbol);
        container->saveStock(new Stock(symbol,filePath));
    }
    
    //Remove the stock from the vector
    //If the stock does not exist, it will print out message
    //@Parameter: symbol is the valid symbol of a stock
    void removeStock(string symbol){
        container->removeStock(symbol);
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
    
    //Get the estimated future prices of the assigned days
    //Return the pairs of <day,price>.
    //@Parameter: stockSymbol is the valid stock symbol
    //@Parameter: numberOfDays is the number of future prices to estimate
    vector<Pair*> getFuturePricesTable(string stockSymbol, int numberOfDays){
        return estimator->getFuturePrices(stockSymbol, numberOfDays);
    }
    
    //Return the suggestion for trading or keeping the assigned stock
    //@Parameter: stockSymbol is the valid stock symbol
    string getTradeSuggestion(string stockSymbol){
        return estimator->getTradeSuggestions(stockSymbol);
    }
    
    //Return a vector of historical prices
    //If the stock could not found, then an empty vector will be returned
    //@Parameter: symbol is the valid stock symbol
    vector<double> getPriceTable(string symbol){
        return container->getPriceTable(symbol);
    }
    
    //Return the close price of tha assigned stock on the assigned day
    //If either the stock symbol or the date is invalid, then return -1
    //@Parameter: symbol is the valid stock symbol
    //@Parameter: date should be in format mm-dd-yy (1-15-14)
    double getPriceOfDay(string symbol, string date){
        return container->getPriceOfDay(symbol, date);
    }
    
    //Return the volume of tha assigned stock on the assigned day
    //If either the stock symbol or the date is invalid, then return -1
    //@Parameter: symbol is the valid stock symbol
    //@Parameter: date should be in format mm-dd-yy (1-15-14)
    double getVolumeOfDay(string symbol, string date){
        return container->getVolumnOfDay(symbol, date);
    }
    
    //Return the open price of tha assigned stock on the assigned day
    //If either the stock symbol or the date is invalid, then return -1
    //@Parameter: symbol is the valid stock symbol
    //@Parameter: date should be in format mm-dd-yy (1-15-14)
    double getOpenPriceOfDay(string symbol, string date){
        return container->getOpenPriceOfDay(symbol, date);
    }
    
    //Return the close price of tha assigned stock on the assigned day
    //If either the stock symbol or the date is invalid, then return -1
    //@Parameter: symbol is the valid stock symbol
    //@Parameter: date should be in format mm-dd-yy (1-15-14)
    double getClosePriceOfDay(string symbol, string date){
        return container->getClosePriceOfDay(symbol, date);
    }
    
    //Return the highest price of tha assigned stock on the assigned day
    //If either the stock symbol or the date is invalid, then return -1
    //@Parameter: symbol is the valid stock symbol
    //@Parameter: date should be in format mm-dd-yy (1-15-14)
    double getHighPriceOfDay(string symbol, string date){
        return container->getHighPriceOfDay(symbol, date);
    }
    
    //Return the lowest price of tha assigned stock on the assigned day
    //If either the stock symbol or the date is invalid, then return -1
    //@Parameter: symbol is the valid stock symbol
    //@Parameter: date should be in format mm-dd-yy (1-15-14)
    double getLowPriceOfDay(string symbol, string date){
        return container->getLowPriceOfDay(symbol, date);
    }
    
    
    //Return a vector of <time,price> pairs of the assigned stock
    //The time is in the format mm-dd-yy, for example 1-4-13
    //The price is in double
    //@Parameter: symbol is the valid stock symbol
    vector<Pair*> getStockHistory(string symbol){
        return container->getStockHistory(symbol);
    }
    
    //Return a vector of all the stock symbols
    vector<string> getAllStockSymbols(){
        return table->getAllStockSymbols();
    }
    
};


#endif
