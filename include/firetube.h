#ifndef _FIRETUBE_H_
#define _FIRETUBE_H_

#include "ftbase.h"
#include "ftserver.h"
#include "ftclient.h"

#include <unordered_map>

namespace FT_NS{

class FireTube
{
private:
    //servers
    std::unordered_map<std::string, FireTubeServer*> m_servers;
    //clients
    std::unordered_map<std::string, FireTubeClient*> m_clients;
public:
    FireTube();
    ~FireTube();

    //create server
    FireTubeServer* createServer(std::string name,ResultStatus* status);
    //create client
    FireTubeClient* createClient(std::string name,ResultStatus* status);

    //write server data
    FT_SIZE writeServerData(std::string name, char* data, FT_SIZE size);
    FT_SIZE writeServerData(FireTubeServer* server, char* data, FT_SIZE size);

    //write client data
    FT_SIZE writeClientData(std::string name, char* data, FT_SIZE size);
    FT_SIZE writeClientData(FireTubeClient* client, char* data, FT_SIZE size);

    //read server data
    FT_SIZE readServerData(std::string name, char* data, FT_SIZE size);
    FT_SIZE readServerData(FireTubeServer* server, char* data, FT_SIZE size);

    //read client data
    FT_SIZE readClientData(std::string name, char* data, FT_SIZE size);
    FT_SIZE readClientData(FireTubeClient* client, char* data, FT_SIZE size);

    //close one server
    ResultStatus closeServer(std::string name);
    ResultStatus closeServer(FireTubeServer* server);

    //close one client
    ResultStatus closeClient(std::string name);
    ResultStatus closeClient(FireTubeClient* client);

    //close all servers
    ResultStatus closeAllServers();

    //close all clients
    ResultStatus closeAllClients();
};

}

#endif