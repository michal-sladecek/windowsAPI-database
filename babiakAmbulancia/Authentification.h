#pragma once
#include "stdafx.h"

/* Authentificate yourself with password, returns TRUE if ok, FALSE otherwise */
BOOL Authentificate(const wchar_t * password);

/* Use our dialog box authentification, this prompts the user for password in a dialog box */
BOOL AuthentificateDialog(HINSTANCE, HWND parent);

/* Checks whether the user is authentificated */
BOOL is_authentificated();