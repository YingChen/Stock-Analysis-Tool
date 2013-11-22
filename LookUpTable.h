//
//  LookUpTable.h
//  Stock
//
// 
//
//

#ifndef Stock_LookUpTable_h
#define Stock_LookUpTable_h

#include "CSVParser.h"
#include "WordSimilarity.h"

using namespace std;

class LookUpTable{
private:
    WordSimilarity* ws;
    vector<string> symbols;
    vector<string> companyNames;
    
    void init(){
        //cout<<"Init in table"<<endl;
        CSVParser* parser = new CSVParser("companylist.csv");
        //cout<<"row count is "<<parser->getRowCount();
        for(int i=0; i<parser->getRowCount(); i++){
            //cout<<parser->getElement(i, 0) << " "<<parser->getElement(i,1)<<endl;
            symbols.push_back(parser->getElement(i,0));
            companyNames.push_back(parser->getElement(i,1));
        }
    }
    
    
public:
    LookUpTable(){
        init();
        ws = new WordSimilarity();
    }
    
    vector<string> getProximitySymbols(string input){
        int maxDistance = 9999;
        vector<int> distance;
        for(int i=0; i<symbols.size(); i++){
            int companyNameDistance = ws->calculateDistance(input, companyNames[i]);
            int symbolDistance = ws->calculateDistance(input,symbols[i]);
            if(symbolDistance > companyNameDistance)
                distance.push_back(companyNameDistance);
            else
                distance.push_back(symbolDistance);
        
        }
        
        int minDistance = maxDistance;
        for(int i=0; i<distance.size(); i++){
            if(minDistance > distance[i])
                minDistance = distance[i];
        }
        
        vector<string> result;
        for(int i=0; i<distance.size(); i++){
            if(distance[i] == minDistance)
                result.push_back(symbols[i]);
        }
        return result;
    }
    
    
    int getSymbolIndex(string str){
        for (int i=0; i<symbols.size(); i++) {
            if(symbols[i].compare(str) == 0)
                return i;
        }
        return -1;
    }
    
    int getCompanyNameIndex(string str){
        for(int i=0; i<companyNames.size(); i++){
            if(companyNames[i].compare(str) == 0)
                return i;
        }
        return -1;
    }
    
    string getCompanyName(int index){
        return companyNames[index];
    }
    
    string getSymbol(int index){
        return symbols[index];
    }
    
    string getCompanyName(string symbol){
        int index = getSymbolIndex(symbol);
        return companyNames[index];
    }
    
    string getSymbol(string companyName){
        int index = getCompanyNameIndex(companyName);
        return symbols[index];
    }
    
        
};

#endif
