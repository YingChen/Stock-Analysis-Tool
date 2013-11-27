//
//  MyXMLParser.h
//  Stock
//
//  
//
//

#ifndef Stock_MyXMLParser_h
#define Stock_MyXMLParser_h

#include <iostream>
#include <fstream>

using namespace std;

/**
 This is simple xml parser which parse the setting xml file
 */
class MyXMLParser{
private:
    vector<string> lines;
    
    string trim(string& str){
        str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
        str.erase(str.find_last_not_of(' ')+1);         //surfixing spaces
        return str;
    }

    void readFile(string filePath){
        ifstream file(filePath.c_str());
        string str;
        if (!file.is_open()){
            perror("error while opening file");
        }
        
        while(getline(file,str)){
            string trimedLine = trim(str);
            //cout<<"line is "<<trimedLine<<endl;
            lines.push_back(trimedLine);
        }
    }
    
    string getStartTag(string label){
        string tag = "<";
        tag.append(label);
        tag.append(">");
        return tag;
    }
    
    string getEndTag(string label){
        string tag = "</";
        tag.append(label);
        tag.append(">");
        return tag;
    }

    
public:
    MyXMLParser(string filePath){
        readFile(filePath);
    }
    
    //Return the value of the item from the input label
    string getValue(string label){
        string startTag = getStartTag(label);
        string endTag = getEndTag(label);
        for(int i=0; i<lines.size(); i++){
            if((lines[i].find(startTag) != -1) && (lines[i].find(endTag) != -1)){
                int lenOfValue = int (lines[i].size() - startTag.size() - endTag.size());
                return lines[i].substr(startTag.size(), lenOfValue);
            }
        }
        return NULL;
    }

};


#endif
