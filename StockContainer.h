//
//  StockContainer.h
//  Stock
//
//  
//
//

#ifndef Stock_StockContainer_h
#define Stock_StockContainer_h

#include "Stock.h"

using namespace std;

class StockContainer{
private:
    vector<Stock*> stocks;

public:
    void saveStock(Stock* input){
        stocks.push_back(input);
    }
    
    Stock* getStock(string symbol){
        for (int i=0; i<stocks.size(); i++) {
            if(stocks[i]->getName().compare(symbol) == 0)
                return stocks[i];
        }
        return NULL;
    }
    
    void printAllStocks(){
        for(int i=0; i<stocks.size(); i++){
            stocks[i]->printInfo();
            cout<<"###################"<<endl;
        }
    }
    
};

#endif
