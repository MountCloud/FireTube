#include "ftutils.h"

//get tube name
std::string FT_NS::FireTubeUtils::getTubeName(std::string name)
{
    std::string result = "";
    //if contains pipe prefix, return it
    if (name.find(FT_PIPE_PREFIX) != std::string::npos)
    {
        result = name;
    }
    else
    {
        result = FT_PIPE_PREFIX + name;
    }
    return result;
}