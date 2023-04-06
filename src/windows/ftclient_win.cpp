#include "ftclient.h"

#include <Windows.h>


FT_NS::ResultStatus FT_NS::FireTubeClient::init()
{
    if (WaitNamedPipeA(this->getName().c_str(), NMPWAIT_WAIT_FOREVER) == FALSE)
	{
		return ResultStatus::RS_REMOTE_CLOSE;
	}
 
	HANDLE hPipe = CreateFileA(this->getName().c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hPipe);
		return ResultStatus::RS_FAULT;
	}
	this->m_tube = hPipe;
	this->m_status = TubeStatus::TS_READY;
    return FT_NS::ResultStatus::RS_SUCCESS;
}