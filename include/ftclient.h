#ifndef _FIRETUBE_CLIENTG_H_
#define _FIRETUBE_CLIENTG_H_

#include "ftbase.h"

namespace FT_NS{

class FireTubeClient : public FireTubeBase
{
private:
public:
    FireTubeClient(std::string name);
    ~FireTubeClient();

    ResultStatus init() override;
};


}

#endif