#ifndef _FIRETUBE_SERVER_H_
#define _FIRETUBE_SERVER_H_

#include "ftbase.h"

namespace FT_NS{

class FireTubeServer : public FireTubeBase
{
private:
public:
    FireTubeServer(std::string name);
    ~FireTubeServer();

    static FireTubeServer* createServer(std::string name,ResultStatus* status);

    ResultStatus init() override;

    ResultStatus close() override;
};


}

#endif