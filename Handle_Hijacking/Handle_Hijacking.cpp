
/*
MIT License

Copyright (c) 2024 Musaed

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <Windows.h>
#include <iostream>



namespace Globals
{
	DWORD dwProcessId;
	HANDLE hProcess = nullptr;
	HWND hWindow;
	const char* ProcessWindow = "Spotify Premium";


	HANDLE hCurrentProcess;
	HANDLE hDuplicateHandle = nullptr;

}


int main()
{
	while (Globals::hWindow == NULL)
	{
		Globals::hWindow = FindWindowA(NULL, Globals::ProcessWindow);
		Sleep(100);
	}
	
	GetWindowThreadProcessId(Globals::hWindow, &Globals::dwProcessId);
	if (!Globals::dwProcessId)
	{
		printf("Cannot find dwProcessId\n");
	}
	else
	{
		printf("dwProcessId found %d", Globals::dwProcessId);
	}

	Globals::hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, Globals::dwProcessId);
	if (!Globals::hProcess)
	{
		printf("\nCannot open the process");
	}
	else
	{
		printf("\nhProcess opened with handle: %p", Globals::hProcess);
	}

	Globals::hCurrentProcess = GetCurrentProcess();

	if (!DuplicateHandle(Globals::hCurrentProcess, Globals::hProcess, Globals::hCurrentProcess, &Globals::hDuplicateHandle, 0, FALSE, DUPLICATE_SAME_ACCESS))
	{
		std::cout << "Cannot duplicate handle " << GetLastError() << std::endl;
	}
	else
	{
		printf("\nHandle created %p", Globals::hDuplicateHandle);
	}

	printf("\nProcess Information:");
	printf("\nProcessId: %d", Globals::dwProcessId);
	printf("\nProcess Window: %s", Globals::ProcessWindow);
	printf("\nProcess New Handle: %p", Globals::hDuplicateHandle);
	std::cout << "" << std::endl;
	

	system("pause");
}