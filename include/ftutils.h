#ifndef _FIRETUBE_UTILS_H_
#define _FIRETUBE_UTILS_H_

#include "ftdef.h"

#include <string>

//platform pipe prefix
#ifdef _WIN32
#define FT_PIPE_PREFIX "\\\\.\\pipe\\"
#else
#define FT_PIPE_PREFIX "/tmp/"
#endif

namespace FT_NS{//namespace FT_NS start

class FireTubeUtils
{
public:
    static std::string getTubeName(std::string name);
};
    
}//namespace FT_NS end

#endif