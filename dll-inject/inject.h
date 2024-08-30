#pragma once
#include<Windows.h>
class Inject
{
public:
	Inject(char* pPath,char* dPath);
	DWORD GetTargetProcessId();
	void DLLInject();
private:
	char* pPath;
	char* dPath;
	DWORD pid;
};