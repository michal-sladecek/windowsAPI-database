#pragma once
#include "stdafx.h"
#include "resource.h"
#include "Databaza.h"

#include <string>
#include <vector>

const UINT IDM_DATABAZA_LIST = 103;
const UINT C_COLUMNS = 7;


class ListView
{
	HWND m_window;
	HWND m_parent;
	std::shared_ptr<Database> m_databaza;

	bool InitListViewColumns();
	bool CreateListView();
	bool InsertListViewItems();
	
public:
	ListView() :m_window(NULL), m_parent(NULL) {}
	ListView::ListView(HWND parent, std::shared_ptr<Database> db);

	void HandleWM_NOTIFY(LPARAM lParam);
	void Show();
	void Resize();
};