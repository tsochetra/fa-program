#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include "functions.h"

using namespace std;

bool deleteFA(string file) {
    string temp;
    while(true) {
        temp.clear();
		
		cout<<"Do you want to delete this FA (Y/n): ";
		cin.get();
		getline(cin, temp);
		if(temp.empty() || temp == "Y" || temp == "y" ) { 
            if(deleteFile(file)) {
                return true;
            } else {
                return false;
            }
        } else if (temp == "n" || temp == "N") {
            return false;
        }
    } 
    
}
