// ©Kris and Tashhhh 2023


#include "Debug.h"
#include "EngineMinimal.h"

Debug::Debug()
{
}

Debug::~Debug()
{
}

void Debug::DebugMessage(const char *format, ...)
{
#if WITH_EDITOR
	if(GEngine)
	{
		char buffer[256];
		va_list args;
		va_start(args, format);
		vsprintf(buffer, format, args);
		va_end(args);
		FString newstr = buffer;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, newstr);
		GLog->Log(ELogVerbosity::Log, newstr);
	}
#endif
}

void Debug::WarningMessage(const char *format, ...)
{
	if (GEngine)
	{
		char buffer[256];
		va_list args;
		va_start(args, format);
		vsprintf(buffer, format, args);
		va_end(args);
		FString newstr = buffer;
#if WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, newstr);
#endif
		GLog->Log(ELogVerbosity::Log, newstr);
	}
}

void Debug::ErrorMessage(const char* format, ...)
{
	if (GEngine)
	{
		char buffer[256];
		va_list args;
		va_start(args, format);
		vsprintf(buffer, format, args);
		va_end(args);
		FString newstr = buffer;
		FString errstr = "[ERROR] ";
		errstr.Append(newstr);
#if WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, errstr);
#endif
		GLog->Log(ELogVerbosity::Error, errstr);
	}
}
