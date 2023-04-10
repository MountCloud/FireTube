#include "ftserver.h"
#include <memory.h>
#include <iostream>
#include <string>
#include <fstream>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <cstdio>
#include <string.h>
#endif

using namespace std;

string getExeDir(){
#ifdef _WIN32
	char exepathc[MAX_PATH + 1] = { 0 };
	GetModuleFileNameA(NULL, exepathc, (MAX_PATH + 1));

	string exepath = exepathc;
	int pos = exepath.find_last_of("\\", exepath.length());
	std::string exedir = exepath.substr(0, pos + 1);
	return exedir;
#else
    char pdir[512];
	char pname[512];
	
	char* path_end;
    readlink("/proc/self/exe", pdir,512);

	string exepath = pdir;

    path_end = strrchr(pdir,  '/');
    ++path_end;
    strcpy(pname, path_end);
    *path_end = '\0';

    string exedir = pdir;
    exedir.append("/");
	return exedir;
#endif
}


int main(){

    string filepath = getExeDir() + "test.txt";
    ifstream fs;
    fs.open(filepath);
    if(!fs.is_open()){
        cout << "file open fail." << endl;
        return -1;
    }

    bool datacheck = true;

    cout << "start check..." << endl;

    string temp;
    while(getline(fs,temp)){
        //1:check thread id
        int indx = temp.find_first_of('_');
        if(indx <=0 ){
            cout << "data check fail..." << endl;
            datacheck = false;
            break;
        }
        string tid = temp.substr(0,indx);
        bool check = true;
        for(int i=0;i<tid.size();i++){
            int tc = (int)tid[i];
            if(tc<48||tc>57){
                check = false;
                break;
            }
        }
        if(!check){
            cout << "data check fail..." << endl;
            datacheck = false;
            break;
        }
        //2:check end str
        string dataend = "</menu>";
        string tempend = temp.substr(temp.size() - dataend.size(),dataend.size());
        if(dataend != tempend){
            cout << "data check fail..." << endl;
            datacheck = false;
            break;
        }
    }

    if(datacheck == true){
        cout << "data check success!!" << endl;
    }

    fs.close();
#ifdef _WIN32
	system("pause");
#else
	cout << "Press Enter to Continue..." << endl;
	char ccc = getchar();
#endif
    return 0;
}