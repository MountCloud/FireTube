#include "ftclient.h"

#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

//tube name
#define TUBE_NAME "testtube"

//tube client
int main(){

	firetube::ResultStatus createResult = firetube::ResultStatus::RS_SUCCESS;
	firetube::FireTubeClient* client = firetube::FireTubeClient::createClient(TUBE_NAME,&createResult);
	
	//check if client is null
	if (client == NULL)
	{
		cout << "create client fail." << endl;
#ifdef _WIN32
		system("pause");
#else
		cout << "Press Enter to Continue..." << endl;
		char ccc = getchar();
#endif
		return -1;
	}

	//client read data onece
	char buffer[1024];
	int readNum = 0;
	//recv data
	readNum = client->read(buffer,1024);
	if(client->getStatus() != firetube::TubeStatus::TS_READY){
		cout << "client status is fail!" <<endl;
		return -1;
	}
	//print hello buffer
	string hellostr = buffer;
	cout << "data:" << hellostr << endl;

	//send buffer to server
	while(1){
		std::string line;
		std::cin >> line;
		char* linestr = const_cast<char*>(line.c_str());
		client->write(linestr, line.size());
		if(client->getStatus() != firetube::TubeStatus::TS_READY){
			cout << "client status is fail!" <<endl;
			break;
		}
		//client->write(buffer, strlen(buffer));
		
		if(line == "exit"){
			break;
		}
	}
	//close client
	client->close();
	delete client;
#ifdef _WIN32
	system("pause");
#else
	cout << "Press Enter to Continue..." << endl;
	char ccc = getchar();
#endif
	return 0;
}
