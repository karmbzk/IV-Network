/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "CPatches.h"
#include <Patcher\CPatcher.h>
#include <fstream>
#include <Ptrs.h>
#include <CXML.h>

bool __cdecl isConnectedToSocialClub(int a1)
{
	return true;
}

void CPatches::Initialize()
{
#ifdef TASKINFO_TEST
	*(BYTE*)(g_pCore->GetBase() + 0x7CA700) = 0xC3; //disable error reporting

	//bypass rockstar social club
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x7E0150, (DWORD)isConnectedToSocialClub);
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x477324, g_pCore->GetBase() + 0x47747F);
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x48436A, g_pCore->GetBase() + 0x48437F);

	//do not ping http://www.rockstargames.com on starup
	CPatcher::InstallNopPatch(g_pCore->GetBase() + 0x475EC5, 5);
	CPatcher::InstallNopPatch(g_pCore->GetBase() + 0x475EDC, 8);

	CPatcher::InstallNopPatch(g_pCore->GetBase() + 0x492D9B, 5); //do not load scrollbars.dat

	char* text = "Kekse!!!!"; //scrollbars text

	for (int i = 0; i < 8; ++i) //set scrollbars text
	{
		memcpy((char*)((g_pCore->GetBase() + 0x11B4508) + (1300 * i)), text, strlen(text)); //max len: 1300
		((char*)((g_pCore->GetBase() + 0x11B4508) + (1300 * i)))[strlen(text)] = '\0';
	}


	*(DWORD*)(g_pCore->GetBase() + 0x8DC8FD) = 0xFF38F5D8;

	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x473432, g_pCore->GetBase() + 0x4734F7); //automatice start game
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x6DECB1, g_pCore->GetBase() + 0x6DED5F);

	*(BYTE*)(g_pCore->GetBase() + 0x853073) = 0xE0;

	*(WORD *)(g_pCore->GetBase() + 0x472EF1) = 0xC033; //xor eax, eax
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x472EF3, g_pCore->GetBase() + 0x47316E);

	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x473207, g_pCore->GetBase() + 0x473213);

	*(BYTE*)(g_pCore->GetBase() + 0xA1FE40) == 0xCC;

	return;
#else

	/*
		87017F
		mov esi, offset g_pPlayerInfos
		replace with our own array
	
	*/

	// Skip main menu #1
	*(BYTE *) COffsets::IV_Hook__PatchUnkownByte1 = 0xE0;

	// Skip main menu #2
	//CPatcher::InstallJmpPatch(COffsets::CGame_Process__Sleep, COffsets::CGame_Process_InitializeRageGame);

	// Make the game think we are not connected to the internet - Balika011: faster game load
	*(BYTE *) COffsets::IV_Hook__PatchInternet_1 = 0; // byteInternetConnectionState
	*(DWORD *) COffsets::IV_Hook__PatchInternet_2 = 0x90C3C032; // xor al, al; retn; nop

	// Always start a new game
	//CPatcher::InstallJmpPatch(COffsets::RAGE_LoadGame, COffsets::RAGE_StartNewGame);


	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x473432, g_pCore->GetBase() + 0x4734F7); //automatice start game
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x6DECB1, g_pCore->GetBase() + 0x6DED5F);
	//pPatcher->EditByte(0x853073, 0xE0);

	// === RAGE %% RGSC Stuff

	// Don't initialize error reporting
	CPatcher::InstallRetnPatch(COffsets::IV_Hook__PatchErrorReporting);

	*(WORD *) (g_pCore->GetBase() + 0x472EF1) = 0xC033; //xor eax, eax
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x472EF3, g_pCore->GetBase() + 0x47316E);

	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x473207, g_pCore->GetBase() + 0x473213);

	// Skip missing tests
	CPatcher::InstallNopPatch(COffsets::IV_Hook__PatchMissingTests1, 14);
	CPatcher::InstallNopPatch(COffsets::IV_Hook__PatchMissingTests2, 14);
	CPatcher::InstallNopPatch(g_pCore->GetBase() + 0x493D4C, 24);

	*(DWORD *) COffsets::IV_Hook__PatchUnkownAddress1 = 0x90CC033; // xor eax, eax; retn
	*(DWORD *) COffsets::IV_Hook__PatchUnkownAddress2 = 0x90CC033; // xor eax, eax; retn

	// Disable securom spot checks (mov al, 1; retn)
	*(DWORD *) COffsets::IV_Hook__PatchSecuromCheck = 0x90C301B0;
	*(DWORD *) (COffsets::IV_Hook__PatchSecuromCheck + 0x20) = 0x90C301B0;
	*(DWORD *) (COffsets::IV_Hook__PatchSecuromCheck + 0x30) = 0x90C301B0;
	*(DWORD *) (COffsets::IV_Hook__PatchSecuromCheck + 0x60) = 0x90C301B0;

	*(BYTE *) (g_pCore->GetBase() + 0x15C3398) = 1; //fix random drunk cam

	// Disables Warning Messages(like "Unkown resource found") -> Disables only the window(and exit code part)...
	// TODO: Replace with own error code function

#ifdef _DEV // Disable this function in our debug mode
	CPatcher::InstallJmpPatch(COffsets::IV_Hook__PatchErrorMessageBoxes, (COffsets::IV_Hook__PatchErrorMessageBoxes + 0x6B1));
#endif

	*(BYTE *) COffsets::IV_Hook__PatchUnkownByte1 = 0xE0;

	// Allow remote desktop connections pff
	//CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x405D67, g_pCore->GetBase() + 0x405D6E, 1);

	// Set the window text
	*(DWORD *) (g_pCore->GetBase() + 0x47316F) = (DWORD) MOD_NAME;

	// Disable automatic vehicle engine turn-on
	*(DWORD*) (COffsets::IV_Hook__PatchVehicleDriverProcess) = 0x04C2C031; //xor eax, eax; retn 4
	*(BYTE*) (COffsets::IV_Hook__PatchVehicleDriverProcess + 4) = 0; //xor eax, eax; retn 4
#endif
}