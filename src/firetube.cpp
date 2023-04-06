#include "firetube.h"

FT_NS::FireTube::FireTube()
{
}

FT_NS::FireTube::~FireTube()
{
    //close all server
    this->closeAllServers();
    //close all clients
    this->closeAllClients();
}

//create server
FT_NS::FireTubeServer* FT_NS::FireTube::createServer(std::string name,ResultStatus* status)
{
    //check if server already exists
    if (m_servers.find(name) != m_servers.end())
    {
        //server already exists
        return m_servers[name];
    }
    //create server
    FT_NS::FireTubeServer* server = new FT_NS::FireTubeServer(name);
    //check init result
    *status = server->init();
    //check if init failed
    if (*status != FT_NS::ResultStatus::RS_SUCCESS)
    {
        //delete server
        delete server;
        //return null
        return NULL;
    }
    //add server to list
    m_servers[name] = server;
    //return server
    return server;
}

//create client
FT_NS::FireTubeClient* FT_NS::FireTube::createClient(std::string name,ResultStatus* status)
{
    //check if client already exists
    if (m_clients.find(name) != m_clients.end())
    {
        //client already exists
        return m_clients[name];
    }
    //create client
    FT_NS::FireTubeClient* client = new FT_NS::FireTubeClient(name);
    //check init result
    *status = client->init();
    //check if init failed
    if (*status != FT_NS::ResultStatus::RS_SUCCESS)
    {
        //delete client
        delete client;
        //return null
        return NULL;
    }
    //add client to list
    m_clients[name] = client;
    //return client
    return client;
}

//write server data
FT_NS::FT_SIZE FT_NS::FireTube::writeServerData(std::string name, char* data, FT_SIZE size)
{
    //check if server exists
    if (m_servers.find(name) == m_servers.end())
    {
        //server does not exist
        return FT_NS::ResultStatus::RS_NOT_FOUND;
    }
    //get server 
    FT_NS::FireTubeServer* server = m_servers[name];
    
    //if server status
    if (server->getStatus() != FT_NS::TubeStatus::TS_READY)
    {
        //server is not ready
        return FT_NS::ResultStatus::RS_FAULT;
    }

    //write data
    return server->write(data, size);
}
//write server data
FT_NS::FT_SIZE FT_NS::FireTube::writeServerData(FT_NS::FireTubeServer* server, char* data, FT_SIZE size)
{
    //if server status
    if (server->getStatus() != FT_NS::TubeStatus::TS_READY)
    {
        //server is not ready
        return FT_NS::ResultStatus::RS_FAULT;
    }

    //write data
    return server->write(data, size);
}

//write client data
FT_NS::FT_SIZE FT_NS::FireTube::writeClientData(std::string name, char* data, FT_SIZE size)
{
    //check if client exists
    if (m_clients.find(name) == m_clients.end())
    {
        //client does not exist
        return FT_NS::ResultStatus::RS_NOT_FOUND;
    }
    //get client 
    FT_NS::FireTubeClient* client = m_clients[name];

    //if client status
    if (client->getStatus() != FT_NS::TubeStatus::TS_READY)
    {
        //client is not ready
        return FT_NS::ResultStatus::RS_FAULT;
    }

    //write data
    return client->write(data, size);
}
//write client data
FT_NS::FT_SIZE FT_NS::FireTube::writeClientData(FT_NS::FireTubeClient* client, char* data, FT_SIZE size)
{
    //if client status
    if (client->getStatus() != FT_NS::TubeStatus::TS_READY)
    {
        //client is not ready
        return FT_NS::ResultStatus::RS_FAULT;
    }

    //write data
    return client->write(data, size);
}

