#include "ftserver.h"

FT_NS::FireTubeServer::FireTubeServer(std::string name) : FireTubeBase(name)
{
}

FT_NS::FireTubeServer::~FireTubeServer()
{
}

//create server
FT_NS::FireTubeServer* FT_NS::FireTubeServer::createServer(std::string name,ResultStatus* status)
{
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
    //return server
    return server;
}
