#pragma once
#include <string>
#include <fstream>
#include <sstream>
std::pair<const std::string, const std::string> loadShader(const char* shaderSource)
{
	std::ifstream shaderFile(shaderSource);
	std::stringstream data[2];
	std::string line;
	enum ShaderTypes
	{
		NONE=-1,
		VERTEX,
		FRAGMENT
	};
	ShaderTypes type = NONE;
	while (getline(shaderFile, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("fragment") != std::string::npos)
				type = FRAGMENT;
			else if (line.find("vertex") != std::string::npos)
				type = VERTEX;
			else if (line.find("none") != std::string::npos)
				type = NONE;
		}
		else
		{
			switch (type)
			{
				case NONE:
					break;
				case FRAGMENT:
				case VERTEX:
					data[type] << line << std::endl;
					break;
				default:
					break;
			}
		}
	}
	shaderFile.close();
	return { data[0].str(), data[1].str() };
}
