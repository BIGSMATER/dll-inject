#include<iostream>
#include"inject.h"

int main(int argc, char* argv[])
{
	//if (argc != 3)
	//{
	//	std::cout << "<xxx.exe> <xxx.dll>" << std::endl;
	//	return -1;
	//}
	//Inject inject(argv[1],argv[2]);

	char pPath[200];
	std::cin >> pPath;
#ifndef _WIN64
	char dPath[200];
	std::cin >> dPath;
#else
	WCHAR dPath[200];
	std::wcin >> dPath;
#endif
	
	Inject inject(pPath, dPath);
	DWORD pid = inject.GetTargetProcessId();
	if (!pid)
	{
		std::cout << "no this process" << std::endl;
		return -1;
	}
	inject.DLLInject();
	
	return 0;
}