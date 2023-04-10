#include "ftserver.h"
#include <memory.h>
#include <iostream>

#ifndef _WIN32
#include <cstdio>
#endif

using namespace std;

//tube name
#define TUBE_NAME "testtube"

//tube server
int main(){


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
	char buffer[1024] = {0};
	//while loop recv data
	while(1){
		//recv data
		int readNum = server->read(buffer,1024);//server->read(buffer, 1024);
		if(server->getStatus() != firetube::TubeStatus::TS_READY){
			cout << "server status is fail!" <<endl;
			break;
		}
		if(readNum <= 0){
			cout << "connect error" << endl;
			break;
		}
		//print string buffer
		cout << "data:" << buffer << endl;

		//if recv data is exit, break loop
		string input = buffer;
		if(input == "exit"){
			break;
		}

		memset(buffer, 0, 1024);
	}

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

