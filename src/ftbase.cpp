#include "ftbase.h"
#include "ftutils.h"

//constructor
FT_NS::FireTubeBase::FireTubeBase(std::string name)
{
    this->m_name = name;
}

//destructor
FT_NS::FireTubeBase::~FireTubeBase()
{
    close();
}

//get name
std::string FT_NS::FireTubeBase::getName()
{
    return FT_NS::FireTubeUtils::getTubeName(this->m_name);
}

//get status
FT_NS::TubeStatus FT_NS::FireTubeBase::getStatus()
{
    return this->m_status;
}


//init empty func
FT_NS::ResultStatus FT_NS::FireTubeBase::init(){
    return ResultStatus::RS_SUCCESS;
}