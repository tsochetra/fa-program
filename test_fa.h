#include<iostream>
#include<stdlib.h>
#include <fstream>
#include <string>
#include "functions.h"
#include "trans.h"

using namespace std;

int testFA(string fa) {
    string temp, symbols;
    string *listSymbols, *listStates, *listFinalStates;
    int numStates, numSymbols, numfinalStates;

    string *data = split(fa, '#');

    string *head = split(data[0], '.');

    numStates = stoi(head[0]);

    numSymbols = data[1].length();

    numfinalStates = head[1].length();

    symbols = data[1].substr(0, data[1].length() - 1);

    listSymbols = splitEach(data[1]);

    listFinalStates = splitEach(head[1]);

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

    for(int i = 0; i< temp.length(); i++) {
        int reject = 1;
        for(int j = 0; j< numSymbols -1; j ++) {
            if(temp[i] == symbols[j]) {
                reject = 0;
            }
        }
        if(reject == 1) {
            cout<<"Rejected"<<endl;
            cout<<"Enter e to exit: ";
            cin>>temp;
            return 0;
        }
    }

    string dfa;

    Trans(numStates, numStates - 1, data[2], &dfa);

    string *dfa_data = split(dfa, '#');
    string *dfa_states_list = split(dfa_data[1], '.');
    string *dfa_states = split(dfa_data[2], '|');

    int dfa_numStates = stoi(dfa_data[0]);

    string DFA_TABLE[dfa_numStates][numSymbols - 1];
    string final_states[10];
    int index = 0;
	for(int i = 0; i< dfa_numStates; i++) {
        string *eachSymbols = split(dfa_states[i], '.');
		for(int j = 0; j< numSymbols - 1; j++) {
			DFA_TABLE[i][j] = eachSymbols[j];
		}
	}
    
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

    int currentState = 0;

    for(int i = 0; i< temp.length(); i++) {
        string cs;
        int j;
        for(j = 0; j < numSymbols - 1; j++) {
            if(temp[i] == symbols[j]) {
                break;
            }
        }
        cs = DFA_TABLE[currentState][j];
        for(int k = 0; k< dfa_numStates; k++) {
            if(dfa_states_list[k] == cs) {
                currentState = k;
            }
        }
        
    }

    for(int i = 0; i < index; i++) {
        if(final_states[i] == dfa_states_list[currentState]) {
            cout<<"Accepted"<<endl;
            cout<<"Enter e to exit: ";
            cin>>temp;
            return 0;
        }
    }



    

    cout<<"Rejected"<<endl;
    cout<<"Enter e to exit: ";
    cin>>temp;
    return 1;
}
