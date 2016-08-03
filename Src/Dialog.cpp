#include "stdafx.h"
#include "Dialog.h"


INT_PTR Dialog::DialogProcCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	Dialog * self = nullptr;
	if (message == WM_INITDIALOG)
	{
		self = reinterpret_cast<Dialog *>(lParam);
		SetWindowLongPtr(hDlg, DWLP_USER, reinterpret_cast<LONG>(self));
	}
	self = reinterpret_cast<Dialog *>(GetWindowLongPtr(hDlg, DWLP_USER));

	if (self != nullptr)
	{
		if (self->m_window == nullptr)
		{
			self->m_window = hDlg;
		}
		return (INT_PTR)self->ProcessMessage(message, wParam);
	}
	else
	{
		return (INT_PTR)FALSE;
	}
	
}

void Dialog::Show()
{
	DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(m_template), m_parent, Dialog::DialogProcCallback, reinterpret_cast<LPARAM>(this));
}
