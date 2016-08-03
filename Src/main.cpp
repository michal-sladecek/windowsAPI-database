// main.cpp : Defines the entry point for the application.
//

#pragma comment(linker,"\"/manifestdependency:type='win32' \ name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \ processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "stdafx.h"
#include "App.h"

#include <cassert>
#include "../Shared/bytes/ZipBytes.h"
void Testy()
{
	std::vector<std::string> V;
	V.push_back("Ahoj");
	V.push_back("A");
	V.push_back("AAAAAAAAAA");
	std::string t = ZipByteVectors(V);
	std::vector<std::string> P = UnzipToByteVectors(t);
	assert(V[0] == P[0] && V[1] == P[1] && V[2] == P[2]);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{


	//Testy();
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	App application;
	application.Run();
	return 0;
}

