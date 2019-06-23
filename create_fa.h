// include libraries
#include <iostream>
#include <string>
#include <fstream>
#include "functions.h"

using namespace std;

// ask user to input information about FA
bool CreateFA(string *file) {

	// total states and symbols
	int numStates, numSymbols;

	string symbols, temp, final_states;

	cout<<"Enter the total of state: ";
	cin>>numStates;
	cout<<"Enter your set of symbols (separate by comma for each symbol): ";
	cin>>temp;

	symbols = removeChar(temp, ','); // remove , from string
	symbols = symbols + "E"; // add Epsilon to symbols
	numSymbols = symbols.length(); // get total of symbols

	// show input options to user
	cout<<"Now, you have ";
	for(int i = 0; i < numStates; i++) {
		if(i != 0 && i < numStates - 1) {
			cout<<", ";
		} else if (i == numStates - 1) {
			cout<<" and ";
		}
		cout<<(char)(65+i); // A,B,C,...
		
	}
	cout<<" as your state"<<endl;
	cout<<"Please enter your transition for each state: "<<endl;
	cout<<"Note:"<<endl;
	cout<<"   * your input options are ";
	for(int i = 0; i< numStates; i++) {
		cout<<(char)(65 + i)<<", ";
	}
	cout<<"-."<<endl;
	cout<<"   * separate by comma, if you have transition to multiple states"<<endl;
	cout<<"   * input - (dash), if no transition"<<endl;
	cout<<"   * E for epsilon"<<endl;
	// end

	 // create 2 dimensional array of string to store transition data each state
	string FA_TABLE[numStates][numSymbols];
	// loop asking user to input transition data of each state
	for(int i = 0; i< numStates; i++) {

		if(i == 0) {
			cout<<"State A (Start State): "<<endl;
		} else {
			cout<<"State "<<(char)(65 + i)<<":"<<endl;
		}
		// loop asking for transition each symbol of a state
		for(int j = 0; j< numSymbols; j++) {
			cout<<"   symbol \""<<symbols[j]<<"\" go to state: ";
			cin>>temp;
			FA_TABLE[i][j] = removeChar(temp, ','); // remove , and push to table
		}
	}

	cout<<"Enter your final state (separate by comma): ";
	cin>>temp;
	final_states = removeChar(temp, ','); // get final state
	
	// show summary of transition of every state
	cout<<"Your FA table summary: "<<endl;
	cout<<"   S.S\t| "; // States, Symbols
	// print row header of symbols
	for(int i = 0; i< numSymbols; i++) {
		cout<<symbols[i]<<"\t";
	}
	cout<<endl;
	// row of each state
	for(int i = 0; i< numStates; i++) {
		cout<<"   "<<(char)(65 + i)<<"\t| ";
		// column of each symbol
		for(int j = 0; j< numSymbols; j++) {
			cout<<FA_TABLE[i][j]<<"\t";
		}
		cout<<endl;
	}

	// asking user to save this FA or not
	while(true) {
		temp.clear(); // clear temp data;
		
		cout<<"Do you want to save this FA (Y/n): ";
		cin.get();
		getline(cin, temp);
		if(temp.empty() || temp == "Y" || temp == "y" ) { // user choose yes or just enter, Y default
			cout<<"Enter your FA name (no space, no special chars): ";
			cin>>temp;
			
			string fa; // for storing FA content
			
			// store file folder the data structure
			fa = to_string(numStates) + "." + final_states + "#" + symbols.substr(0, symbols.length() - 1) + "#";
			// loop append transition to content
			for(int i = 0; i< numStates; i++) {
				for(int j = 0; j< numSymbols; j++) {
					fa = fa + FA_TABLE[i][j];
					// last symbols doesn't need . to separate
					if(j < numSymbols - 1) {
						fa = fa + ".";
					}
				}
				// last state doesn't need |
				if(i < numStates - 1) {
					fa = fa + "|";
				}
			}
			write_file(temp, fa); // write file to folder
			*file = temp + ".fa"; // return file name to main program for futher operations
			return true;
		} else if (temp == "n" || temp == "N") { // not save the file
			return false;
		}
	}

	return false;
}