#include "ftserver.h"

#include <Windows.h>
#include <thread>

FT_NS::ResultStatus FT_NS::FireTubeServer::init(){

    HANDLE hPipe = CreateNamedPipeA(this->getName().c_str(), PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1, 0, 0, 3000, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hPipe);
        this->m_status = FT_NS::TubeStatus::TS_FAULT;
		return FT_NS::ResultStatus::RS_FAULT;
	}

		//backgroup thread connnect named pipe
	std::thread t([this, hPipe](){
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
	});
	//start backgroup thread
	t.detach();

    return FT_NS::ResultStatus::RS_SUCCESS;
}

//close
FT_NS::ResultStatus FT_NS::FireTubeServer::close()
{
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

		this->m_status = FT_NS::TubeStatus::TS_CLOSED;
		return FT_NS::ResultStatus::RS_SUCCESS;
	}
	return FT_NS::ResultStatus::RS_FAULT;
}