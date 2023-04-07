#include "ftclient.h"

#include <error.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <thread>
#include <mutex>
#include <condition_variable>

FT_NS::ResultStatus FT_NS::FireTubeClient::init(){

    FT_NS::ResultStatus ret = FT_NS::FireTubeBase::init();
    if(ret!=FT_NS::ResultStatus::RS_SUCCESS){
        return ret;
    }

    //0=client
    ((int *)this->m_tube)[2] = 0;

	datas["initlock"] = new std::mutex();
	datas["initcv"] = new std::condition_variable();

    std::thread bs([this](){
        std::mutex* mtx = (std::mutex*)this->datas["initlock"];
        //0 c2s,1 s2c,2 type:0=client/1=server
        std::string c2spipename = this->getName() + "_c2s";
        //client write only c2s
        int c2sfd = open(c2spipename.c_str(),O_WRONLY);
        if(c2sfd < 0){
            this->m_status = FT_NS::TubeStatus::TS_FAULT;
            return;
        }
        //client read only s2c
        std::string s2cspipename = this->getName() + "_s2c";
        int s2cfd = open(s2cspipename.c_str(),O_RDONLY);
        if(s2cfd < 0){
            ::close(c2sfd);
            this->m_status = FT_NS::TubeStatus::TS_FAULT;
            return;
        }

        //0 c2s,1 s2c
        ((int *)this->m_tube)[0] = c2sfd;
        ((int *)this->m_tube)[1] = s2cfd;

        this->m_status = FT_NS::TubeStatus::TS_READY;
		((std::condition_variable*)datas["initcv"])->notify_all();
    });
    bs.detach();
}

FT_NS::ResultStatus FT_NS::FireTubeClient::close(){
    if(this->m_status ==  FT_NS::TubeStatus::TS_CLOSED){
        return FT_NS::ResultStatus::RS_SUCCESS;
    }
    FT_NS::ResultStatus ret = FT_NS::FireTubeBase::close();
    if(ret != FT_NS::ResultStatus::RS_SUCCESS){
        return ret;
    }
    if(this->datas.find("initlock") != this->datas.end()){
        std::mutex* mtx = (std::mutex*)this->datas["initlock"];
		std::condition_variable* initcv = (std::condition_variable*)datas["initcv"];
        this->datas.erase("initlock");
        this->datas.erase("initcv");
		initcv->notify_all();
        delete mtx;
        delete initcv;
    }
    this->m_status = FT_NS::TubeStatus::TS_CLOSED;
    return FT_NS::ResultStatus::RS_SUCCESS;
}

FT_NS::FT_SIZE FT_NS::FireTubeClient::read(char* buffer, FT_NS::FT_SIZE size){
    return FT_NS::FireTubeBase::read(buffer,size);
}
FT_NS::FT_SIZE FT_NS::FireTubeClient::write(char* buffer, FT_NS::FT_SIZE size){
    return FT_NS::FireTubeBase::write(buffer,size);
}