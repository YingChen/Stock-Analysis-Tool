//
//  main.cpp
//  Stock
//
//
//
//

#include <iostream>

#include "StockCenter.h"
#include "Pair.h"

using namespace std;

int main(int argc, const char * argv[])
{
    StockCenter* center = new StockCenter();
    //Ask for setting file
    cout<<"Do you need to add a setting file? If no, we will use the default setting. (Y/N)"<<endl;
    string answer;
    getline(cin,answer);
    if(answer.compare("Y")==0){
        cout<<"Please input invalid setting file name"<<endl;
        string fileName;
        getline(cin,fileName);
        center->addSettingFile(fileName);
    }
    
    int getValidInput = 0;
    string validSymbol;
    while (true) {
        
        while (getValidInput == 0) {
            //Input valid stock symbol
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
                cout<<"We find a valid stock symbol " << validSymbol<<endl;
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
        getValidInput = 0;
        
        cout<<"What do you want to do with the stock "<<validSymbol<<"? 1. Add it to the database. 2. Remove it from the database."<<endl;
        string option;
        getline(cin,option);
        int opt = atoi(option.c_str());
        
        if(opt == 1){
            //Download file from internet
            string fileName = center->downloadStock(validSymbol);
            cout<<"fileName is "<<fileName<<endl;
            
            //Parse the csv file
            center->createStock(validSymbol, fileName);
            center->printAllStocks();
        }
        else if(opt ==2){
            center->removeStock(validSymbol);
        }
        else{
            cout<<"Invalid command"<<endl;
        }
        
        cout<<"What do you want to process next. 1. Get stock history. 2. Get future prices. 3. Get the future <time,price> pairs. 4. Get suggestions for the current stock"<<endl;
        
        getline(cin,option);
        opt = atoi(option.c_str());
        
        if(opt == 1){
            //Print the stock history
            cout<<"Print the stock history"<<endl;
            vector<Pair*> history = center->getStockHistory(validSymbol);
            for(int i=0; i<history.size(); i++){
                cout<<history[i]->toString()<<endl;
            }
        }
        else if(opt == 2){
            cout<<"How many days in the future do you want to see"<<endl;
            string number;
            getline(cin,number);
            //Get the future prices
            int numberOfDays = atoi(number.c_str());
            
            vector<double> futurePrices = center->getFuturePrices(validSymbol, numberOfDays);
            cout<<"Future price is "<<endl;
            for(int i=0; i<numberOfDays; i++){
                cout<<futurePrices[i]<<endl;
            }
        }
        else if(opt == 3){
            cout<<"How many days in the future do you want to see"<<endl;
            string number;
            getline(cin,number);
            //Get the future <time,price> pairs
            int numberOfDays = atoi(number.c_str());
            vector<Pair*> future = center->getFuturePricesTable(validSymbol, numberOfDays);
            for(int i=0; i<numberOfDays; i++){
                Pair* pair = future[i];
                cout<<pair->getTime()<<" "<<pair->getPrice()<<endl;
            }
        }
        else if(opt == 4){
            //Get the suggestion
            cout<<center->getTradeSuggestion(validSymbol)<<endl;
        }
        else{
            cout<<"Invalid input"<<endl;
        }
    }
    return 0;
}

