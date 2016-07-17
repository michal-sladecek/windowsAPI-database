#pragma once

#include <string>
#include "ListView.h"
#include "Databaza.h"

/*
App contains window, and database.
*/
class App
{
	const std::wstring appName = L"PRENATAL Databáza";
	const std::wstring className = L"PRENATAL";

	std::shared_ptr<Database> m_database;
	ListView m_listView;

	HINSTANCE m_instance;
	HWND m_window;
	
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);
	_Check_return_  bool StartWindow();
	_Check_return_ bool RegisterApp();
public:
	App();
	_Check_return_ bool Run();
};
