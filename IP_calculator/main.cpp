#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include "resource.h"
#include <CommCtrl.h>
#include <iostream>

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, (DLGPROC)DlgProc, NULL);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hIPaddress = GetDlgItem(hwnd, IDC_IP_ADDRESS);
	HWND hIPmask = GetDlgItem(hwnd, IDC_IP_MASK);
	HWND hIPprefix = GetDlgItem(hwnd, IDC_EDIT_PREFIX);
	
	switch (uMsg)
	{
	case WM_INITDIALOG:
		/*InitCommonControls();*/
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		std::cout << "init" << std::endl;

		SetFocus(GetDlgItem(hwnd, IDC_IP_ADDRESS));

		SendMessage(GetDlgItem(hwnd, IDC_SPIN_PREFIX), UDM_SETRANGE, 0, MAKEWORD(30, 0));

		break;
	case WM_NOTIFY:
	{
		NMHDR* pNMHDR = (NMHDR*)lParam;

		//if (pNMHDR->idFrom == IDC_IP_MASK && pNMHDR->code == IPN_FIELDCHANGED)
		{

			DWORD dwIPmask = 0;
			DWORD dwIPprefix = 0;
			SendMessage(hIPmask, IPM_GETADDRESS, 0, (LPARAM)&dwIPmask);
			for (dwIPprefix = 0; dwIPmask; dwIPprefix++) dwIPmask <<= 1;
			CHAR szIPprefix[3] = {};
			sprintf(szIPprefix, "%i", dwIPprefix);
			SendMessage(hIPprefix, WM_SETTEXT, 0, (LPARAM)szIPprefix);

			//DWORD dwIPmask = 0;
			//DWORD dwIPprefix = 0;
			//CHAR szIPprefix[3] = {};
			//SendMessage(hIPprefix, WM_GETTEXT, 3, (LPARAM)szIPprefix);
			//dwIPprefix = atoi(szIPprefix);
			//dwIPmask = 0xFFFFFFFF;
			//for (DWORD i = 32 - dwIPprefix; i; i--)
			//{
			//	dwIPmask <<= 1;
			//}
			//SendMessage(hIPmask, IPM_SETADDRESS, 0, dwIPmask);

			/*SendMessage(hIPmask, IPM_GETADDRESS, 0, (LPARAM)&dwIPmask);
			for (dwIPprefix = 0; dwIPmask; dwIPprefix++) dwIPmask <<= 1;
			CHAR szIPprefix[3] = {};
			sprintf(szIPprefix, "%i", dwIPprefix);
			std::cout << szIPprefix << std::endl;
			SendMessage(hIPprefix, WM_SETTEXT, 0, (LPARAM)szIPprefix);*/
		}

	}
		break;
	case WM_COMMAND:
	{
			

	static DWORD dwIPaddress = 0;

		switch (LOWORD(wParam))
		{
		case IDC_IP_ADDRESS:
		{
			if(HIWORD(wParam) == EN_CHANGE)
			{


				DWORD dwIPmask = 0;
				DWORD dwIPprefix = 0;


				SendMessage(hIPaddress, IPM_GETADDRESS, 0, (LPARAM)&dwIPaddress);
				//std::cout << FIRST_IPADDRESS(dwIPaddress) << std::endl;
				if (FIRST_IPADDRESS(dwIPaddress) < 128) dwIPmask = 0xFF000000, dwIPprefix = 8;
				else if (FIRST_IPADDRESS(dwIPaddress) < 192) dwIPmask = 0xFFFF0000, dwIPprefix = 16;
				else if (FIRST_IPADDRESS(dwIPaddress) < 224) dwIPmask = 0xFFFFFF00, dwIPprefix = 24;
				
				SendMessage(hIPmask, IPM_SETADDRESS, 0, dwIPmask);
				CHAR szIPprefix[3] = {};
				sprintf(szIPprefix, "%i", dwIPprefix);
				SendMessage(hIPprefix, WM_SETTEXT, 0, (LPARAM)szIPprefix);
			}
		}
			//break;
		case IDC_IP_MASK:
		{
			if (HIWORD(wParam) == EN_CHANGE)
			{

				/*DWORD dwIPmask = 0;
				DWORD dwIPprefix = 0;
				SendMessage(hIPmask, IPM_GETADDRESS, 0, (LPARAM)&dwIPmask);
				for (dwIPprefix = 0; dwIPmask; dwIPprefix++) dwIPmask <<= 1;
				CHAR szPrefix[3] = {};
				sprintf(szPrefix, "%i", dwIPprefix);
				SendMessage(hIPprefix,)*/
			
			}
		}
			break;
		case IDC_EDIT_PREFIX:
			{
			if (HIWORD(wParam) == EN_CHANGE)
			{

				CHAR szIPprefix[3] = {};
				SendMessage(hIPprefix, WM_GETTEXT, 3, (LPARAM)szIPprefix);
				DWORD dwIPprefix = std::atoi(szIPprefix);
				DWORD dwIPmask = UINT_MAX;
				for (int i = 0; i < 32 - dwIPprefix; i++) dwIPmask <<= 1;
				SendMessage(hIPmask, IPM_SETADDRESS, 0, dwIPmask);

			}
			}
			break;
		case IDOK:
			break;
		case IDCANCEL:EndDialog(hwnd, 0);
		}
	}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
		return FALSE;
}