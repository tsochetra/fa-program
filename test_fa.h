// include libraries
#include<iostream>
#include<stdlib.h>
#include <fstream>
#include <string>
#include "functions.h"
#include "trans.h"

using namespace std;

// function to test string
int testFA(string fa) {
    string temp, symbols;
    string *listSymbols, *listStates, *listFinalStates;
    int numStates, numSymbols, numfinalStates;
    // extract data from FA content
    string *data = split(fa, '#');

    string *head = split(data[0], '.');

    numStates = stoi(head[0]);

    data[1] = data[1] + "E";

    numSymbols = data[1].length();

    numfinalStates = head[1].length();

    symbols = data[1].substr(0, data[1].length() - 1);

    listSymbols = splitEach(data[1]);

    listFinalStates = splitEach(head[1]);

    // show the accepted symbols to test
    cout<<"Accept string: ";
    for(int i  = 0; i< numSymbols - 1; i++) {
        cout<<listSymbols[i];
        if(i < numSymbols - 2) {
            cout<<", ";
        }
    }
    cout<<"."<<endl;
    cout<<"Enter a string: ";
    cin>>temp;

    // check if string that user input is in accepted symbols or not
    // loop each symbols in string that user input
    for(int i = 0; i< temp.length(); i++) {
        int reject = 1;
        // if symbol input is in accepted symbols
        for(int j = 0; j< numSymbols -1; j ++) {
            if(temp[i] == symbols[j]) {
                reject = 0;
            }
        }
        // if symbol is not in accepted symbols
        if(reject == 1) {
            cout<<"Rejected"<<endl;
            cout<<"Enter e to exit: ";
            cin>>temp;
            return 0;
        }
    }

    string dfa;
    // transit FA to DFA
    Trans(numStates, numSymbols - 1, data[2], &dfa);

    // extract data from returned DFA string
    string *dfa_data = split(dfa, '#');
    string *dfa_states_list = split(dfa_data[1], '.');
    string *dfa_states = split(dfa_data[2], '|');

    int dfa_numStates = stoi(dfa_data[0]);
    // create DFA table to store state transition
    string DFA_TABLE[dfa_numStates][numSymbols - 1];
    string final_states[20];
    int index = 0;

    // loop push transition to each state in the DFA table
	for(int i = 0; i< dfa_numStates; i++) {
        string *eachSymbols = split(dfa_states[i], '.');
		for(int j = 0; j< numSymbols - 1; j++) {
			DFA_TABLE[i][j] = eachSymbols[j];
		}
	}
    // find new final state from previous FA
    for(int i = 0; i < numfinalStates; i++) {
        string search = listFinalStates[i];
        // cout<<search<<endl;
        for(int j = 0; j< dfa_numStates; j++) {
            string st = dfa_states_list[j];
            // cout<<st<<endl;
            if (st.find(search) != string::npos) {
                final_states[index++] = st;
            }
        }
    }
    // start state from 0 (state A)
    int currentState = 0;

    // loop every character of string that user input
    for(int i = 0; i< temp.length(); i++) {
        
        string nextState;

        // find index of that character in the symbols list
        int j;
        for(j = 0; j < numSymbols - 1; j++) {
            if(temp[i] == symbols[j]) {
                break;
            }
        }
        // get next state from current state of that symbol
        nextState = DFA_TABLE[currentState][j];
        
        // find index of next state and transit it as current state 
        for(int k = 0; k< dfa_numStates; k++) {
            if(dfa_states_list[k] == nextState) {
                currentState = k;
            }
        }
        
    }

    // check after the transition, current state is in final state list or not

    for(int i = 0; i < index; i++) {
        if(final_states[i] == dfa_states_list[currentState]) {
            cout<<"Accepted"<<endl;
            cout<<"Enter e to exit: ";
            cin>>temp;
            return 0;
        }
    }

    // if not in final state, then reject
    cout<<"Rejected"<<endl;
    cout<<"Enter e to exit: ";
    cin>>temp;
    return 1;
}
