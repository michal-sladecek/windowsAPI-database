// babiakAmbulancia.cpp : Defines the entry point for the application.
//

#pragma comment(linker,"\"/manifestdependency:type='win32' \ name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \ processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "stdafx.h"
#include "babiakAmbulancia.h"

#include "Backup.h"
#include "resource.h"
#include "Vyhladavanie.h"
#include "Authentification.h"
#include "Pacientka.h"
#include "Databaza.h"
#include "DatabazaAPacienti.h"
#include <Strsafe.h>
#include <commctrl.h>
#define MAX_LOADSTRING 100
#define IDM_DATABAZA_LIST 103
#define C_COLUMNS 7
static Databaza hlavnaDatabaza;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void HandleWM_NOTIFY(LPARAM lParam);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND CreateListView(HWND hwndParent, std::vector<Pacientka>);
BOOL InsertListViewItems(HWND hWndListView);
BOOL InitListViewColumns(HWND hWndListView);
void showDatabaza(HWND hWnd, HWND & listView, std::vector<Pacientka>);



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

	/* The first thing we want to do is to show a dialog box about authentification, if it fails we stop the application */

	
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
#ifdef NDEBUG

	AuthentificateDialog(hInst);
	if (!is_authentificated()) {
		return FALSE;
	}
#endif //NDEBUG	

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BABIAKAMBULANCIA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BABIAKAMBULANCIA));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BABIAKAMBULANCIA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BABIAKAMBULANCIA);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

std::vector<Pacientka> toShowInListView;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND listView = NULL;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case ID_DATABAZA:
				showDatabaza(hWnd, listView, hlavnaDatabaza.as_list());
				break;
			case ID_ODHLASENIE:
				DestroyWindow(hWnd);
				break;
			case ID_VYHLADAVANIE:
			{
				BOOL ok = false;
				std::vector<Pacientka> najdene = vyhladavaciDialog(&hlavnaDatabaza,ok);
				if(ok==TRUE)
					showDatabaza(hWnd, listView, najdene);
			}
				break;
			case ID_ZALOHA:
				BackupDialog(&hlavnaDatabaza);
				showDatabaza(hWnd, listView, hlavnaDatabaza.as_list());
				break;
			case ID_NOVYPACIENT:
				NovyPacientDialog(&hlavnaDatabaza);
				showDatabaza(hWnd, listView, hlavnaDatabaza.as_list());
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_NOTIFY:
		switch (LOWORD(wParam)) {
		case IDM_DATABAZA_LIST:
			HandleWM_NOTIFY(lParam);
			break;
		}
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

HWND CreateListView(HWND hwndParent, std::vector<Pacientka> toShow)
{
	toShowInListView = toShow;
	INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	icex.dwSize = sizeof(icex);
	if(InitCommonControlsEx(&icex) == FALSE) MessageBox(NULL,L"Initiation of common controls failed",L"Fail", MB_OK);

	RECT rcClient;                       // The parent window's client area.

	GetClientRect(hwndParent, &rcClient);

	// Create the list-view window in report view with label editing enabled.
	HWND hWndListView = CreateWindow(WC_LISTVIEW,
		L"",
		WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
		0, 0,
		rcClient.right - rcClient.left,
		rcClient.bottom - rcClient.top,
		hwndParent,
		(HMENU)IDM_DATABAZA_LIST,
		hInst,
		NULL);

	return (hWndListView);
}
BOOL InitListViewColumns(HWND hWndListView)
{
	WCHAR szText[256];     // Temporary buffer.
	LVCOLUMN lvc;
	memset(&lvc, 0, sizeof(lvc));
	int iCol;

	// Initialize the LVCOLUMN structure.
	// The mask specifies that the format, width, text,
	// and subitem members of the structure are valid.
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	// Add the columns.
	for (iCol = 0; iCol < C_COLUMNS; iCol++)
	{
		lvc.iSubItem = iCol;
		lvc.pszText = szText;
		lvc.cx = 100;               // Width of column in pixels.

		if (iCol < 2)
			lvc.fmt = LVCFMT_LEFT;  // Left-aligned column.
		else
			lvc.fmt = LVCFMT_RIGHT; // Right-aligned column.

									// Load the names of the column headings from the string resources.
		LoadString(hInst,
			IDS_COLUMN1 + iCol,
			szText,
			sizeof(szText) / sizeof(szText[0]));

		// Insert the columns into the list view.
		if (ListView_InsertColumn(hWndListView, iCol, &lvc) == -1)
			return FALSE;
	}

	return TRUE;
}
void showDatabaza(HWND hWnd, HWND & listView, std::vector<Pacientka> V)
{
	DestroyWindow(listView);
	listView = CreateListView(hWnd, V);
	if (!listView) MessageBox(NULL, L"Creating list view failed", L"Fail", MB_OK);
	else if (InitListViewColumns(listView) == FALSE) MessageBox(NULL, L"Adding items failed", L"Fail", MB_OK);
	else if (InsertListViewItems(listView) == FALSE)  MessageBox(NULL, L"Adding columns failed", L"Fail", MB_OK);
}
BOOL InsertListViewItems(HWND hWndListView)
{
	int cItems = toShowInListView.size();
	LVITEM lvI;
	memset(&lvI, 0, sizeof(lvI));
	// Initialize LVITEM members that are common to all items.
	lvI.pszText = LPSTR_TEXTCALLBACK; // Sends an LVN_GETDISPINFO message.
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvI.stateMask = 0;
	lvI.iSubItem = 0;
	lvI.state = 0;

	// Initialize LVITEM members that are different for each item.
	for (int index = 0; index < cItems; index++)
	{
		lvI.iItem = index;
		lvI.iImage = index;

		// Insert items into the list.
		if (ListView_InsertItem(hWndListView, &lvI) == -1)
			return FALSE;
	}

	return TRUE;
}
void HandleWM_NOTIFY(LPARAM lParam)
{
	NMLVDISPINFO* plvdi;

	switch (((LPNMHDR)lParam)->code)
	{
	case LVN_GETDISPINFO:

		plvdi = (NMLVDISPINFO*)lParam;
		if (plvdi->item.iItem >= toShowInListView.size())break;
		switch (plvdi->item.iSubItem)
		{
		case 0:
			StringCchCopy(plvdi->item.pszText, plvdi->item.cchTextMax, toShowInListView[plvdi->item.iItem].getMeno().c_str());
			break;
		case 1:
			StringCchCopy(plvdi->item.pszText, plvdi->item.cchTextMax, toShowInListView[plvdi->item.iItem].getRodneCislo().c_str());
			break;
		case 2:
			StringCchCopy(plvdi->item.pszText, plvdi->item.cchTextMax, toShowInListView[plvdi->item.iItem].getTelCislo().c_str());
			break;
		case 3:
			StringCchCopy(plvdi->item.pszText, plvdi->item.cchTextMax, toShowInListView[plvdi->item.iItem].getZmluvnaPoistovna().c_str());
			break;
		case 4:
			StringCchCopy(plvdi->item.pszText, plvdi->item.cchTextMax, toShowInListView[plvdi->item.iItem].getZmluvnyLekar().c_str());
			break;
		case 5:
			StringCchCopy(plvdi->item.pszText, plvdi->item.cchTextMax, toShowInListView[plvdi->item.iItem].getPoznamka().c_str());
			break;
		case 6:
			StringCchCopy(plvdi->item.pszText, plvdi->item.cchTextMax, toShowInListView[plvdi->item.iItem].getIDstr().c_str());
			break;
		default:
			break;
		}

		break;

	}
	return;
}