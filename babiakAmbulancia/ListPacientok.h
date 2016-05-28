#pragma once
#include "stdafx.h"
#include "resource.h"
#include "Pacientka.h"
#include "Databaza.h"

#include <string>
#include <vector>

const UINT IDM_DATABAZA_LIST = 103;
const UINT C_COLUMNS = 7;


HWND CreateListView(HWND hwndParent);
BOOL InsertListViewItems(HWND hWndListView);
BOOL InitListViewColumns(HWND hWndListView);
void resize(HWND parent,HWND listView);
void showDatabaza(HWND hWnd, HWND & listView, std::vector<Pacientka>);
void HandleWM_NOTIFY(LPARAM lParam);