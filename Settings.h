//
//  Settings.h
//  Stock
//
//  
//
//

#ifndef Stock_Settings_h
#define Stock_Settings_h

#include "MyXMLParser.h"

using namespace std;

/**
 This is a setting object which stores all the setting values
 */
class Settings{
private:
    MyXMLParser* xmlParser;
    string baseUrl;
    string companyNamesFile;
    double threadhold_tradeInHighlyRecommened;
    double threadhold_tradeInRecommended;
    double threadhold_tradeOutRecommended;
    double threadhold_tradeOutHighlyRecommended;

public:
    //If no setting file is imported, we use the default value
    Settings(){
        baseUrl = "http://www.google.com/finance/historical?output=csv&q=";
        companyNamesFile = "companylist.csv";
        threadhold_tradeInHighlyRecommened = 0.05;
        threadhold_tradeInRecommended = 0.01;
        threadhold_tradeOutRecommended = -0.01;
        threadhold_tradeOutHighlyRecommended = -0.05;
    }
    
    //In case setting file is imported
    Settings(string settingFile){
        baseUrl = "http://www.google.com/finance/historical?output=csv&q=";
        xmlParser  = new MyXMLParser(settingFile);
        companyNamesFile = xmlParser -> getValue("LookUpTable");
        threadhold_tradeInHighlyRecommened = atof(xmlParser -> getValue("TradeInHighRecommended").c_str());
        threadhold_tradeInRecommended = atof(xmlParser -> getValue("TradeInRecommended").c_str());
        threadhold_tradeOutRecommended = atof(xmlParser -> getValue("TradeOutRecommended").c_str());
        threadhold_tradeOutHighlyRecommended = atof(xmlParser -> getValue("TradeOutHighRecommended").c_str());
    }
    
    //Change the setting file
    void setSettingsFile(string settingFile){
        xmlParser  = new MyXMLParser(settingFile);
        companyNamesFile = xmlParser -> getValue("LookUpTable");
        threadhold_tradeInHighlyRecommened = atof(xmlParser -> getValue("TradeInHighRecommended").c_str());
        threadhold_tradeInRecommended = atof(xmlParser -> getValue("TradeInRecommended").c_str());
        threadhold_tradeOutRecommended = atof(xmlParser -> getValue("TradeOutRecommended").c_str());
        threadhold_tradeOutHighlyRecommended = atof(xmlParser -> getValue("TradeOutHighRecommended").c_str());
    }
    
    string getBaseurl(){
        return baseUrl;
    }
    
    string getCompanyNamesFile(){
        return companyNamesFile;
    }
    
    double getThreadholdForHighlyRecommendedTradeIn(){
        return threadhold_tradeInHighlyRecommened;
    }
    
    double getThreadholdForRecommendedTradeIn(){
        return threadhold_tradeInRecommended;
    }
    
    double getThreadholdForHighlyRecommendedTradeOut(){
        return threadhold_tradeOutHighlyRecommended;
    }
    
    double getThreadholdForRecommendedTradeOut(){
        return threadhold_tradeOutRecommended;
    }
    
};

#endif
