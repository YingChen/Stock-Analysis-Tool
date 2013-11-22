//
//  main.cpp
//  Stock
//
//  
//
//

#include <iostream>

#include "CSVRow.h"
#include "CSVParser.h"
#include "Time.h"
#include "Stock.h"
#include "StockCenter.h"
#include "LookUpTable.h"
#include "WordSimilarity.h"
#include "FileExecutor.h"
#include "PriceEstimator.h"

int main(int argc, const char * argv[])
{
    StockCenter* center = new StockCenter();
    //while (true) {
        int getValidInput = 0;
        string validSymbol;
        
        while (getValidInput == 0) {
            cout<<"Please input the stock symbol or name"<<endl;
            string inputSymbol;
            getline(cin,inputSymbol);
            cout<<"The stock symbol or name you've entered is "<<inputSymbol<<endl;
            
            
            vector<string> similarSymbols = center->getStockSymbols(inputSymbol);
            if(similarSymbols.size() == 0){
                cout<<"could not find the valid stock symbol that matches your input"<<endl;
            }
            else if(similarSymbols.size() == 1){
                validSymbol = similarSymbols[0];
                cout<<"We find a valid stock symbol" << validSymbol<<endl;
                getValidInput = 1;
            }
            else{
                cout<<"We find more than 1 symbols that matches your input"<<endl;
                for(int i=0; i<similarSymbols.size(); i++){
                    cout<<similarSymbols[i]<<endl;
                }
                cout<<"Please make input again"<<endl;
            }
        }
        
        //Download file from internet
        string fileName = center->openStock(validSymbol);
        cout<<"fileName is "<<fileName<<endl;
        
        //Parse the csv file
        center->createStock(validSymbol, fileName);
        center->printAllStocks();
    
        //Get the future prices
        int numberOfDays = 7;
        vector<double> futurePrices = center->getFuturePrices(validSymbol, numberOfDays);
        cout<<"Future price is "<<endl;
        for(int i=0; i<numberOfDays; i++){
            cout<<futurePrices[i]<<endl;
        }
    
        //Get the suggestion
        cout<<center->getTradeSuggestion(validSymbol)<<endl;
    //}
    
    return 0;
}

