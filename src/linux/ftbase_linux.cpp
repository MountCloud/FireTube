#include "ftbase.h"

#include <error.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <mutex>

FT_NS::ResultStatus FT_NS::FireTubeBase::init(){
    //client write c2s pipe,read s2c pipe.
    //0 c2s,1 s2c,2 type:0=client/1=server
    this->m_tube = calloc(3,sizeof(int));
    //c2s
    std::string c2spipename = this->getName() + "_c2s";
    if((mkfifo(c2spipename.c_str(),0600) == -1) &&errno != EEXIST){
        return ResultStatus::RS_FAULT;
    }

    //s2c
    std::string s2cpipename = this->getName() + "_s2c";
    if((mkfifo(s2cpipename.c_str(),0600) == -1) &&errno != EEXIST){
        return ResultStatus::RS_FAULT;
    }

    return FT_NS::ResultStatus::RS_SUCCESS;
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
        if(this->m_tube!=NULL){
            int c2sfd = ((int *)this->m_tube)[0];
            int s2cfd = ((int *)this->m_tube)[1];
            if(c2sfd != 0){
                ::close(c2sfd);
            }
            if(s2cfd != 0){
                ::close(s2cfd);
            }
            delete this->m_tube;
            this->m_tube = NULL;
        }
		this->m_status = FT_NS::TubeStatus::TS_CLOSED;
		return FT_NS::ResultStatus::RS_SUCCESS;
	}
	return FT_NS::ResultStatus::RS_FAULT;
}

FT_NS::FT_SIZE FT_NS::FireTubeBase::read(char* buffer, FT_SIZE size){
    if(this->m_status == FT_NS::TubeStatus::TS_NEW){
        std::mutex* mtx = (std::mutex*)this->datas["initlock"];
        mtx->lock();
        mtx->unlock();
    }
     //if status
    if (this->m_status != FT_NS::TubeStatus::TS_READY)
    {
        //server is not ready
        return FT_NS::ResultStatus::RS_FAULT;
    }
    if(this->m_status == TubeStatus::TS_CLOSED){
        return ResultStatus::RS_LOCAL_CLOSE;
    }
    //if type type:0=client/1=server,fd type:0 c2s,1 s2c,
    int type = ((int *)this->m_tube)[2];
    int fd = 0;
    if(type == 0){
        //client fd = s2c: read server to client fd;
        fd = ((int *)this->m_tube)[1];
    }else{
        //server fd = c2s: read client to server fd;
        fd = ((int *)this->m_tube)[0];
    }
    FT_NS::FT_SIZE ret = ::read(fd,buffer,size);
    if(ret < 0){
        this->m_status = FT_NS::TubeStatus::TS_FAULT;
    }
    return ret;
}

FT_NS::FT_SIZE FT_NS::FireTubeBase::write(char* buffer, FT_SIZE size){
    if(this->m_status == FT_NS::TubeStatus::TS_NEW){
        std::mutex* mtx = (std::mutex*)this->datas["initlock"];
        mtx->lock();
        mtx->unlock();
    }
    //if status
    if (this->m_status != FT_NS::TubeStatus::TS_READY)
    {
        //server is not ready
        return FT_NS::ResultStatus::RS_FAULT;
    }
    if(this->m_status == TubeStatus::TS_CLOSED){
        return ResultStatus::RS_LOCAL_CLOSE;
    }
    //if type type:0=client/1=server,fd type:0 c2s,1 s2c,
    int type = ((int *)this->m_tube)[2];
    int fd = 0;
    if(type == 0){
        //client fd = c2s: write client to server fd;
        fd = ((int *)this->m_tube)[0];
    }else{
        //server fd = s2c: write server to client fd;
        fd = ((int *)this->m_tube)[1];
    }
    FT_NS::FT_SIZE ret = ::write(fd,buffer,size);
    if(ret < 0){
        this->m_status = FT_NS::TubeStatus::TS_FAULT;
    }
    return ret;    
}