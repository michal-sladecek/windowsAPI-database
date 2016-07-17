#include "stdafx.h"

#include "App.h"
#include "Authentification.h"
#include "Backup.h"
#include "ListView.h"
#include <iostream>
#include "LoginDialog.h"
#include "Pacientka.h"
#include "Vyhladavanie.h"
#include "Databaza.h"

LRESULT CALLBACK App::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	App * self;
	self = reinterpret_cast<App *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	if (self != nullptr)
	{
		return self->ProcessMessage(message, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

LRESULT App::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{	
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_DATABAZA:
			m_database->queryAll();
			m_listView.Show();
			break;
		case ID_ODHLASENIE:
			DestroyWindow(m_window);
			break;
		case ID_VYHLADAVANIE:
		{
			BOOL ok = FALSE;
			vyhladavaciDialog(m_database.get(), ok, m_window);
			if (ok == TRUE)
			{
				m_listView.Show();
			}
				
		}
		break;
		case ID_ZALOHA:
		{
			BackupSystem::BackupDialog dialog(m_window, m_database);
			dialog.Show();
			m_database->queryAll();
			m_listView.Show();
			break;
		}
		case ID_NOVYPACIENT:
		{
			AddPatientDialog dialog(m_window, m_database);
			dialog.Show();
			m_database->queryAll();
			m_listView.Show();
			break;
		}
		default:
			return DefWindowProc(m_window, message, wParam, lParam);
		}
	}
	break;
	case WM_NOTIFY:
		switch (LOWORD(wParam)) {
		case IDM_DATABAZA_LIST:
			m_listView.HandleWM_NOTIFY(lParam);
			break;
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_window, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(m_window, &ps);
	}
	break;
	case WM_SIZE:
		m_listView.Resize();
		break;
	case WM_SIZING:
		m_listView.Resize();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(m_window, message, wParam, lParam);
	}
	return 0;
}

_Check_return_ bool App::RegisterApp()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = App::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_instance;
	wcex.hIcon = LoadIcon(m_instance, MAKEINTRESOURCE(IDI_BABIAKAMBULANCIA));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_BABIAKAMBULANCIA);
	wcex.lpszClassName = className.c_str();
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	if (0 == RegisterClassExW(&wcex))
	{
		return false;
	}
	return true;
}

_Check_return_ bool App::StartWindow()
{
	m_window = CreateWindowW(className.c_str(), appName.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_instance, nullptr);

	if (!m_window)
	{
		return false;
	}
	ShowWindow(m_window, SW_SHOW);
	if (FALSE == UpdateWindow(m_window))
	{
		return false;
	}
	return true;

}

App::App()
{
	m_database = std::make_shared<Databaza>();
	
	m_instance = GetModuleHandle(NULL);
	if (!RegisterApp())
	{
		throw std::runtime_error("Could not register app error.");
	}
	if (!StartWindow())
	{
		throw std::runtime_error("Could not run window.");
	}
	AuthentificationSystem::AuthentificateDialog dialog(m_window);
	dialog.Show();
	if (!AuthentificationSystem::IsAuthentificated()) 
	{
		throw std::runtime_error("Authentification error");
	}
	m_listView = ListView(m_window, m_database);
	SetWindowLongPtr(m_window, GWLP_USERDATA,
		reinterpret_cast<LPARAM>(this));
}

bool App::Run()
{
	HACCEL hAccelTable = LoadAccelerators(m_instance, MAKEINTRESOURCE(IDC_BABIAKAMBULANCIA));

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
	std::cout << m_database.use_count() << "\n";
	return msg.wParam;
}
