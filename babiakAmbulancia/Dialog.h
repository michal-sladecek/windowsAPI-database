#pragma once
#include <windows.h>

class Dialog
{
protected:
	HWND m_parent;
	HWND m_window;
	uint32_t m_template;

	static INT_PTR CALLBACK DialogProcCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	virtual INT_PTR ProcessMessage(UINT message, WPARAM wParam) = 0;
public:
	Dialog(HWND parent) : m_parent(parent), m_window(nullptr) {}
	void Show();
};