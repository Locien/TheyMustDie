// ©Kris and Tashhhh 2023

#pragma once

#include "CoreMinimal.h"
#include <stdarg.h>
#include <string>

/**
 * 
 */
class THEYMUSTDIE_API Debug
{
public:
	Debug();
	~Debug();

	//Prints and logs a debug message. Only works in editor, not in shipping build.
	static void DebugMessage(const char *Format, ...);

	//Prints and logs a warning message. Only prints in editor, but will log in shipping build.
	static void WarningMessage(const char *Format, ...);

	//Prints and logs an error message. Only prints in editor, but will log in shipping build.
	static void ErrorMessage(const char *Format, ...);
	
};
