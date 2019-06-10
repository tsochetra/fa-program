#include<iostream>
#include<stdlib.h>
#include <fstream>
#include <string>
#include "functions.h"
#include "trans.h"

using namespace std;

void convertFA(string fa) {
    string temp;
    string *listSymbols, *listStates, *listFinalStates;
    int numStates, numSymbols, numfinalStates;

    string *data = split(fa, '#');

    string *head = split(data[0], '.');

    numStates = stoi(head[0]);

    numSymbols = data[1].length();

    numfinalStates = head[1].length();

    listSymbols = splitEach(data[1]);

    listFinalStates = splitEach(head[1]);

    string dfa;

    Trans(numStates, numStates - 1, data[2], &dfa);

    string *dfa_data = split(dfa, '#');
    string *dfa_states_list = split(dfa_data[1], '.');
    string *dfa_states = split(dfa_data[2], '|');

    int dfa_numStates = stoi(dfa_data[0]);

    cout<<"Your converted DFA table: "<<endl;
	cout<<"   S.S\t| ";
	for(int i = 0; i< numSymbols - 1; i++) {
		cout<<listSymbols[i]<<"\t";
	}
	cout<<endl;
	for(int i = 0; i< dfa_numStates; i++) {
        string *eachSymbols = split(dfa_states[i], '.');
		cout<<"   "<<dfa_states_list[i]<<"\t| ";
		for(int j = 0; j< numSymbols - 1; j++) {
			cout<<eachSymbols[j]<<"\t";
		}
		cout<<endl;
	}

    string final_states[10];
    int index = 0;
    for(int i = 0; i < numfinalStates; i++) {
        string search = listFinalStates[i];

        for(int j = 0; j< dfa_numStates; j++) {
            string st = dfa_states_list[j];

            if (st.find(search) != string::npos) {
                final_states[index++] = st;
            }
        }
    }
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
