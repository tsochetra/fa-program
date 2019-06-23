// include libraries
#include<iostream>
#include<stdlib.h>
#include <fstream>
#include <string>
#include "functions.h"
#include "trans.h"

using namespace std;

// convert FA to DFA function
void convertFA(string fa) {

    string temp;
    string *listSymbols, *listStates, *listFinalStates;
    int numStates, numSymbols, numfinalStates;

    // extract data from FA content
    string *data = split(fa, '#'); 

    string *head = split(data[0], '.');

    numStates = stoi(head[0]);

    data[1] = data[1] + "E";

    numSymbols = data[1].length();

    numfinalStates = head[1].length();

    listSymbols = splitEach(data[1]);

    listFinalStates = splitEach(head[1]);

    string dfa;

    // transit FA to DFA and store it in dfa
    Trans(numStates, numSymbols - 1, data[2], &dfa);

    // extract data from dfa string
    string *dfa_data = split(dfa, '#');
    string *dfa_states_list = split(dfa_data[1], '.');
    string *dfa_states = split(dfa_data[2], '|');

    int dfa_numStates = stoi(dfa_data[0]);

    cout<<"Your converted DFA table: "<<endl;
	cout<<"   S.S\t| ";
    // print symbols with no Epsilon anymore
	for(int i = 0; i< numSymbols - 1; i++) {
		cout<<listSymbols[i]<<"\t";
	}
	cout<<endl;
    // print transition of each state
	for(int i = 0; i< dfa_numStates; i++) {
        string *eachSymbols = split(dfa_states[i], '.');
		cout<<"   "<<dfa_states_list[i]<<"\t| ";
		for(int j = 0; j< numSymbols - 1; j++) {
			cout<<eachSymbols[j]<<"\t";
		}
		cout<<endl;
	}

    string final_states[20]; // final state size up to 20 
    int index = 0;
    // loop finding new state that has previous final state is also a final state, E final state => EF also final state
    for(int i = 0; i < numfinalStates; i++) {
        string search = listFinalStates[i];
        // loop every new state
        for(int j = 0; j< dfa_numStates; j++) {
            string st = dfa_states_list[j];
            // if new state contain previous final state, and push to the final state
            if (st.find(search) != string::npos) {
                final_states[index++] = st;
            }
        }
    }
    // print final states to console
    cout<<"Your final state: ";
    for(int i = 0; i< index; i++) {
        cout<<final_states[i];
        if(i < index -1) {
            cout<<", ";
        }
    }
    cout<<endl;

    cout<<"Enter e to exit: ";
    cin>>temp;
}
