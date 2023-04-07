#include "ftbase.h"

#include <Windows.h>


//init empty func
FT_NS::ResultStatus FT_NS::FireTubeBase::init(){
    return ResultStatus::RS_SUCCESS;
}

FT_NS::ResultStatus FT_NS::FireTubeBase::close(){
    //close
	if (this->m_status == FT_NS::TubeStatus::TS_CLOSED)
	{
		return FT_NS::ResultStatus::RS_SUCCESS;
	}
	if (this->m_status == FT_NS::TubeStatus::TS_FAULT)
	{
		return FT_NS::ResultStatus::RS_FAULT;
	}
	if (this->m_status == FT_NS::TubeStatus::TS_NEW)
	{
		return FT_NS::ResultStatus::RS_SUCCESS;
	}
	if (this->m_status == FT_NS::TubeStatus::TS_READY)
	{
		if (DisconnectNamedPipe(this->m_tube) == FALSE)
		{
			return FT_NS::ResultStatus::RS_FAULT;
		}
		CloseHandle(this->m_tube);
        this->m_tube = NULL:

		this->m_status = FT_NS::TubeStatus::TS_CLOSED;
		return FT_NS::ResultStatus::RS_SUCCESS;
	}
	return FT_NS::ResultStatus::RS_FAULT;
}


FT_NS::FT_SIZE FT_NS::FireTubeBase::read(char* buffer, FT_SIZE size){
     //if status
    if (this->m_status != FT_NS::TubeStatus::TS_READY)
    {
        //server is not ready
        return FT_NS::ResultStatus::RS_FAULT;
    }
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
    //if status
    if (this->m_status != FT_NS::TubeStatus::TS_READY)
    {
        //server is not ready
        return FT_NS::ResultStatus::RS_FAULT;
    }
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
