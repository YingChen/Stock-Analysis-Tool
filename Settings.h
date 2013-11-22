//
//  Settings.h
//  Stock
//
//  
//
//

#ifndef Stock_Settings_h
#define Stock_Settings_h

using namespace std;

class Settings{
private:
    string baseUrl;
    string companyNamesFile;
    double threadhold_tradeInHighlyRecommened;
    double threadhold_tradeInRecommended;
    double threadhold_tradeOutRecommended;
    double threadhold_tradeOutHighlyRecommended;

public:
    Settings(){
        baseurl = "http://www.google.com/finance/historical?output=csv&q=";
        companyNamesFile = "companylist.csv";
        threadhold_tradeInHighlyRecommened = 0.05;
        threadhold_tradeInRecommended = 0.01;
        threadhold_tradeOutRecommended = -0.01;
        threadhold_tradeOutHighlyRecommended = -0.05;
    }
    
    Settings(string settingFile){
        
    }
    
    string getBaseurl(){
        return baseurl;
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
