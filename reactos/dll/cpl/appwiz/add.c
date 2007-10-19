/*
 *  ReactOS
 *  Copyright (C) 2004 ReactOS Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
/*
 *
 * PROJECT:         		ReactOS Software Control Panel
 * FILE:            		dll/cpl/appwiz/add.c
 * PURPOSE:         		ReactOS Software Control Panel
 * PROGRAMMERS:	Gero Kuehn (reactos.filter@gkware.com)
 *				Dmitry Chapyshev (lentind@yandex.ru)
 * UPDATE HISTORY:
 *	06-17-2004  Created
 *	09-25-2007 Modify
 */

#include "appwiz.h"

BOOL
CheckDownload(VOID)
{
	TCHAR Buf[MAX_PATH];
	if(!GetSystemDirectory(Buf,MAX_PATH)) return FALSE;
	lstrcat((LPTSTR)Buf, L"\\downloader.exe");
	if (GetFileAttributes(Buf) != 0xFFFFFFFF) return TRUE;
	return FALSE;
}

BOOL
LaunchDownload(HWND hwndDlg)
{
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
	TCHAR Buf[MAX_PATH];

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if(!GetSystemDirectory(Buf,MAX_PATH)) return FALSE;
	lstrcat((LPTSTR)Buf, L"\\downloader.exe");

	if(CreateProcess(NULL,Buf,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
	{
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		return TRUE;
	}
	return FALSE;
}

/* Property page dialog callback */
INT_PTR CALLBACK
AddPageProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    UNREFERENCED_PARAMETER(wParam);
    UNREFERENCED_PARAMETER(hwndDlg);

    switch (uMsg)
    {
        case WM_INITDIALOG:
			EnableWindow(GetDlgItem(hwndDlg, IDC_INSTALL), FALSE);
			if (CheckDownload()) EnableWindow(GetDlgItem(hwndDlg, IDC_ADD_DOWNLOAD_BUTTON), TRUE);
        break;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDC_ADD_DOWNLOAD_BUTTON:
					LaunchDownload(hwndDlg);
				break;
			}
		break;
    }

    return FALSE;
}
