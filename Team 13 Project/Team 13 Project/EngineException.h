//Written by Geoffrey Tucker

#include <string>

#ifndef _ENGINE_EXCEPTION_
#define _ENGINE_EXCEPTION_

class EngineException
{
public:
	EngineException(std::string message);
	~EngineException();

	std::string getMessage() { return message; }
private:
	std::string message;
};

#endif