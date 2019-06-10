#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include<dirent.h>

using namespace std;

class LoadFile { 
    public: 
  
    string list[100];
    int total;

    LoadFile() {
        total = 0;
    }

    void getListFile() {
        DIR *pDIR;
        struct dirent *entry;
        int i = 0;
        pDIR = opendir("./data");

        if(pDIR) {

            entry = readdir(pDIR);
            
            while(entry != NULL){
                if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ) {

                    string file = entry->d_name;
                    int length = file.length();

                    string file_ext = file.substr(length - 3);
                    string file_name = file.substr(0, length - 3);

                    if(file_ext == ".fa") {
                        LoadFile::list[i] = file;
                        LoadFile::total++;
                        i++;
                    }
                    
                }  
                entry = readdir(pDIR);  
            }
            closedir(pDIR);

        } else {
            cout<<"Directory not found."<<endl;
        }
    }

};

string loadFile () {

    int temp;
    string c;
    LoadFile load_file;

    load_file.getListFile();

    if(load_file.total > 0) {
        for(int i = 0; i < load_file.total; i++) {
            cout<<i+1<<". "<<load_file.list[i]<<endl;
        }
        cout<<endl;
        while(true) {
            cout<<"Please choose your file: ";
            cin>>temp;
            if(temp > 0 && temp <= load_file.total) {
                return load_file.list[temp - 1];
            }
        }
    } else {
        cout<<"There is no FA file in the folder."<<endl;
        cout<<"Enter e to exit: ";
        cin>>c;
        return "no";
    }
}

