#include "firetube.h"

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <string>
using namespace std;

//tube name
#define TUBE_NAME "testtube"

//tube client
void main(){
	firetube::FireTube tube = firetube::FireTube();

	//create firetube client
	firetube::ResultStatus createResult = firetube::ResultStatus::RS_SUCCESS;
	firetube::FireTubeClient* client = tube.createClient(TUBE_NAME,&createResult);
	//check if client is null
	if (client == NULL)
	{
		cout << "create client fail." << endl;
		system("pause");
		return;
	}

	//client read data onece
	char buffer[1024];
	int readNum = 0;
	//recv data
	readNum = tube.readClientData(client,buffer,1024);

	//print string buffer
	cout << "data:" << buffer << endl;


	//send buffer to server
	while(1){
		gets_s(buffer, 1024);
		string input = buffer;
		tube.writeClientData(client, buffer, strlen(buffer));
		//client->write(buffer, strlen(buffer));
		
		if(input == "exit"){
			break;
		}
		memset(buffer, 0, 1024);
	}
	//close client
	tube.closeClient(client);
	system("pause");
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