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
		system("pause");
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

	//print string buffer
	cout << "data:" << buffer << endl;

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
	system("pause");
	return 0;
}
// void  main()
// {
// 	char buffer[1024];
// 	DWORD WriteNum;
 
// 	if (WaitNamedPipeA(PIPE_NAME, NMPWAIT_WAIT_FOREVER) == FALSE)
// 	{
// 		cout << "WaitNamedPipeA fail." << endl;
// 		return;
// 	}
 
// 	HANDLE hPipe = CreateFileA(PIPE_NAME, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
// 	if (hPipe == INVALID_HANDLE_VALUE)
// 	{
// 		cout << "CreateFileA fail." << endl;
// 		CloseHandle(hPipe);
// 		return;
// 	}
// 	cout << "connect server success." << endl;
// 	while (1)
// 	{
//         gets_s(buffer, 1024);
//         string input = buffer;
//         if(input == "exit"){
//             break;
//         }
// 		if (WriteFile(hPipe, buffer, strlen(buffer), &WriteNum, NULL) == FALSE)
// 		{
// 			cout << "input fail." << endl;
// 			break;
// 		}
//         memset(buffer, 0, 1024);
// 	}
	
// 	cout << "close." << endl;
// 	CloseHandle(hPipe);
// 	system("pause");
// }