//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CEFLCSupport.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CEFLCSupport.h"
#include <CCore.h>
extern CCore * g_pCore;

struct sImportItem
{
	CString		strArea;
	CString		strImportName;
	bool		bLoaded;
	int			iType;
};

sImportItem ImportItems[] = {
	{"east","bronx_e.ide"},
	{"east","bronx_e.img"},
	{"east","bronx_e.wpl"},

	{"east","bronx_e2.ide"},
	{"east","bronx_e2.img"},
	{"east","bronx_e2.wpl"},

	{"east","bronx_w.ide"},
	{"east","bronx_w.img"},
	{"east","bronx_w.wpl"},

	{"east","bronx_w2.ide"},
	{"east","bronx_w2.img"},
	{"east","bronx_w2.wpl"},

	{"east","brook_n.ide"},
	{"east","brook_n.img"},
	{"east","brook_n.wpl"},

	{"east","brook_n2.ide"},
	{"east","brook_n2.img"},
	{"east","brook_n2.wpl"},

	{"east","brook_s.ide"},
	{"east","brook_s.img"},
	{"east","brook_s.wpl"},

	{"east","brook_s2.ide"},
	{"east","brook_s2.img"},
	{"east","brook_s2.wpl"},

	{"east","brook_s3.ide"},
	{"east","brook_s3.img"},
	{"east","brook_s3.wpl"},

	{"east","east_xr.ide"},
	{"east","east_xr.img"},

	{"east","queens_e.ide"},
	{"east","queens_e.img"},
	{"east","queens_e.wpl"},

	{"east","queens_m.ide"},
	{"east","queens_m.img"},
	{"east","queens_m.wpl"},

	{"east","queens_w.ide"},
	{"east","queens_w.img"},
	{"east","queens_w.wpl"},

	{"east","queens_w2.ide"},
	{"east","queens_w2.img"},
	{"east","queens_w2.wpl"},

	// Generic

	{"interiors/generic","bars_1.ide"},
	{"interiors/generic","bars_1.img"},

	{"interiors/generic","bars_2.ide"},
	{"interiors/generic","bars_2.img"},

	{"interiors/generic","bars_3.ide"},
	{"interiors/generic","bars_3.img"},

	{"interiors/generic","blocks.ide"},
	{"interiors/generic","blocks.img"},

	{"interiors/generic","blocks_2.ide"},
	{"interiors/generic","blocks_2.img"},

	{"interiors/generic","blocks_3.ide"},
	{"interiors/generic","blocks_3.img"},

	{"interiors/generic","brownstones.ide"},
	{"interiors/generic","brownstones.img"},

	{"interiors/generic","homes_1.ide"},
	{"interiors/generic","homes_1.img"},

	{"interiors/generic","homes_2.ide"},
	{"interiors/generic","homes_2.img"},

	{"interiors/generic","homes_3.ide"},
	{"interiors/generic","homes_3.img"},

	{"interiors/generic","indust_1.ide"},
	{"interiors/generic","indust_1.img"},

	{"interiors/generic","indust_1.ide"},
	{"interiors/generic","indust_1.img"},

	{"interiors/generic","public_1.ide"},
	{"interiors/generic","public_1.img"},

	{"interiors/generic","public_2.ide"},
	{"interiors/generic","public_2.img"},

	{"interiors/generic","public_3.ide"},
	{"interiors/generic","public_3.img"},

	{"interiors/generic","retail_1.ide"},
	{"interiors/generic","retail_1.img"},

	{"interiors/generic","retail_2.ide"},
	{"interiors/generic","retail_2.img"},

	{"interiors/generic","retail_3.ide"},
	{"interiors/generic","retail_3.img"},

	{"interiors/generic","retail_4.ide"},
	{"interiors/generic","retail_4.img"},

	{"interiors/int_props","props_ab.ide"},
	{"interiors/int_props","props_ab.img"},

	{"interiors/int_props","props_ah.ide"},
	{"interiors/int_props","props_ah.img"},

	{"interiors/int_props","props_km.ide"},
	{"interiors/int_props","props_km.img"},

	{"interiors/int_props","props_ld.ide"},
	{"interiors/int_props","props_ld.img"},

	{"interiors/int_props","props_mp.ide"},
	{"interiors/int_props","props_mp.img"},

	{"interiors/int_props","props_ss.ide"},
	{"interiors/int_props","props_ss.img"},

	{"interiors/mission","level_1.ide"},
	{"interiors/mission","level_1.img"},

	{"interiors/mission","level_2.ide"},
	{"interiors/mission","level_2.img"},

	{"interiors/mission","level_3.ide"},
	{"interiors/mission","level_3.img"},

	{"interiors/mission","level_4.ide"},
	{"interiors/mission","level_4.img"},

	{"interiors/mission","level_5.ide"},
	{"interiors/mission","level_5.img"},

	{"interiors/mission","level_6.ide"},
	{"interiors/mission","level_6.img"},

	//
	{"interiors/test","interiors.ide"},
	{"interiors/test","interiors.img"},
	{"interiors/test","interiors.wpl"},

	//
	{"manhat", "manhat01.ide" },
	{"manhat", "manhat01.img" },
	{"manhat", "manhat01.wpl" },
	{"manhat", "manhat01.xpl" },

	{"manhat", "manhat02.ide" },
	{"manhat", "manhat02.img" },
	{"manhat", "manhat02.wpl" },
	{"manhat", "manhat02.xpl" },

	{"manhat", "manhat03.ide" },
	{"manhat", "manhat03.img" },
	{"manhat", "manhat03.wpl" },
	{"manhat", "manhat03.xpl" },

	{"manhat", "manhat04.ide" },
	{"manhat", "manhat04.img" },
	{"manhat", "manhat04.wpl" },
	{"manhat", "manhat04.xpl" },

	{"manhat", "manhat05.ide" },
	{"manhat", "manhat05.img" },
	{"manhat", "manhat05.wpl" },
	{"manhat", "manhat05.xpl" },

	{"manhat", "manhat06.ide" },
	{"manhat", "manhat06.img" },
	{"manhat", "manhat06.wpl" },
	{"manhat", "manhat06.xpl" },

	{"manhat", "manhat07.ide" },
	{"manhat", "manhat07.img" },
	{"manhat", "manhat07.wpl" },
	{"manhat", "manhat07.xpl" },

	{"manhat", "manhat08.ide" },
	{"manhat", "manhat08.img" },
	{"manhat", "manhat08.wpl" },
	{"manhat", "manhat08.xpl" },

	{"manhat", "manhat09.ide" },
	{"manhat", "manhat09.img" },
	{"manhat", "manhat09.wpl" },
	{"manhat", "manhat09.xpl" },

	{"manhat", "manhat10.ide" },
	{"manhat", "manhat10.img" },
	{"manhat", "manhat10.wpl" },
	{"manhat", "manhat10.xpl" },

	{"manhat", "manhat11.ide" },
	{"manhat", "manhat11.img" },
	{"manhat", "manhat11.wpl" },
	{"manhat", "manhat11.xpl" },

	{"manhat", "manhat12.ide" },
	{"manhat", "manhat12.img" },
	{"manhat", "manhat12.wpl" },
	{"manhat", "manhat12.xpl" },

	{"manhat", "manhatsw.ide" },
	{"manhat", "manhatsw.img" },
	{"manhat", "manhatsw.wpl" },
	{"manhat", "manhatsw.xpl" },

	{"manhat", "manhatxr.ide" },
	{"manhat", "manhatxr.img" },

	{"manhat", "subwayxr.ide" },
	{"manhat", "subwayxr.img" },

	//
	{"jersey", "nj_01.ide" },
	{"jersey", "nj_01.img" },
	{"jersey", "nj_01.wpl" },
	{"jersey", "nj_01.xpl" },

	{"jersey", "nj_02.ide" },
	{"jersey", "nj_02.img" },
	{"jersey", "nj_02.wpl" },
	{"jersey", "nj_02.xpl" },

	{"jersey", "nj_03.ide" },
	{"jersey", "nj_03.img" },
	{"jersey", "nj_03.wpl" },
	{"jersey", "nj_03.xpl" },

	{"jersey", "nj_04e.ide" },
	{"jersey", "nj_04e.img" },
	{"jersey", "nj_04e.wpl" },
	{"jersey", "nj_04e.xpl" },

	{"jersey", "nj_04w.ide" },
	{"jersey", "nj_04w.img" },
	{"jersey", "nj_04w.wpl" },
	{"jersey", "nj_04w.xpl" },

	{"jersey", "nj_05.ide" },
	{"jersey", "nj_05.img" },
	{"jersey", "nj_05.wpl" },
	{"jersey", "nj_05.xpl" },

	{"jersey", "nj_docks.ide" },
	{"jersey", "nj_docks.img" },
	{"jersey", "nj_docks.wpl" },
	{"jersey", "nj_docks.xpl" },

	{"jersey", "nj_liberty.ide" },
	{"jersey", "nj_liberty.img" },
	{"jersey", "nj_liberty.wpl" },
	{"jersey", "nj_liberty.xpl" },

	{"jersey", "nj_xref.ide" },
	{"jersey", "nj_xref.img" },

	//
	{"props/commercial","7_11.ide"},
	{"props/commercial","7_11.img"},

	{"props/commercial","bar.ide"},
	{"props/commercial","bar.img"},

	{"props/commercial","beauty.ide"},
	{"props/commercial","beauty.img"},

	{"props/commercial","clothes.ide"},
	{"props/commercial","clothes.img"},

	{"props/commercial","club.ide"},

	{"props/commercial","fastfood.ide"},
	{"props/commercial","fastfood.img"},

	{"props/commercial","garage.ide"},

	{"props/commercial","office.ide"},
	{"props/commercial","office.img"},

	{"props/commercial","poster.ide"},

	//
	{"props/doors","ext_door.ide"},
	{"props/doors","ext_door.img"},

	{"props/doors","int_door.ide"},
	{"props/doors","int_door.img"},

	//
	{"props/industrial","build.ide"},
	{"props/industrial","build.img"},

	{"props/industrial","drums.ide"},
	{"props/industrial","drums.img"},

	{"props/industrial","farm.ide"},

	{"props/industrial","industrial.ide"},
	{"props/industrial","industrial.img"},

	{"props/industrial","pipes.ide"},

	{"props/industrial","railway.ide"},
	{"props/industrial","railway.img"},

	{"props/industrial","skips.ide"},
	{"props/industrial","skips.img"},

	{"props/industrial","storage.ide"},

	{"props/industrial","switches.ide"},

	//
	{"props/lev_des","icons.ide"},
	{"props/lev_des","icons.img"},

	{"props/lev_des","minigame.ide"},
	{"props/lev_des","minigame.img"},

	{"props/lev_des","mission_int.ide"},
	{"props/lev_des","mission_int.img"},

	//
	{"props/prop_test","cj_test.ide"},
	{"props/prop_test","cj_test.img"},
	{"props/prop_test","cj_test.ide"},

	//
	{"props/residential","bathroom.ide"},
	{"props/residential","bathroom.img"},

	{"props/residential","bedroom.ide"},
	{"props/residential","bedroom.img"},

	{"props/residential","chairs.ide"},

	{"props/residential","details.ide"},
	{"props/residential","details.img"},

	{"props/residential","dinning.ide"},
	{"props/residential","dinning.img"},

	{"props/residential","electrical.ide"},
	{"props/residential","electrical.img"},

	{"props/residential","kitchen.ide"},
	{"props/residential","kitchen.img"},

	{"props/residential","lights.ide"},
	{"props/residential","lights.img"},

	{"props/residential","soft.ide"},
	{"props/residential","soft.img"},

	{"props/residential","walls.ide"},

	//
	{"props/windows", "gen_win.ide" },
	{"props/windows", "gen_win.img" },
	{"props/windows", "unique.ide" },



	{"props/vegetation", "ext_veg.ide" },
	{"props/vegetation", "ext_veg.img" },

	{"props/vegetation", "int_veg.ide" },
	{"props/vegetation", "int_veg.img" },



	{"props/street", "amenitie.ide" },
	{"props/street", "amenitie.img" },

	{"props/street", "elecbox.ide" },
	{"props/street", "elecbox.img" },

	{"props/street", "misc.ide" },
	{"props/street", "misc.img" },

	{"props/street", "rooftop.ide" },
	{"props/street", "rooftop.img" },



	{"props/roadside", "bins.ide" },
	{"props/roadside", "bins.img" },

	{"props/roadside", "bllbrd.ide" },
	{"props/roadside", "bllbrd.img" },

	{"props/roadside", "crates.ide" },
	{"props/roadside", "crates.img" },

	{"props/roadside", "fences.ide" },
	{"props/roadside", "fences.img" },

	{"props/roadside", "lamppost.ide" },
	{"props/roadside", "lamppost.img" },

	{"props/roadside", "rubbish.ide" },
	{"props/roadside", "rubbish.img" },

	{"props/roadside", "sign.ide" },
	{"props/roadside", "sign.img" },

	{"props/roadside", "st_vend.ide" },
	{"props/roadside", "st_vend.img" },

	{"props/roadside", "traffic.ide" },
	{"props/roadside", "traffic.img" },

	{"props/roadside", "works.ide" },
	{"props/roadside", "works.img" },


	//
	{"util","animviewer.ide"},
	{"util","animviewer.img"},
	{"util","animviewer.wpl"},

	//
	{"generic", "lodcull_e.img" },
	{"generic", "lodcull_e.wpl" },
	{"generic", "lodcull_e.xpl" },

	{"generic", "lodcull_j.img" },
	{"generic", "lodcull_j.wpl" },
	{"generic", "lodcull_j.xpl" },

	{"generic", "lodcull_m.img" },
	{"generic", "lodcull_m.wpl" },
	{"generic", "lodcull_m.xpl" },

	{"generic", "procobj.ide" },
	{"generic", "procobj.img" },

	{"handling_tbogt.dat", "ivmp_replace_pad_tbogt_0", false, (eEFLCStruct)TBOGT_PAD_DAT_HANDLING}, // TheBalladOfGayTony - handling.dat
	{"data", "ivmp_replace_pad_tbogt_1", false, (eEFLCStruct)TBOGT_PAD_IDE_VEHICLE}, // TheBalladOfGayTony - vehicles.ide
	{"data", "ivmp_replace_pad_tbogt_2", false, (eEFLCStruct)TBOGT_PAD_TXT_IMAGES}, // TheBalladOfGayTony - images.txt PAD
	{"data", "ivmp_replace_pad_tbogt_3", false, (eEFLCStruct)TBOGT_PAD_TXT_CJIMAGES}, // TheBalladOfGayTony - cj_images.txt PAD
	{"data", "ivmp_replace_pad_tbogt_4", false, (eEFLCStruct)TBOGT_PAD_DAT_CARCOLS}, // TheBalladOfGayTony - carcols.dat PAD
	{"data", "ivmp_replace_pad_tbogt_5", false, (eEFLCStruct)TBOGT_PAD_DAT_CARGRP}, // TheBalladOfGayTony - cargrp.dat PAD
	{"data", "ivmp_replace_pad_tbogt_6", false, (eEFLCStruct)TBOGT_PAD_DAT_VEHICLEEXTRAS}, // TheBalladOfGayTony - VehicleExtras.dat PAD
	{"data", "ivmp_replace_pad_tbogt_7", false, (eEFLCStruct)TBOGT_PAD_CSV_VEHOFF}, // TheBalladOfGayTony - vehOff.csv PAD

	{"images.txt", "images.txt", false, (eEFLCStruct)DEFAULT_FILE_HOOK},
	{"default.dat", "default.dat", false, (eEFLCStruct)DEFAULT_FILE_HOOK},
	{"gta.dat", "gta.dat", false, (eEFLCStruct)DEFAULT_FILE_HOOK},
};