//read server data
FT_NS::FT_SIZE FT_NS::FireTube::readServerData(std::string name, char* data, FT_SIZE size)
{
    //check if server exists
    if (m_servers.find(name) == m_servers.end())
    {
        //server does not exist
        return FT_NS::ResultStatus::RS_NOT_FOUND;
    }
    //get server 
    FT_NS::FireTubeServer* server = m_servers[name];

    //if server status
    if (server->getStatus() != FT_NS::TubeStatus::TS_READY)
    {
        //server is not ready
        return FT_NS::ResultStatus::RS_FAULT;
    }

    //read data
    return server->read(data, size);
}
//read server data
FT_NS::FT_SIZE FT_NS::FireTube::readServerData(FT_NS::FireTubeServer* server, char* data, FT_SIZE size)
{
    //if server status
    if (server->getStatus() != FT_NS::TubeStatus::TS_READY)
    {
        //server is not ready
        return FT_NS::ResultStatus::RS_FAULT;
    }

    //read data
    return server->read(data, size);
}

//read client data
FT_NS::FT_SIZE FT_NS::FireTube::readClientData(std::string name, char* data, FT_SIZE size)
{
    //check if client exists
    if (m_clients.find(name) == m_clients.end())
    {
        //client does not exist
        return FT_NS::ResultStatus::RS_NOT_FOUND;
    }
    //get client 
    FT_NS::FireTubeClient* client = m_clients[name];

    //if client status
    if (client->getStatus() != FT_NS::TubeStatus::TS_READY)
    {
        //client is not ready
        return FT_NS::ResultStatus::RS_FAULT;
    }

    //read data
    return client->read(data, size);
}

//read client data
FT_NS::FT_SIZE FT_NS::FireTube::readClientData(FT_NS::FireTubeClient* client, char* data, FT_SIZE size)
{
    //if client status
    if (client->getStatus() != FT_NS::TubeStatus::TS_READY)
    {
        //client is not ready
        return FT_NS::ResultStatus::RS_FAULT;
    }

    //read data
    return client->read(data, size);
}

//close one server
FT_NS::ResultStatus FT_NS::FireTube::closeServer(std::string name)
{
    //check if server exists
    if (m_servers.find(name) == m_servers.end())
    {
        //server does not exist
        return FT_NS::ResultStatus::RS_NOT_FOUND;
    }
    //get server 
    FT_NS::FireTubeServer* server = m_servers[name];
    //close server
    server->close();
    //delete server
    delete server;
    //remove server from map
    m_servers.erase(name);
    //return success
    return FT_NS::ResultStatus::RS_SUCCESS;
}
//close one server
FT_NS::ResultStatus FT_NS::FireTube::closeServer(FT_NS::FireTubeServer* server)
{
    //server name
    std::string name = server->getName();
    //remove server from map
    m_servers.erase(name);

    //close server
    server->close();
    //delete server
    delete server;
    //return success
    return FT_NS::ResultStatus::RS_SUCCESS;
}

//close one client
FT_NS::ResultStatus FT_NS::FireTube::closeClient(std::string name)
{
    //check if client exists
    if (m_clients.find(name) == m_clients.end())
    {
        //client does not exist
        return FT_NS::ResultStatus::RS_NOT_FOUND;
    }
    //get client 
    FT_NS::FireTubeClient* client = m_clients[name];
    //close client
    client->close();
    //delete client
    delete client;
    //remove client from map
    m_clients.erase(name);
    //return success
    return FT_NS::ResultStatus::RS_SUCCESS;
}
//close one client
FT_NS::ResultStatus FT_NS::FireTube::closeClient(FT_NS::FireTubeClient* client)
{
    //client name
    std::string name = client->getName();
    //remove client from map
    m_clients.erase(name);

    //close client
    client->close();
    //delete client
    delete client;
    //return success
    return FT_NS::ResultStatus::RS_SUCCESS;
}

//close all servers
FT_NS::ResultStatus FT_NS::FireTube::closeAllServers()
{
    //close all servers
    for (auto& server : m_servers)
    {
        //close server
        server.second->close();
        //delete server
        delete server.second;
    }
    //clear map
    m_servers.clear();
    //return success
    return FT_NS::ResultStatus::RS_SUCCESS;
}

//close all clients
FT_NS::ResultStatus FT_NS::FireTube::closeAllClients()
{
    //close all clients
    for (auto& client : m_clients)
    {
        //close client
        client.second->close();
        //delete client
        delete client.second;
    }
    //clear map
    m_clients.clear();
    //return success
    return FT_NS::ResultStatus::RS_SUCCESS;
}