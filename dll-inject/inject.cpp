#include"inject.h"
#include <TlHelp32.h> 
#include <comdef.h>
#include<iostream>
Inject::Inject(char* p,char* d)
{
	pPath = p;
	dPath = d;
	pid = 0;
}
DWORD Inject::GetTargetProcessId()
{
	HANDLE hsnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hsnapshot == INVALID_HANDLE_VALUE)
	{
		std::cout << "Create TlHelp32 Error!" << std::endl;
		return -1;
	}

	PROCESSENTRY32 processer;
	processer.dwSize = sizeof(PROCESSENTRY32);

	DWORD flag = Process32First(hsnapshot, &processer);
	while (flag != 0)
	{
		_bstr_t processName(processer.szExeFile);  //WCHAR字符串转换成CHAR字符串
		if (strcmp(processName, pPath) == 0)
		{
			pid = processer.th32ProcessID;        //返回进程ID
			return pid;
		}
		flag = Process32Next(hsnapshot, &processer);
	}

	CloseHandle(hsnapshot);
	return 0;
}
void Inject::DLLInject()
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);//获取目标进程句柄
	LPVOID Address = VirtualAllocEx(hProcess, NULL, 0x100, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);//在目标进程申请地址存dll路径名
	FARPROC pfnStartAssr = GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryA");//LoadLibraryW地址
	size_t pNameLong= strlen(dPath)+1;
	WriteProcessMemory(hProcess, Address, dPath, pNameLong, NULL);
	HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, (PTHREAD_START_ROUTINE)pfnStartAssr, Address, 0, NULL);
	WaitForSingleObject(hRemoteThread, -1);
	CloseHandle(hRemoteThread);
	VirtualFreeEx(hProcess, Address, 0, MEM_FREE);

}