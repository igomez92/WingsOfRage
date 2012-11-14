//Written by Geoffrey Tucker

#include "EngineException.h"

EngineException::EngineException(std::string message)
{
	this->message = message;
}

EngineException::~EngineException() {}