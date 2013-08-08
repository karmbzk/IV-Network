//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: Input.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include <algorithm>
#include <CCore.h>
#include <list>
#include "Input.h"
#include <CString.h>

WNDPROC           m_wWndProc = NULL;
extern CCore * g_pCore;
extern bool g_bDisplayData;
std::list< CString >		pressedKeys;

CString GetKeyNameByCode(DWORD dwCode)
{
	CString strCode;

	if(dwCode >= 0x30 && dwCode <= 0x39)
	{
		strCode = (unsigned char)dwCode;
	}
	else if(dwCode >= 0x41 && dwCode <= 0x5A)
	{
		strCode = (unsigned char)(dwCode + 0x20);
	}
	else if(dwCode >= VK_NUMPAD0 && dwCode <= VK_NUMPAD9)
	{
		strCode.Format("num_%d", dwCode - VK_NUMPAD0);
	}
	else if(dwCode >= VK_F1 && dwCode <= VK_F12)
	{
		strCode.Format("f%d", dwCode - VK_F1 + 1);
	}
	else
	{
		switch(dwCode)
		{
		case VK_TAB:
			strCode = "tab"; break;
		case VK_RETURN:
			strCode = "enter"; break;
		case VK_CONTROL:
			strCode = "ctrl"; break;
		case VK_SHIFT:
			strCode = "shift"; break;
		case VK_MENU:
			strCode = "alt"; break;
		case VK_ADD:
			strCode = "num_add"; break;
		case VK_SUBTRACT:
			strCode = "num_sub"; break;
		case VK_DIVIDE:
			strCode = "num_div"; break;
		case VK_MULTIPLY:
			strCode = "num_mul"; break;
		case VK_SPACE:
			strCode = "space"; break;
		case VK_LEFT:
			strCode = "arrow_left"; break;
		case VK_RIGHT:
			strCode = "arrow_right"; break;
		case VK_UP:
			strCode = "arrow_up"; break;
		case VK_DOWN:
			strCode = "arrow_down"; break;
		case VK_PRIOR:
			strCode = "page_up"; break;
		case VK_NEXT:
			strCode = "page_down"; break;
		case VK_END:
			strCode = "end"; break;
		case VK_HOME:
			strCode = "home"; break;
		case VK_INSERT:
			strCode = "insert"; break;
		case VK_DELETE:
			strCode = "delete"; break;
		case 0x1E:
			strCode = "backspace"; break;
		case 0x01:
			strCode = "esc"; break;
		case VK_CAPITAL:
			strCode = "caps"; break;
		case VK_BACK:
			strCode = "back"; break;
		case 0xC4:
			strCode = "�"; break;
		case 0xE4:
			strCode = "�"; break;
		case 0xD4:
			strCode = "�"; break;
		case 0xF4:
			strCode = "�"; break;
		case 0xDC:
			strCode = "�"; break;
		case 0xFC:
			strCode = "�"; break;
		default:
			break;
		}
	}

	return strCode;
}

void StartGame()
{
	DWORD unk_10F8088 = g_pCore->GetBase() + 0x10F8088;
	DWORD sub_5AF930 = g_pCore->GetBase() + 0x5AF930;
	DWORD dword_10F8078 = g_pCore->GetBase() + 0x10F8078;
	DWORD dword_10F805C = g_pCore->GetBase() + 0x10F805C;
	int * v7 = new int(0);
	_asm
	{
		push v7
		mov ecx, unk_10F8088
		call sub_5AF930
	}
	*(DWORD*)dword_10F8078 = *v7;
	*(DWORD*)dword_10F805C = *v7;
	if ( *v7 > 0 )
	{
		DWORD sub_7B2DF0 = g_pCore->GetBase() + 0x7B2DF0;
		_asm
		{
		call sub_7B2DF0
		}
	}

	DWORD sub_7870A0 = g_pCore->GetBase() + 0x7870A0;
	_asm
	{
		push 6
		call sub_7870A0
		add     esp, 4
	}
}
bool bToggle = true;
LRESULT APIENTRY WndProc_Hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    bool bFocused = (GetForegroundWindow() == hWnd);

    // Are we focused?
    if(bFocused)
    {
		if(uMsg == WM_KILLFOCUS || (uMsg == WM_ACTIVATE && LOWORD(wParam) == WA_INACTIVE))
		{
			return true;
		}

		if(uMsg == WM_KEYUP && wParam == VK_F12)
		{
			//
		}
		if(g_pCore->GetChat())
			 g_pCore->GetChat()->HandleUserInput(uMsg, (DWORD)wParam);

		// Is the chat input not visible?
		if(g_pCore->GetChat() && !g_pCore->GetChat()->IsInputVisible())
		{
			// Get the key code string
			CString strCode = GetKeyNameByCode((DWORD)wParam);

			// Was something presses?
			if(!strCode.IsEmpty())
			{
				CString strState;

				// Get the key state
				if(uMsg == WM_KEYUP)
                {
                    // Check if key was pressed beforehand
                    if(std::find(pressedKeys.begin(), pressedKeys.end(), strCode) != pressedKeys.end())
                    {
						pressedKeys.remove(strCode);
						strState = "up";
                    }
				}
				else if(uMsg == WM_KEYDOWN)
				{
                    // Check if key was pressed beforehand
                    if(std::find(pressedKeys.begin(), pressedKeys.end(), strCode) == pressedKeys.end())
                    {
                        pressedKeys.push_back(strCode);
                        strState = "down";
                    }
                }

				// Is the state valid?
				if(!strState.IsEmpty())
				{
					/*// Call the script event
					CSquirrelArguments pArguments;
					pArguments.push(strCode);
					pArguments.push(strState);
					pGame->GetClientScriptingManager()->GetEvents()->Call("onClientKeyPress", &pArguments);
					*/
				}
			}
		}
    }

    return CallWindowProc(m_wWndProc, hWnd, uMsg, wParam, lParam);
}