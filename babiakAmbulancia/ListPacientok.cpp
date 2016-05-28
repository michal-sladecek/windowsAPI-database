#include "stdafx.h"
#include "resource.h"

#include <vector>
#include <string>
#include <Strsafe.h>
#include "Pacientka.h"
#include "Databaza.h"
#include "ListPacientok.h"


static std::vector<Pacientka> toShowInListView;
extern HINSTANCE hInst;

HWND CreateListView(HWND hwndParent)
{

	INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	icex.dwSize = sizeof(icex);
	if (InitCommonControlsEx(&icex) == FALSE) MessageBox(NULL, L"Initiation of common controls failed", L"Fail", MB_OK);

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
	InitListViewColumns(hWndListView);
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
void resize(HWND parent, HWND listView) {
	RECT A;
	GetClientRect(parent, &A);
	SetWindowPos(listView, 0, 0, 0, A.right, A.bottom, SWP_NOZORDER);
}
void showDatabaza(HWND hWnd, HWND & listView, std::vector<Pacientka> V)
{
	if(listView == NULL)
		listView = CreateListView(hWnd);
	ListView_DeleteAllItems(listView);
	toShowInListView = V;
	if (!listView) MessageBox(NULL, L"Creating list view failed", L"Fail", MB_OK);
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