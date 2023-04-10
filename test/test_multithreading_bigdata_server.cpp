#include "ftserver.h"
#include <memory.h>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <cstdio>
#include <string.h>
#endif

using namespace std;

//tube name
#define TUBE_NAME "testtube"

#define PKG_HEADER "mtcd"

typedef long long DATA_SIZE;


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

//tube server
int main(){

	string filepath = getExeDir() + "test.txt";
	FILE* file = fopen(filepath.c_str(),"wb");
	if(file==NULL){
		cout << "fopen fail" << endl;
		#ifdef _WIN32
		system("pause");
#else
		cout << "Press Enter to Continue..." << endl;
		char ccc = getchar();
#endif
		return -1;
	}

	//create firetube server
	firetube::ResultStatus createResult = firetube::ResultStatus::RS_SUCCESS;
	firetube::FireTubeServer* server = firetube::FireTubeServer::createServer(TUBE_NAME,&createResult);
	//check if server is null
	if (server == NULL)
	{
		cout << "create server fail." << endl;
#ifdef _WIN32
		system("pause");
#else
		cout << "Press Enter to Continue..." << endl;
		char ccc = getchar();
#endif
		return -1;
	}

	//client send data onece
	std::string hello = "hello";

	//firetube send data
	firetube::FT_SIZE size = server->write(const_cast<char*>(hello.c_str()), hello.size());
	if(server->getStatus() != firetube::TubeStatus::TS_READY){
		cout << "server status is fail!" <<endl;
		return -1;
	}

	DATA_SIZE headerSize = strlen(PKG_HEADER) + sizeof(DATA_SIZE);
	char *header = (char*) calloc(headerSize,sizeof(char));
	//while loop recv data
	while(1){
		//recv data
		int readNum = server->read(header,headerSize);//server->read(buffer, 1024);
		
		if(readNum <= 0){
			cout << "connect error" << endl;
			break;
		}

		if(memcmp(header,PKG_HEADER,strlen(PKG_HEADER))!=0){
			cout << "data format error" << endl;
			break;
		}

		DATA_SIZE* contentSize = (DATA_SIZE*)(header+strlen(PKG_HEADER));

		DATA_SIZE writeSize = *contentSize + 1;

		char* content = (char*)malloc(writeSize);

		readNum = server->read(content,*contentSize);//server->read(buffer, 1024);
		content[*contentSize] = '\n';

		if(readNum <= 0){
			cout << "connect error" << endl;
			delete content;
			break;
		}

		if(server->getStatus() != firetube::TubeStatus::TS_READY){
			cout << "server status is fail!" <<endl;
			delete content;
			break;
		}

		fwrite(content,1,writeSize,file);
		delete content;
	}

	fclose(file);

	//close server
	server->close();
	delete server;
#ifdef _WIN32
	system("pause");
#else
	cout << "Press Enter to Continue..." << endl;
	char ccc = getchar();
#endif
	return 0;	
}

