//
//  Pair.h
//  Stock
//
//
//
//

#ifndef Stock_Pair_h
#define Stock_Pair_h

#include "Time.h"

using namespace std;

class Pair{
private:
    Time* time;
    double price;
    
public:
    Pair(Time* time, double price){
        this->time = time;
        this->price = price;
    }
    
    
    string getTime(){
        return time->toString();
    }
    
    double getPrice(){
        return price;
    }
    
    string toString(){
        string str = "<";
        str.append(time->toString().c_str());
        str.append(" , ");
        str.append(to_string(price).c_str());
        str.append(">");
        return str;
    }
    
};


#endif
