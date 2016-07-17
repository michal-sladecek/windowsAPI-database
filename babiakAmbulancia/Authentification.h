#pragma once
#include "resource.h"
#include "Dialog.h"

namespace AuthentificationSystem
{
	class AuthentificateDialog : public Dialog
	{
		INT_PTR ProcessMessage(UINT message, WPARAM wParam);
	public:
		AuthentificateDialog(HWND parent) :Dialog(parent)
		{
			m_template = IDD_LOGIN;
		}
	};
	bool IsAuthentificated();
}