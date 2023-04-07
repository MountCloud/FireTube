#include "ftserver.h"
#include <memory.h>
#include <iostream>
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
		system("pause");
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
	system("pause");
	return 0;
}


// #define PIPE_NAME "\\\\.\\Pipe\\test" 
// void main()
// {
// 	char buffer[1024];
// 	DWORD ReadNum;
 
// 	HANDLE hPipe = CreateNamedPipeA(PIPE_NAME, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1, 0, 0, 1000, NULL);
// 	if (hPipe == INVALID_HANDLE_VALUE)
// 	{
// 		cout << "CreateNamedPipeA fail" << endl;
// 		CloseHandle(hPipe);
// 		return;
// 	}
 
// 	if (ConnectNamedPipe(hPipe, NULL) == FALSE)
// 	{
// 		cout << "connect client fail." << endl;
// 		CloseHandle(hPipe);
// 		return;
// 	}
// 	cout << "client connect success." << endl;
 
// 	while (1)
// 	{
// 		if (ReadFile(hPipe, buffer, 1024, &ReadNum, NULL) == FALSE)
// 		{
// 			cout << "read data fail." << endl;
// 			break;
// 		}
			
// 		buffer[ReadNum] = 0;
// 		cout << "data:" << buffer << endl;
// 	}
 
// 	cout << "close." << endl;
// 	CloseHandle(hPipe);
// 	system("pause");
// }