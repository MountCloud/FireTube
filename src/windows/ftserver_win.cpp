#include "ftserver.h"

#include <Windows.h>
#include <thread>

#include <mutex>
#include <condition_variable>

FT_NS::ResultStatus FT_NS::FireTubeServer::init(){

    HANDLE hPipe = CreateNamedPipeA(this->getName().c_str(), PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1, 0, 0, 3000, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hPipe);
        this->m_status = FT_NS::TubeStatus::TS_FAULT;
		return FT_NS::ResultStatus::RS_FAULT;
	}

	datas["initlock"] = new std::mutex();
	datas["initcv"] = new std::condition_variable();
	//backgroup thread connnect named pipe
	std::thread bt([this, hPipe](){
		if (ConnectNamedPipe(hPipe, NULL) == FALSE)
		{
			if (GetLastError() != ERROR_PIPE_CONNECTED)
			{
				CloseHandle(hPipe);
				this->m_status = TubeStatus::TS_FAULT;
				this->close();
				return;
			}
		}
		this->m_tube = hPipe;
		this->m_status = TubeStatus::TS_READY;
		((std::condition_variable*)datas["initcv"])->notify_all();
	});
	//start backgroup thread
	bt.detach();

    return FT_NS::ResultStatus::RS_SUCCESS;
}

FT_NS::ResultStatus FT_NS::FireTubeServer::close(){
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

FT_NS::FT_SIZE FT_NS::FireTubeServer::read(char* buffer, FT_NS::FT_SIZE size){
	if(this->m_status == FT_NS::TubeStatus::TS_NEW){
        std::mutex* mtx = (std::mutex*)this->datas["initlock"];
		std::condition_variable* initcv = (std::condition_variable*)datas["initcv"];
		std::unique_lock<std::mutex> lck(*mtx);
		initcv->wait(lck);
    }
    return FT_NS::FireTubeBase::read(buffer,size);
}
FT_NS::FT_SIZE FT_NS::FireTubeServer::write(char* buffer, FT_NS::FT_SIZE size){
	if(this->m_status == FT_NS::TubeStatus::TS_NEW){
        std::mutex* mtx = (std::mutex*)this->datas["initlock"];
		std::condition_variable* initcv = (std::condition_variable*)datas["initcv"];
		std::unique_lock<std::mutex> lck(*mtx);
		initcv->wait(lck);
    }
    return FT_NS::FireTubeBase::write(buffer,size);
}