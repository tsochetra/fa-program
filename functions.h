#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include <fstream>
#include <string>

using namespace std;

// split each character from string, to array of string (abc => [a, b, c])
string *splitEach(string data) {
    string* arrayData = new string[data.length()];

    for(int i = 0; i< data.length(); i++) {
        arrayData[i] = data[i];
    }

    return arrayData;
}
// split string to array by a specific character (aa.be split by . => [aa, be])
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

// read content from file, and return content
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
// delete file, and return boolean
bool deleteFile(string file) {
    if(remove(("./data/" + file).c_str()) != 0) {
        
        cerr << "Unable to delete file "<<file<<endl;
        exit(1);
    } else {
        
        return true;
    }
}

// remove a specific character from the string (ababba remove b => aaa) 
string removeChar(string str, char charRemove) { 
    str.erase(remove(str.begin(), str.end(), charRemove), str.end());
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str; 
}
// write content to file
void write_file(string name, string data) {
	ofstream myfile;
	myfile.open ("./data/" + name + ".fa");
	myfile << data;
	myfile.close();
}

#endif