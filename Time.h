//
//  Time.h
//  Stock
//
//  
//
//

#ifndef Stock_Time_h
#define Stock_Time_h

#include <string>

using namespace std;

/**
 This is a Time object contains YEAR, MONTH, DAY infos
 */
class Time{
private:
    int year;
    int month;
    int day;
    
    int convertMonthToInt(string str){
        //Save time. hard-coded. Ugly
        if(str.compare("Jan") == 0)
            return 1;
        else if(str.compare("Feb") == 0)
            return 2;
        else if(str.compare("Mar") == 0)
            return 3;
        else if(str.compare("Apr") == 0)
            return 4;
        else if(str.compare("May") == 0)
            return 5;
        else if(str.compare("Jun") == 0)
            return 6;
        else if(str.compare("Jul") == 0)
            return 7;
        else if(str.compare("Aug") == 0)
            return 8;
        else if(str.compare("Sep") == 0)
            return 9;
        else if(str.compare("Oct") == 0)
            return 10;
        else if(str.compare("Nov") == 0)
            return 11;
        else if(str.compare("Dec") == 0)
            return 12;
        else
            cerr<<"Error in converting month"<<endl;
        
        return -1;
    }
    
    vector<string> split(string input, const char token){
        string str;
        vector<string> result;
        istringstream iss(input);
        while (getline(iss,str,token)) {
            result.push_back(str);
        }
        return result;
    }
    
    int getDayOfThisMonth(int month){
        if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month ==12)
            return 31;
        else if(month==4 || month ==6 || month == 9 || month ==11)
            return 30;
        else
            return 28;
    }
    
    
public:
    Time(string input){
        vector<string> timeInfo = split(input,'-');
        this->day = atoi(timeInfo[0].c_str());
        this->month = convertMonthToInt(timeInfo[1]);
        this->year = atoi(timeInfo[2].c_str());
    }
    
    Time(int year, int month, int day){
        this->year = year;
        this->month = month;
        this->day = day;
    }
    
    
    string toString(){
        string result = to_string(year);
        result.append("-");
        result.append(to_string(month));
        result.append("-");
        result.append(to_string(day));
        return result;
    }
    
    //Compare with time object
    //Return < 0, if the current time is earlier
    //Return > 0, if the compared time is earlier
    //Return = 0, if the two time objects are equal
    int compareTo(Time* anotherTime){
        if(this->year != anotherTime->year)
            return this->year - anotherTime->year;
        else if(this->month != anotherTime->month)
            return this->month - anotherTime->month;
        else
            return this->day - anotherTime->day;
    }
    
    bool equalTo(Time* anotherTime){
        return (this->year==anotherTime->year) && (this->month==anotherTime->month) && (this->day==anotherTime->day);
    }
    
    //Tell if the current Time is in the range of {first, second}.
    bool inThisRange(Time* first, Time* second){
        return (this->compareTo(first) >= 0) && (this->compareTo(second) <=0);
    }
    
    Time* getTomorrow(){
        int day = this->day + 1;
        int dayOfMonth = getDayOfThisMonth(this->month);
        int carry = 0;
        if(day > dayOfMonth){
            day = day - dayOfMonth;
            carry = 1;
        }
        
        int month = this->month + carry;
        if(month > 12){
            month = month -12;
            carry = 1;
        }
        else{
            carry = 0;
        }
        
        int year = this->year + carry;
        
        return new Time(year,month,day);
        
    }
    
};

#endif
