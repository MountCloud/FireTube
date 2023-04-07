#include "ftclient.h"

FT_NS::FireTubeClient::FireTubeClient(std::string name) : FireTubeBase(name)
{
}

FT_NS::FireTubeClient::~FireTubeClient()
{
}



//create client
FT_NS::FireTubeClient* FT_NS::FireTubeClient::createClient(std::string name,ResultStatus* status)
{
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
    //return client
    return client;
}
