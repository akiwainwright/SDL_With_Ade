#pragma once

#include <iostream>
#include <string>
#include <filesystem>


namespace Callbacks
{
	void LogSDLError(std::string message);

	void LogIMGError(std::string message);

	void LogMIXError(std::string message);

	std::string FileNameToString(std::filesystem::directory_entry entry);
}

