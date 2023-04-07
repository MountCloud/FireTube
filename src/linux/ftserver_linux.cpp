#include "ftserver.h"

#include <error.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <thread>
#include <mutex>

FT_NS::ResultStatus FT_NS::FireTubeServer::init(){

    FT_NS::ResultStatus ret = FT_NS::FireTubeBase::init();
    if(ret!=FT_NS::ResultStatus::RS_SUCCESS){
        return ret;
    }

    //1=server
    ((int *)this->m_tube)[2] = 1;

    datas["initlock"] = new std::mutex();
    ((std::mutex*)datas["initlock"])->lock();

    std::thread bs([this](){
        std::mutex* mtx = (std::mutex*)this->datas["initlock"];
        //0 c2s,1 s2c,2 type:0=client/1=server
        std::string c2spipename = this->getName() + "_c2s";
        //server read only c2s
        int c2sfd = open(c2spipename.c_str(),O_RDONLY);
        if(c2sfd < 0){
            this->m_status = FT_NS::TubeStatus::TS_FAULT;
            return;
        }
        //server write only s2c
        std::string s2cspipename = this->getName() + "_s2c";
        int s2cfd = open(c2spipename.c_str(),O_WRONLY);
        if(c2sfd < 0){
            ::close(c2sfd);
            this->m_status = FT_NS::TubeStatus::TS_FAULT;
            return;
        }

        //0 c2s,1 s2c
        ((int *)this->m_tube)[0] = c2sfd;
        ((int *)this->m_tube)[1] = s2cfd;

        mtx->unlock();
        this->m_status = FT_NS::TubeStatus::TS_READY;
    });
    bs.detach();

}