DWORD sub_5B4F60;
DWORD dwJmp2;
char *file = new char[255];
char *file_ptr;

#include <algorithm> 
#include <string> 
bool Should(char* j)
{
	for(size_t i = 0; i < (sizeof(ImportItems) / sizeof(sImportItem)); i++)
	{
		// Loop through all characters
		CString strText = ImportItems[i].strImportName;
		std::string strFind = j;
		std::transform(strFind.begin(),  strFind.end(),  strFind.begin(), ::tolower);

		std::size_t found = strFind.find(strText.Get());
		if (found!=std::string::npos)
		{
			CString strPathToFile;

			switch(ImportItems[i].iType)
			{
				case TBOGT_PAD_DAT_HANDLING:
				{
					strPathToFile = CString("%s/TBoGT/common/data/handling.dat",g_pCore->GetGame()->GetEFLCDirectory().Get());
					break;
				}
				case TBOGT_PAD_IDE_VEHICLE:
				{
					strPathToFile = CString("%s/TBoGT/common/data/vehicles.ide",g_pCore->GetGame()->GetEFLCDirectory().Get());
					break;
				}

				case TBOGT_PAD_TXT_IMAGES:
				{
					strPathToFile = CString("%s/TBoGT/pc/models/cdimages/vehicles.img",g_pCore->GetGame()->GetEFLCDirectory().Get());
					break;
				}
				
				case TBOGT_PAD_TXT_CJIMAGES:
				{
					strPathToFile = CString("%s/TBoGT/pc/models/cdimages/vehicles.img",g_pCore->GetGame()->GetEFLCDirectory().Get());
					break;
				}

				case TBOGT_PAD_DAT_CARCOLS:
				{
					strPathToFile = CString("%s/TBoGT/common/data/carcols.dat",g_pCore->GetGame()->GetEFLCDirectory().Get());
					break;
				}

				case TBOGT_PAD_DAT_CARGRP:
				{
					strPathToFile = CString("%s/TBoGT/common/data/cargrp.dat",g_pCore->GetGame()->GetEFLCDirectory().Get());
					break;
				}

				case TBOGT_PAD_DAT_VEHICLEEXTRAS:
				{
					strPathToFile = CString("%s/TBoGT/common/data/vehicleextras.dat",g_pCore->GetGame()->GetEFLCDirectory().Get());
					break;
				}

				case TBOGT_PAD_CSV_VEHOFF:
				{
					strPathToFile = CString("%s/TBoGT/common/data/vehOff.csv",g_pCore->GetGame()->GetEFLCDirectory().Get());
					break;
				}

				case DEFAULT_FILE_HOOK:
				{
					char * szPath = (char *)SharedUtility::GetAppPath();

					for(size_t x = 0; x < strlen(szPath); x++)
					{
						if(szPath[x] == '\\')
							szPath[x] = '/';
					}

					strPathToFile = CString("%smultiplayer/gamefiles/%s", szPath, ImportItems[i].strArea.Get());
					break;
				}
				default:
				{
					strPathToFile = CString("%s/pc/data/maps/%s/%s",g_pCore->GetGame()->GetEFLCDirectory().Get(),ImportItems[i].strArea.Get(),ImportItems[i].strImportName.Get());
					break;
				}
			}


			ImportItems[i].bLoaded = true;
			
			SAFE_DELETE(file);
			file = new char[strPathToFile.GetLength() + 1];
			
			sprintf(file, strPathToFile.Get());

			CLogFile::Printf("CEFLCSupport - Hook loading file: %s",strPathToFile.Get());
			return true;
		}
	}

	return false;
}

_declspec(naked) void _stdcall OpenFileHook()
{
	_asm	mov file_ptr, edx;
	_asm	pushad;

	//CLogFile::Printf("OpenFile %s", file_ptr);

	dwJmp2 = (g_pCore->GetBase() + 0x5B2796);
	sub_5B4F60 = (g_pCore->GetBase() + 0x5B4F60);

	if(Should(file_ptr))
	{
		_asm	mov eax, file;
		_asm	mov file_ptr, eax;
		_asm	;mov edx, [eax];
		_asm	popad;
		_asm	push file;
	}
	else
	{
		_asm	popad;
		_asm	push edx;
	}

	_asm	call sub_5B4F60;
	_asm	add esi, 1;
	_asm	add esp, 8;
	_asm	jmp dwJmp2;
}


void CEFLCSupport::InstallSupport()
{
	// If our user wants to load the EFLC map, hook the function
	if(g_pCore->GetGame()->IsUsingEFLCContent())
		CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x5B278A, (DWORD)OpenFileHook);
}