#include "handleFiles.h"
#include <fstream>
const std::string loadFile(const char* shaderSource)
{
	std::ifstream shaderFile(shaderSource);
	std::string line, data;
	while (getline(shaderFile, line))
	{
		data += line + '\n';
	}
	return data;
}
