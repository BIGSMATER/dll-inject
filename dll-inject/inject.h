#pragma once
#include<Windows.h>
class Inject
{
public:
	Inject(char* pPath,char* dPath);
	Inject(char* pPath, WCHAR* dPath);
	DWORD GetTargetProcessId();
	void DLLInject();
private:
	char* pPath;
#ifndef _WIN64
	char* dPath;
#else
	WCHAR* dPath;
#endif
	
	DWORD pid;
};