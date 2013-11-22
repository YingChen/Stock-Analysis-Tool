//
//  WordSimilarity.h
//  Stock
//
//  
//
//

#ifndef Stock_WordSimilarity_h
#define Stock_WordSimilarity_h

#include "LookUpTable.h"

using namespace std;

/*
 Calculate the similarities of two words using Levenshtein distance
 Reference for algorithm can be found at： http://en.wikipedia.org/wiki/Levenshtein_distance
 */
class WordSimilarity{
    
private:
    int LevenshteinDistance(string wordA, string wordB){
        if(wordA.compare(wordB) == 0)
            return 0;
        
        int lenA = (int) wordA.length();
        int lenB = (int) wordB.length();
        
        if(lenA ==0)
            return lenB;
        else if(lenB == 0)
            return lenA;
        
        int* v0 = new int[lenB+1];
        int* v1 = new int[lenB+1];
        //int v0[lenB+1];
        //int v1[lenB+1];
        
        for(int i=0; i<lenB+1; i++){
            v0[i] = i;
        }
        
        for(int i=0; i<lenA; i++){
            v1[0] = i+1;
            
            for(int j=0; j<lenB; j++){
                int cost = (wordA[i] == wordB[j]) ? 0 : 1;
                v1[j+1] =minimum(v1[j]+1, v0[j+1]+1, v0[j]+cost);
            }
            
            for(int j=0; j<lenB+1; j++){
                v0[j] = v1[j];
            }
            
        }
        int result = v1[lenB];
        delete v0;
        delete v1;
        return result;
    }
    
    int minimum(int a, int b, int c){
        int temp = (a>=b) ? b : a;
        int result = (temp >= c) ? c : temp;
        return result;
    }
    
public:
    WordSimilarity(){
        
    }
    
    int calculateDistance(string wordA, string wordB){
        int distance =  LevenshteinDistance(wordA, wordB);
        //cout<<wordA << " "<<wordB << " distance is "<<distance<<endl;
        return distance;
    }
    
};

#endif
