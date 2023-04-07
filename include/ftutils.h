#ifndef _FIRETUBE_UTILS_H_
#define _FIRETUBE_UTILS_H_

#include "ftdef.h"

#include <string>

//platform pipe prefix
#ifdef _WIN32
#define FT_PIPE_PREFIX "\\\\.\\pipe\\"
#else
//linux pipe name : /tmp/pipe_test_s2c /tmp/pipe_test_c2s
//s2c = server to client
//c2s = client to server
#define FT_PIPE_PREFIX "/tmp/pipe_"
#endif

namespace FT_NS{//namespace FT_NS start

class FireTubeUtils
{
public:
    static std::string getTubeName(std::string name);
};
    
}//namespace FT_NS end

#endif