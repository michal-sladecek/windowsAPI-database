#pragma once
#include "Databaza.h"
#include "stdafx.h"


INT_PTR CALLBACK NovyPaciendDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void NovyPacientDialog(Databaza * p, HWND parent);
