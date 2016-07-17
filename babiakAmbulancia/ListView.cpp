#include "stdafx.h"

#include "Pacientka.h"
#include "Databaza.h"
#include "ListView.h"


static std::vector<Patient> toShowInListView;

void ListView::Resize() {
	RECT A;
	GetClientRect(m_parent, &A);
	SetWindowPos(m_window, 0, 0, 0, A.right, A.bottom, SWP_NOZORDER);
}

void ListView::Show()
{
	ListView_DeleteAllItems(m_window);
	if(InsertListViewItems() == false)  
		MessageBox(NULL, L"List view failed", L"Fail", MB_OK);
}

void ListView::HandleWM_NOTIFY(LPARAM lParam)
{
	NMLVDISPINFO* plvdi;

	switch (((LPNMHDR)lParam)->code)
	{
	case LVN_GETDISPINFO:

		plvdi = (NMLVDISPINFO*)lParam;
		if (plvdi->item.iItem >= m_databaza->numberEntries())break;
		switch (plvdi->item.iSubItem)
		{
		case 0:
			StringCchCopy(plvdi->item.pszText, plvdi->item.cchTextMax, m_databaza->queryGet(plvdi->item.iItem).getName().c_str());
			break;
		case 1:
			StringCchCopy(plvdi->item.pszText, plvdi->item.cchTextMax, m_databaza->queryGet(plvdi->item.iItem).getBirthNumber().c_str());
			break;
		case 2:
			StringCchCopy(plvdi->item.pszText, plvdi->item.cchTextMax, m_databaza->queryGet(plvdi->item.iItem).getPhoneNumber().c_str());
			break;
		case 3:
			StringCchCopy(plvdi->item.pszText, plvdi->item.cchTextMax, m_databaza->queryGet(plvdi->item.iItem).getInsurance().c_str());
			break;
		case 4:
			StringCchCopy(plvdi->item.pszText, plvdi->item.cchTextMax, m_databaza->queryGet(plvdi->item.iItem).getDoctor().c_str());
			break;
		case 5:
			StringCchCopy(plvdi->item.pszText, plvdi->item.cchTextMax, m_databaza->queryGet(plvdi->item.iItem).getNote().c_str());
			break;
		case 6:
			StringCchCopy(plvdi->item.pszText, plvdi->item.cchTextMax, m_databaza->queryGet(plvdi->item.iItem).getIDasString().c_str());
			break;
		default:
			break;
		}

		break;

	}
	return;
}

bool ListView::InsertListViewItems()
{
	uint32_t cItems = m_databaza->querySize();
	LVITEM lvI = {};

	lvI.pszText = LPSTR_TEXTCALLBACK; 
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;

	for (uint32_t index = 0; index < cItems; ++index)
	{
		lvI.iItem = index;
		lvI.iImage = index;

		if (ListView_InsertItem(m_window, &lvI) == -1)
			return false;
	}

	return true;
}

bool ListView::InitListViewColumns()
{
	wchar_t szText[256];     
	LVCOLUMN lvc = {};
	lvc.pszText = szText;

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	for (uint32_t iCol = 0; iCol < C_COLUMNS; iCol++)
	{
		lvc.iSubItem = iCol;
		
		lvc.cx = 100;               // Width of column in pixels.

		if (iCol < 2)
			lvc.fmt = LVCFMT_LEFT;  // Left-aligned column.
		else
			lvc.fmt = LVCFMT_RIGHT; // Right-aligned column.

									// Load the names of the column headings from the string resources.
		LoadString(GetModuleHandle(NULL),
			IDS_COLUMN1 + iCol,
			szText,
			sizeof(szText) / sizeof(szText[0]));

		// Insert the columns into the list view.
		if (ListView_InsertColumn(m_window, iCol, &lvc) == -1)
			return false;
	}

	return true;
}

bool ListView::CreateListView()
{
	INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	icex.dwSize = sizeof(icex);
	if (InitCommonControlsEx(&icex) == FALSE) MessageBox(NULL, L"Initiation of common controls failed", L"Fail", MB_OK);

	RECT rcClient;                       // The parent window's client area.

	GetClientRect(m_parent, &rcClient);

	// Create the list-view window in report view with label editing enabled.
	m_window = CreateWindow(WC_LISTVIEW,
		L"",
		WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
		0, 0,
		rcClient.right - rcClient.left,
		rcClient.bottom - rcClient.top,
		m_parent,
		(HMENU)IDM_DATABAZA_LIST,
		GetModuleHandle(NULL),
		NULL);
	if (m_window == NULL)
	{
		return false;
	}
	return true;
}

ListView::ListView(HWND parent, std::shared_ptr<Databaza> db)
	:m_parent(parent), m_databaza(db)
{
	if (!CreateListView())
	{
		throw std::runtime_error("Could not create list view");
	}
	if (!InitListViewColumns())
	{
		throw std::runtime_error("Could not insert list view columns");
	}
}
