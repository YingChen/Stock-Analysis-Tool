//
//  PriceEstimator.h
//  Stock
//
// 
//
//

#ifndef Stock_PriceEstimator_h
#define Stock_PriceEstimator_h

#include "StockContainer.h"
#include "Stock.h"
#include "Settings.h"
#include "Pair.h"

using namespace std;

/**
 This class helps to estimate the future price from historical price
 */
class PriceEstimator{
private:
    StockContainer* stockContainer;
    Settings* mySettings;
    
    vector<double> estimatePrice(vector<double> priceTable){
        //int tableSize = (int) priceTable.size();
        //Give initial value to coefficients
        double a0_init = (0-priceTable[0]);
        double a1_init = 0;
        double a2_init = -0.25;
        double a3_init = -0.125;
        
        //Give the max values of coefficients
        double a0_max = 0;
        double a1_max = 1;
        double a2_max = 0.25;
        double a3_max = 0.125;
        
        double a0_increment = priceTable[0]/20;
        double a1_increment = 0.05;
        double a2_increment = 0.025;
        double a3_increment = 0.0125;
        
        //Record the values of coefficients when they bring the minimum
        double a0_in_min = a0_init;
        double a1_in_min = a1_init;
        double a2_in_min = a2_init;
        double a3_in_min = a3_init;
        
        //Have a min record. Set a big number to it at first
        double min = 99999999999999;
        
        //Start!!!!!
        for (double a0 = a0_init; a0<=a0_max; a0=a0+a0_increment) {
            for(double a1 = a1_init; a1<=a1_max; a1=a1+a1_increment){
                for(double a2=a2_init; a2<=a2_max; a2=a2+a2_increment){
                    for(double a3=a3_init; a3<=a3_max; a3=a3+a3_increment){
                        double variance = calculateVariances(priceTable,a0,a1,a2,a3);
                        if (variance < min) {
                            min = variance;
                            a0_in_min = a0;
                            a1_in_min = a1;
                            a2_in_min = a2;
                            a3_in_min = a3;
                        }
                    }
                }
            }
        }
        vector<double> result;
        result.push_back(a0_in_min);
        result.push_back(a1_in_min);
        result.push_back(a2_in_min);
        result.push_back(a3_in_min);
        
        return result;
    }
    
    //Sum of e^2 where e^2 = (y[0] - a0 - a1 * y[1] - a2 * y[2] - a3* y[3])^2
    double calculateVariances(vector<double> table, double a0, double a1, double a2, double a3){
        double result = 0;
        for (int i=0; i<table.size()-3; i++) {
            double variance = table[i] - a0 - a1*table[i+1] - a2*table[i+2] -a3*table[i+3];
            result = result + variance * variance;
        }
        return result;
    }
    
    //Get the furture price of next few days
    vector<double> calculateFuturePrice(vector<double> priceTable, vector<double> coefficients, int numOfDays){
        //Get coefficients
        double a0 = coefficients[0];
        double a1 = coefficients[1];
        double a2 = coefficients[2];
        double a3 = coefficients[3];
        
        cout<<"Coefficients are "<<a0<<" "<<a1<<" "<<a2<<" "<<a3<<endl;
        
        //This vector will include stock prices of 3 days starting from yesterday
        vector<double> internalResult;
        
        //Insert the first three elements from history
        //Take care of the sequence
        internalResult.push_back(priceTable[2]);
        internalResult.push_back(priceTable[1]);
        internalResult.push_back(priceTable[0]);
        
        //Calculate the future price
        for (int i=0; i<numOfDays; i++) {
            double newValue = a0 + a1 * internalResult[i+2] + a2 * internalResult[i+1] + a3 * internalResult[i];
            internalResult.push_back(newValue);
        }
        
        //Get the return vector
        //Here only includes the future prices
        vector<double> futurePrices;
        for (int i=3; i<internalResult.size(); i++) {
            futurePrices.push_back(internalResult[i]);
        }
        
        return futurePrices;
    }
    
    string getSuggestion(double pastPrice, double futurePrice){
        double threadhold_tradeInHighlyRecommened = mySettings->getThreadholdForHighlyRecommendedTradeIn();
        double threadhold_tradeInRecommended = mySettings->getThreadholdForRecommendedTradeIn();
        double threadhold_tradeOutRecommended = mySettings->getThreadholdForRecommendedTradeOut();
        double threadhold_tradeOutHighlyRecommended = mySettings->getThreadholdForHighlyRecommendedTradeOut();
        
        double futurePriceChange = (futurePrice - pastPrice) / pastPrice;
        if(futurePriceChange >= threadhold_tradeInHighlyRecommened)
            return "Trade In, Highly Recommeneded";
        else if(futurePriceChange >= threadhold_tradeInRecommended)
            return "Trade In, Recommended";
        else if(futurePriceChange < threadhold_tradeOutHighlyRecommended)
            return "Trade Out, Highly Recommended";
        else if(futurePriceChange < threadhold_tradeOutRecommended)
            return "Trade Out, Recommended";
        else
            return "Keep it";
    }
    
public:
    PriceEstimator(StockContainer* container, Settings* setting){
        stockContainer = container;
        mySettings = setting;
    }
    
    //Get the price of future days
    vector<double> getFuturePrice(string stockSymbol, int numOfDays){
        Stock* stock = stockContainer->getStock(stockSymbol);
        vector<double> priceTable = stock->getPriceTable();
        //Get the coeffients. Here the vector should only contain four elements
        vector<double> coefficients = estimatePrice(priceTable);
        //Calculate the future prices
        vector<double> futurePrices = calculateFuturePrice(priceTable,coefficients,numOfDays);
        return futurePrices;
    }
    
    vector<Pair*> getFuturePrices(string stockSymbol, int numOfDays){
        Stock* stock = stockContainer->getStock(stockSymbol);
        vector<double> priceTable = stock->getPriceTable();
        //Get the coeffients. Here the vector should only contain four elements
        vector<double> coefficients = estimatePrice(priceTable);
        //Calculate the future prices
        vector<double> futurePrices = calculateFuturePrice(priceTable,coefficients,numOfDays);
        
        vector<Time*> futureTimes;
        Time* current= stock->getLastTimeInHistory();
        vector<Pair*> result;
        
        for(int i=0; i<numOfDays; i++){
            current = current->getTomorrow();
            futureTimes.push_back(current);
        }
        
        for(int i=0; i<numOfDays; i++){
            result.push_back(new Pair(futureTimes[i],futurePrices[i]));
        }
        
        return result;
    }

    //Get Trade Suggestions
    //Compare the the latest price with the price of next day
    string getTradeSuggestions(string stockSymbol){
        Stock* stock = stockContainer->getStock(stockSymbol);
        vector<double> priceTable = stock->getPriceTable();
        //Get the coeffients. Here the vector should only contain four elements
        vector<double> coefficients = estimatePrice(priceTable);
        //Calculate the prices of the next 3 days
        vector<double> futurePrices = calculateFuturePrice(priceTable,coefficients,1);
        //Get the suggestion
        string suggestion = getSuggestion(priceTable[0],futurePrices[0]);
        return suggestion;
    }
    
    
};

#endif
