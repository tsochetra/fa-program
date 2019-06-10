#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include <fstream>
#include <string>

using namespace std;

string *splitEach(string data) {
    string* arrayData = new string[data.length()];

    for(int i = 0; i< data.length(); i++) {
        arrayData[i] = data[i];
    }

    return arrayData;
}

string *split(string data, char c) {

    int totalChar = 1;

    for(int i = 0; i < data.length(); i ++) {
        if(data[i] == c) {
            totalChar += 1;
        }
    }

    int posSplit[totalChar + 2], j = 1;

    posSplit[0] = 0;

    for(int i = 0; i < data.length(); i ++) {
        if(data[i] == c) {
            posSplit[j] = i + 1;
            j++;
        }
    }
    posSplit[j] = data.length() + 1;

    string* arrayData = new string[totalChar + 1];

    for(int i = 0; i< totalChar; i++) {
        arrayData[i] = data.substr(posSplit[i], posSplit[i+1] - posSplit[i] - 1);
    }

    return arrayData;
}

string readFile(string file) {
    ifstream inFile;
    string sum;
    inFile.open("./data/" + file);

    if (!inFile) {
        cerr << "Unable to open file "<<file<<endl;
        exit(1);
    }

    inFile >> sum;
    inFile.close();
    return sum;
}

bool deleteFile(string file) {
    if(remove(("./data/" + file).c_str()) != 0) {
        
        cerr << "Unable to delete file "<<file<<endl;
        exit(1);
    } else {
        
        return true;
    }
}

#endif