#ifndef _FIRETUBE_BASE_H_
#define _FIRETUBE_BASE_H_

//namespace

#include "ftdef.h"

#include <string>

namespace FT_NS{//namespace FT_NS start

enum ResultStatus{
    RS_SUCCESS = 0,
    RS_REMOTE_CLOSE = -1,
    RS_LOCAL_CLOSE = -2,
    RS_NOT_FOUND = -3,
    
    RS_FAULT = -999999,
};

enum TubeStatus{
    TS_NEW = 0,
    TS_READY = 1,
    TS_CLOSED = 2,
    
    TS_FAULT = -999999,
};

/// @brief FireTubeBase 每个继承tube base的类都必须实现init方法，用于初始化m_tube。
class FireTubeBase{
protected:
    TubeStatus m_status = TubeStatus::TS_NEW;
    std::string m_name;
    FT_HANDLE m_tube = NULL;
public:
    FireTubeBase(std::string name);
    ~FireTubeBase();

    TubeStatus getStatus();
    std::string getName();

    virtual ResultStatus init();
    virtual ResultStatus close();

    virtual FT_SIZE read(char* buffer, FT_SIZE size);
    virtual FT_SIZE write(char* buffer, FT_SIZE size);
};

}//namespace FT_NS end


#endif