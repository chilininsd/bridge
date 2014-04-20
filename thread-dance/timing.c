#include <stdio.h>
#include <windows.h>

DWORD WINAPI getMilliSeconds()
{
	return GetTickCount();
}

