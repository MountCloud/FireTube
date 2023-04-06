#include "ftbase.h"

#include <Windows.h>

FT_NS::ResultStatus FT_NS::FireTubeBase::close(){
    this->m_status = TubeStatus::TS_CLOSED;
    if(m_tube!=NULL){
        CloseHandle(m_tube);
    }
    return ResultStatus::RS_SUCCESS;
}

FT_NS::FT_SIZE FT_NS::FireTubeBase::read(char* buffer, FT_SIZE size){
    if(this->m_status == TubeStatus::TS_CLOSED){
        return ResultStatus::RS_LOCAL_CLOSE;
    }
    DWORD readed = 0;
    BOOL fstate = ReadFile(m_tube, buffer, size, &readed, NULL);
    if(fstate == FALSE){
        return ResultStatus::RS_REMOTE_CLOSE;
    }
    return readed;
}

FT_NS::FT_SIZE FT_NS::FireTubeBase::write(char* buffer, FT_SIZE size){
    if(this->m_status == TubeStatus::TS_CLOSED){
        return ResultStatus::RS_LOCAL_CLOSE;
    }
    DWORD writed = 0;
    BOOL fstate = WriteFile(m_tube, buffer, size, &writed, NULL);
    if(fstate == FALSE){
        return ResultStatus::RS_REMOTE_CLOSE;
    }
    return writed;
}
