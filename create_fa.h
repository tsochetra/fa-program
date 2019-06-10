#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string removeChar(string str, char charRemove) { 
    str.erase(remove(str.begin(), str.end(), charRemove), str.end());
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str; 
}

void write_file(string name, string data) {
	ofstream myfile;
	myfile.open ("./data/" + name + ".fa");
	myfile << data;
	myfile.close();
}

bool CreateFA(string *file) {

	int numStates, numSymbols;

	string symbols, temp, final_states;

	cout<<"Enter the total of state: ";
	cin>>numStates;
	cout<<"Enter your set of symbols (separate by comma for each symbol): ";
	cin>>temp;

	symbols = removeChar(temp, ',');
	symbols = symbols + "E";
	numSymbols = symbols.length();

	cout<<"Now, you have ";
	for(int i = 0; i < numStates; i++) {
		if(i != 0 && i < numStates - 1) {
			cout<<", ";
		} else if (i == numStates - 1) {
			cout<<" and ";
		}
		cout<<(char)(65+i);
		
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

	string FA_TABLE[numStates][numSymbols];


	for(int i = 0; i< numStates; i++) {
		if(i == 0) {
			cout<<"State A (Start State): "<<endl;
		} else {
			cout<<"State "<<(char)(65 + i)<<":"<<endl;
		}

		for(int j = 0; j< numSymbols; j++) {
			cout<<"   symbol \""<<symbols[j]<<"\" go to state: ";
			cin>>temp;
			FA_TABLE[i][j] = removeChar(temp, ',');
		}
	}

	cout<<"Enter your final state (separate by comma): ";
	cin>>temp;
	final_states = removeChar(temp, ',');
	
	
	cout<<"Your FA table summary: "<<endl;
	cout<<"   S.S\t| ";
	for(int i = 0; i< numSymbols; i++) {
		cout<<symbols[i]<<"\t";
	}
	cout<<endl;
	for(int i = 0; i< numStates; i++) {
		cout<<"   "<<(char)(65 + i)<<"\t| ";
		for(int j = 0; j< numSymbols; j++) {
			cout<<FA_TABLE[i][j]<<"\t";
		}
		cout<<endl;
	}


	while(true) {
		temp.clear();
		
		cout<<"Do you want to save this FA (Y/n): ";
		cin.get();
		getline(cin, temp);
		if(temp.empty() || temp == "Y" || temp == "y" ) {
			cout<<"Enter your FA name (no space, no special chars): ";
			cin>>temp;
			string fa;
			fa = to_string(numStates) + "." + final_states + "#" + symbols + "#";
			for(int i = 0; i< numStates; i++) {
				for(int j = 0; j< numSymbols; j++) {
					fa = fa + FA_TABLE[i][j];
					if(j < numSymbols - 1) {
						fa = fa + ".";
					}
				}
				if(i < numStates - 1) {
					fa = fa + "|";
				}
			}
			write_file(temp, fa);
			*file = temp + ".fa";
			return true;
		} else if (temp == "n" || temp == "N") {
			return false;
		}
	}

	return false;
}