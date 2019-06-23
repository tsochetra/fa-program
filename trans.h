#ifndef TRANS_H
#define TRANS_H
// include libraries
#include<iostream>
#include<stdlib.h>
#include<string>
#include "functions.h"

using namespace std;
// create structure for storing temporary state for processing
struct DFA { 
    string states; 
    int count; 
};
// linked list structure for storing closure of FA
struct closure_table_element {
    string data;
    closure_table_element *next;
};
struct closure_table_list {
    int n;
    closure_table_element *head, *tail;
};
// temporary variable
string buffer, T_buf;
int last_index = 0; 

// add closure to the list
void addLast(closure_table_list *l, string value) {
    closure_table_element *e;
    e = new closure_table_element;
    e->data = value;
    e->next = NULL;
    

    if(l->n == 0) {
        l->head = e;
        l->tail = e;
    } else {
        e->next = NULL;
        l->tail->next = e;
        l->tail = e;
    }

    l->n = l->n + 1;
}

// return element data in list by index
string getElement(closure_table_list *l , int index) {
    closure_table_element *e;
    e = l->head;
    for(int i = 0; i< index; i++) {
        e = e->next;
    }
    return e->data;
}

// reset each element of array to zero
void reset(int ar[], int size) { 
    int i; 

    for (i = 0; i < size; i++) { 
        ar[i] = 0; 
    } 
} 

void check(int ar[], string S) { 
    int i, j; 

    int len = S.length(); 
    for (i = 0; i < len; i++) { 

        j = int(S[i]) - 65; 
        ar[j]++; 
    }
} 

string state(int ar[], int size, string S) { 
    int j, k = 0;

    char temp[100];

    for (j = 0; j < size; j++) { 
        if (ar[j] != 0) {

            temp[k] = 65+j;

            k++;
        }
        
    } 


    temp[k] = '\0'; 
    return temp;
}
// to pick the next closure from closure set
int closure(int ar[], int size) { 
    int i; 
    // check if next closure already existed in closure list
    for (i = 0; i < size; i++) { 
        if (ar[i] == 1) {
            return i;
        }
         
    } 
    return 100; 
}

int indexing(struct DFA *dfa) { 
    int i; 

    for (i = 0; i < last_index; i++) { 
        if (dfa[i].count == 0) 
        return 1; 
    } 
    return -1; 
}
// get closure of FA and store it in the list for transition to DFA
void getClosure(int states, int symbols, string * NFA_TABLE, closure_table_list *closure_table) { 

    int closure_ar[states];
 
    for (int i = 0; i < states; i++) { 
        reset(closure_ar, states); 
        closure_ar[i] = 2; 

        string currentState = NFA_TABLE[i*(symbols+1) + symbols];

        if (currentState != "-") {

            buffer = currentState;
            check(closure_ar, buffer); 
            int z = closure(closure_ar, states); 

            while (z != 100) { 
                string subState = NFA_TABLE[z*(symbols+1) + symbols];
                if (subState != "-") { 
                    buffer = subState;
                    check(closure_ar, buffer); 
                }
                closure_ar[z]++; 
                z = closure(closure_ar, states); 
            }
        }

        buffer.clear();
        
        buffer = state(closure_ar, states, buffer); 
        addLast(closure_table, buffer); 
    }
}

void trans(string S, int M, closure_table_list *closure_table, int states, int symbols,  string *NFA_TABLE, string TB) { 

    int len = S.length(); 
    int i, j, k, g; 
    int arr[states]; 
    int sz; 
    reset(arr, states); 
    string temp, temp2; 
    
    for (i = 0; i < len; i++) { 

        j = int(S[i]) - 65; 

        temp = NFA_TABLE[j*(symbols+1) + M];

        if (temp[0] != '-') { 
            sz = temp.length(); 
            g = 0; 

            while (g < sz) { 
                k = int(temp[g]) - 65; 

                temp2 = getElement(closure_table, k);
                check(arr, temp2);
                g++; 
            } 
        } 
    } 

    temp = state(arr, states, temp);
    if (temp != "\0") { 
        T_buf = temp;
    } else {
        T_buf = "-";
    }
	
}
// to check new state in DFA
int new_states(struct DFA *dfa, string S) { 

    int i; 

    for (i = 0; i < last_index; i++) { 
        if (dfa[i].states == S) {
            return 0; 
        }
        
    } 
    dfa[last_index++].states = S;

    dfa[last_index - 1].count = 0; 
    return 1; 
}

// transit FA to DFA
void Trans(int states, int symbols, string stateList, string *dfaStates) { 


    string NFA_TABLE[states][symbols + 1];
    string DFA_TABLE[100][symbols];

    DFA *dfa_states;
    dfa_states = new DFA[100];

    string *listStates = split(stateList, '|');

    for(int i = 0; i< states; i++) {
        string *eachState = split(listStates[i], '.');
        for(int j = 0; j < symbols + 1; j++) {
            NFA_TABLE[i][j] = eachState[j];
        }
    }

    int closure_ar[states]; 
    closure_table_list *closure_table;
    closure_table = new closure_table_list;
    closure_table->n = 0;


    getClosure(states, symbols, (string*)NFA_TABLE, closure_table);

    dfa_states[last_index++].states = "-";

    dfa_states[last_index - 1].count = 1;

    buffer = getElement(closure_table, 0);

    dfa_states[last_index++].states = buffer;

    int Sm = 1, ind = 1; 
    int start_index = 1;
    int count = 0;

    while (ind != -1) { 
        dfa_states[start_index].count = 1; 
        
        for (int i = 0; i < symbols; i++) { 

            trans(buffer, i, closure_table, states, symbols, (string*)NFA_TABLE, T_buf);

            DFA_TABLE[count][i] = T_buf;

            new_states(dfa_states, T_buf); 
        }
        
        ind = indexing(dfa_states);

        if (ind != -1) {
            buffer = dfa_states[++start_index].states; 
        }
        count++;
    }

    *dfaStates = *dfaStates + to_string(count) + "#";
    for(int i = 0; i < count; i++) {
        *dfaStates = *dfaStates + dfa_states[i+1].states;
        if(i < count - 1) {
            *dfaStates = *dfaStates + ".";
        }
    }
    *dfaStates = *dfaStates + "#";

    for(int i = 0; i< count; i++) {

        for(int j = 0; j< symbols; j++) {
            *dfaStates = *dfaStates + DFA_TABLE[i][j];
            if(j < symbols - 1) {
                *dfaStates = *dfaStates + ".";
            }
            
        }
        if(i < count - 1) {
            *dfaStates = *dfaStates + "|";
        }
    }

    buffer.clear();
    T_buf.clear();
    last_index = 0;

}

#endif