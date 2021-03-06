//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CScriptClasses.cpp
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CScriptClasses.h"
#include <Scripting/CLuaVM.h>
#include <Scripting/CSquirrelVM.h>
#include <CLogFile.h>
#include <Scripting/ResourceSystem/CResourceManager.h>
#include "../../../Server/Scripting/Natives/Natives_Server.h"
#include "Entity/Entities.h"
#include "CTimer.h"
#include <CXML.h>
#include <CServer.h>

int IsPlayerConnected(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	int id;
	pVM->Pop(id);

	pVM->Push(CServer::GetInstance()->GetPlayerManager()->DoesExists((EntityId)id));

	return 1;
}

int GetPlayerById(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	int id;
	pVM->Pop(id);

	if (CServer::GetInstance()->GetPlayerManager()->DoesExists((EntityId)id))
	{
		pVM->PushInstance("CPlayerEntity", CServer::GetInstance()->GetPlayerManager()->GetAt((EntityId)id)->GetScriptPlayer());
		return 1;
	}
	pVM->Push(false);

	return 1;
}

int SendPlayerMessageToAll(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	CString sMessage;
	pVM->Pop(sMessage);

	int iColor;
	pVM->Pop(iColor);

	bool bAllowFormatting;
	pVM->Pop(bAllowFormatting);

	RakNet::BitStream bitStream;
	bitStream.Write(RakNet::RakString(sMessage.C_String()));
	bitStream.Write((DWORD)iColor);
	bitStream.Write(bAllowFormatting);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_MESSAGE_TO_ALL), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);

	pVM->Push(true);

	return 1;
}

int CreateVehicle(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	int vehicleModel;
	pVM->Pop(vehicleModel);
	
	CVector3 vecPosition;
	pVM->Pop(vecPosition);

	float fAngle;
	pVM->Pop(fAngle);

	DWORD color1;
	pVM->Pop(color1);

	DWORD color2;
	pVM->Pop(color2);

	DWORD color3;
	pVM->Pop(color3);

	DWORD color4;
	pVM->Pop(color4);

	DWORD color5;
	pVM->Pop(color5, 0xFFFFFFFF);

	CVehicleEntity * pVehicle = new CVehicleEntity();
	pVehicle->SetId(CServer::GetInstance()->GetVehicleManager()->FindFreeSlot());
	CServer::GetInstance()->GetVehicleManager()->Add(pVehicle->GetId(), pVehicle);
	pVehicle->SetModelId(vehicleModel);
	pVehicle->SetPosition(vecPosition);
	pVehicle->SetRotation(CVector3(fAngle, 0.0f, 0.0f));
	pVehicle->SetColor(1, color1);
	pVehicle->SetColor(2, color2);
	pVehicle->SetColor(3, color3);
	pVehicle->SetColor(4, color4);
	pVehicle->SetColor(5, color5);

	RakNet::BitStream bitStream;
	bitStream.Write(pVehicle->GetId());
	bitStream.Write(vehicleModel);
	bitStream.Write(vecPosition);
	bitStream.Write(fAngle);
	bitStream.Write(color1);
	bitStream.Write(color2);
	bitStream.Write(color3);
	bitStream.Write(color4);
	bitStream.Write(color5);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_CREATE_VEHICLE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);

	CScriptVehicle * pScriptVehicle = new CScriptVehicle();
	pScriptVehicle->SetEntity(pVehicle);
	pVehicle->SetScriptVehicle(pScriptVehicle);
	pVM->PushInstance("CVehicleEntity", pScriptVehicle);
	return 1;
}

int CreateCheckpoint(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	int iType;
	pVM->Pop(iType);

	CVector3 vecPosition;
	pVM->Pop(vecPosition);

	CVector3 vecNextPosition;
	pVM->Pop(vecNextPosition);

	float fRadius;
	pVM->Pop(fRadius);

	CCheckpointEntity * pCheckpoint = new CCheckpointEntity();
	pCheckpoint->SetId(CServer::GetInstance()->GetCheckpointManager()->FindFreeSlot());
	CServer::GetInstance()->GetCheckpointManager()->Add(pCheckpoint->GetId(), pCheckpoint);
	pCheckpoint->SetType(iType);
	pCheckpoint->SetPosition(vecPosition);
	pCheckpoint->SetTargetPosition(vecNextPosition);
	pCheckpoint->SetRadius(fRadius);
	pCheckpoint->SetVisible(true);

	RakNet::BitStream bitStream;
	bitStream.Write(pCheckpoint->GetId());
	bitStream.Write(iType);
	bitStream.Write(vecPosition);
	bitStream.Write(vecNextPosition);
	bitStream.Write(fRadius);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_CREATE_CHECKPOINT), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);

	CScriptCheckpoint * pScriptCheckpoint = new CScriptCheckpoint();
	pScriptCheckpoint->SetEntity(pCheckpoint);
	pCheckpoint->SetScriptCheckpoint(pScriptCheckpoint);
	pVM->PushInstance("CCheckpointEntity", pScriptCheckpoint);
	return 1;
}

int CreateBlip(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	unsigned int iIcon;
	pVM->Pop(iIcon);

	CVector3 vecPosition;
	pVM->Pop(vecPosition);

	bool bRange;
	pVM->Pop(bRange);

	CBlipEntity * pBlip = new CBlipEntity();
	pBlip->SetId(CServer::GetInstance()->GetBlipManager()->FindFreeSlot());
	CServer::GetInstance()->GetBlipManager()->Add(pBlip->GetId(), pBlip);
	pBlip->SetIcon(iIcon);
	pBlip->SetPosition(vecPosition);
	pBlip->SetRange(bRange);

	RakNet::BitStream bitStream;
	bitStream.Write(pBlip->GetId());
	bitStream.Write(iIcon);
	bitStream.Write(vecPosition);
	bitStream.Write(bRange);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_CREATE_BLIP), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);

	CScriptBlip * pScriptBlip = new CScriptBlip();
	pScriptBlip->SetEntity(pBlip);
	pBlip->SetScriptBlip(pScriptBlip);
	pVM->PushInstance("CBlipEntity", pScriptBlip);
	return 1;
}

int CreateTimer(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	stScriptFunction function;
	pVM->Pop(function);

	int interval;
	pVM->Pop(interval);

	int repeatings;
	pVM->Pop(repeatings);

	CTimer* pTimer = new CTimer(function, interval, repeatings);
	CServer::GetInstance()->GetTimerManager()->push_back(pTimer);

	CScriptTimer * pScriptTimer = new CScriptTimer();
	pScriptTimer->SetTimer(pTimer);
	pTimer->SetScriptTimer(pScriptTimer);
	pVM->PushInstance("CTimer", pScriptTimer);

	return 1;
}

int OpenXML(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	CString strFilePath;
	pVM->Pop(strFilePath);

	CScriptXML* pScriptXML = new CScriptXML();
	pScriptXML->load(strFilePath);
	pVM->PushInstance("CXML", pScriptXML);

	return 1;
}

int CreateFolder(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	CString folderName;
	pVM->Pop(folderName);

	SharedUtility::CreateDirectory(SharedUtility::GetAbsolutePath(folderName));

	pVM->Push(SharedUtility::Exists(SharedUtility::GetAbsolutePath(folderName)));

	return 1;
}

int Exists(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	CString pathName;
	pVM->Pop(pathName);

	pVM->Push(SharedUtility::Exists(SharedUtility::GetAbsolutePath("/%s", pathName.C_String())));

	return 1;
}

class CScriptSQLite
{
public:
	CScriptSQLite();
	~CScriptSQLite();

	bool Open(CString strFileName);
	void Query(CString strQuery, CString callback);
	void Close();
};

class CScriptMysql
{
public:
	CScriptMysql();
	~CScriptMysql();
};

void CScriptClasses::Register(IScriptVM * pVM)
{
	pVM->RegisterFunction("createVehicle", CreateVehicle);
	pVM->RegisterFunction("getPlayerById", GetPlayerById);
	pVM->RegisterFunction("isPlayerConnected", IsPlayerConnected);
	pVM->RegisterFunction("sendMessageToAll", SendPlayerMessageToAll);
	pVM->RegisterFunction("createCheckpoint", CreateCheckpoint);
	pVM->RegisterFunction("createBlip", CreateBlip);
	pVM->RegisterFunction("createTimer", CreateTimer);
	pVM->RegisterFunction("openXML", OpenXML);
	pVM->RegisterFunction("createFolder", CreateFolder);
	pVM->RegisterFunction("exists", Exists);

#if 0
	(new CScriptClass<CScriptSQLite>("CSQLite"))->
		AddMethod("open", &CScriptSQLite::Open).
		AddMethod("query", &CScriptSQLite::Query).
		AddMethod("close", &CScriptSQLite::Close).
		Register(pVM);
#endif // 0

#if 0
	(new CScriptClass<CScriptMySQL>("CMySQL"))->
		AddMethod("open", &CScriptMySQL::Open).
		AddMethod("query", &CScriptMySQL::Query).
		AddMethod("close", &CScriptMySQL::Close).
		Register(pVM);
#endif
	{ // ScriptXML
		static CScriptClass<CScriptXML>* pScriptXML = &(new CScriptClass<CScriptXML>("CXML"))->
			AddMethod("save", &CScriptXML::save).
			AddMethod("close", &CScriptXML::close).
			AddMethod("setTabSize", &CScriptXML::setTabSize).
			AddMethod("getAttribute", &CScriptXML::getAttribute).
			AddMethod("removeAttribute", &CScriptXML::removeAttribute).
			AddMethod("setAttribute", &CScriptXML::setAttribute).
			AddMethod("nodeName", &CScriptXML::nodeName).
			AddMethod("nodeSetName", &CScriptXML::nodeSetName).
			AddMethod("nodeContent", &CScriptXML::nodeContent).
			AddMethod("nodeSetContent", &CScriptXML::nodeSetContent).
			AddMethod("nodeToRoot", &CScriptXML::nodeToRoot).
			AddMethod("findNode", &CScriptXML::findNode).
			AddMethod("nextNode", &CScriptXML::nextNode).					
			AddMethod("previousNode", &CScriptXML::previousNode).
			AddMethod("childNodeFirst", &CScriptXML::childNodeFirst).
			AddMethod("nodeParent", &CScriptXML::nodeParent).
			AddMethod("nodeClear", &CScriptXML::nodeClear).
			AddMethod("newNode", &CScriptXML::newNode).
			AddMethod("newComment", &CScriptXML::newComment).
			AddMethod("lastError", &CScriptXML::lastError).
			AddMethod("isComment", &CScriptXML::isComment);
		(pScriptXML)->Register(pVM);
	}

	{ // ScriptPlayer
		static CScriptClass<CScriptPlayer>* pScriptPlayer = &(new CScriptClass<CScriptPlayer>("CPlayerEntity"))->
			AddMethod("setPosition", &CScriptPlayer::SetPosition). // Synced
			AddMethod("setRotation", &CScriptPlayer::SetRotation). // Synced
			AddMethod("setMoveSpeed", &CScriptPlayer::SetMoveSpeed). // Synced
			AddMethod("setTurnSpeed", &CScriptPlayer::SetTurnSpeed). // Synced
			AddMethod("getPosition", &CScriptPlayer::GetPosition). // Synced
			AddMethod("getRotation", &CScriptPlayer::GetRotation). // Synced
			AddMethod("getMoveSpeed", &CScriptPlayer::GetMoveSpeed). // Synced
			AddMethod("getTurnSpeed", &CScriptPlayer::GetTurnSpeed). // Synced
			AddMethod("getArmour", &CScriptPlayer::GetArmour). // Synced
			AddMethod("setArmour", &CScriptPlayer::SetArmour). // Synced
			AddMethod("getHealth", &CScriptPlayer::GetHealth). // Synced
			AddMethod("setHealth", &CScriptPlayer::SetHealth). // Synced
			AddMethod("getHeading", &CScriptPlayer::GetHeading). // Synced
			AddMethod("setHeading", &CScriptPlayer::SetHeading). // Synced
			AddMethod("getModel", &CScriptPlayer::GetModel). // Synced
			AddMethod("setModel", &CScriptPlayer::SetModel). // Synced
			AddMethod("getDimension", &CScriptPlayer::GetDimension).
			AddMethod("setDimension", &CScriptPlayer::SetDimension).
			AddMethod("getName", &CScriptPlayer::GetName). // Synced
			AddMethod("setName", &CScriptPlayer::SetName). // Synced
			AddMethod("getMoney", &CScriptPlayer::GetMoney). // Synced
			AddMethod("setMoney", &CScriptPlayer::SetMoney). // Synced
			AddMethod("getWantedLevel", &CScriptPlayer::GetWantedLevel). // Synced
			AddMethod("setWantedLevel", &CScriptPlayer::SetWantedLevel). // Synced
			AddMethod("giveWeapon", &CScriptPlayer::GiveWeapon). // Synced
			AddMethod("getWeaponType", &CScriptPlayer::GetWeaponType). // Synced
			AddMethod("getWeaponAmmo", &CScriptPlayer::GetWeaponAmmo). // Synced
			AddMethod("giveMoney", &CScriptPlayer::GiveMoney). // Synced
			AddMethod("setColor", &CScriptPlayer::SetColor). // Synced
			AddMethod("getColor", &CScriptPlayer::GetColor). // Synced
			AddMethod("sendMessage", &CScriptPlayer::SendPlayerMessage). // Synced
			AddMethod("getId", &CScriptPlayer::GetId). // Synced
			AddMethod("setHudElementVisible", &CScriptPlayer::SetHudElementVisible). // Synced		
			AddMethod("setClothes", &CScriptPlayer::SetClothes). // Synced	
			AddMethod("getClothes", &CScriptPlayer::GetClothes). // Synced	
			AddMethod("isOnFoot", &CScriptPlayer::IsOnFoot).
			AddMethod("spawn", &CScriptPlayer::Spawn).
			AddMethod("kill", &CScriptPlayer::Kill).
			AddMethod("isSpawned", &CScriptPlayer::IsSpawned).
			AddMethod("getVehicle", &CScriptPlayer::GetVehicle).
			AddMethod("getVehicleSeat", &CScriptPlayer::GetVehicleSeat).
			AddMethod("putIntoVehicle", &CScriptPlayer::PutIntoVehicle).
			AddMethod("removeFromVehicle", &CScriptPlayer::RemoveFromVehicle).
			AddMethod("getSerial", &CScriptPlayer::GetSerial).
			AddMethod("getPing", &CScriptPlayer::GetPing).
			AddMethod("kick", &CScriptPlayer::Kick).
			AddMethod("triggerPlayerEvent", &CScriptPlayer::TriggerPlayerEvent);
		(pScriptPlayer)->Register(pVM);
	}

	{ // ScriptVehicle
		static CScriptClass<CScriptVehicle>* pScriptVehicle = &(new CScriptClass<CScriptVehicle>("CVehicleEntity"))->
			//AddMethod("deleteVehicle", &CScriptVehicle::DeleteVehicle).
			AddMethod("setPosition", &CScriptVehicle::SetPosition).
			AddMethod("getPosition", &CScriptVehicle::GetPosition).
			AddMethod("setRotation", &CScriptVehicle::SetRotation).
			AddMethod("getRotation", &CScriptVehicle::GetRotation).
			AddMethod("setMoveSpeed", &CScriptVehicle::SetMoveSpeed).
			AddMethod("setTurnSpeed", &CScriptVehicle::SetTurnSpeed).
			AddMethod("setHealth", &CScriptVehicle::SetHealth).
			AddMethod("getHealth", &CScriptVehicle::GetHealth).
			AddMethod("setLocked", &CScriptVehicle::SetLocked).
			AddMethod("getLocked", &CScriptVehicle::GetLocked).
			AddMethod("setSiren", &CScriptVehicle::SetSiren).
			AddMethod("getSiren", &CScriptVehicle::GetSiren).
			AddMethod("setLights", &CScriptVehicle::SetLights).
			AddMethod("getLights", &CScriptVehicle::GetLights).
			AddMethod("setTaxiLights", &CScriptVehicle::SetTaxiLights).
			AddMethod("getTaxiLights", &CScriptVehicle::GetTaxiLights).
			AddMethod("setEngine", &CScriptVehicle::SetEngine).
			AddMethod("getEngine", &CScriptVehicle::GetEngine).
			AddMethod("getHorn", &CScriptVehicle::GetHorn).
			AddMethod("setDirtLevel", &CScriptVehicle::SetDirtLevel).
			AddMethod("getDirtLevel", &CScriptVehicle::GetDirtLevel);
		(pScriptVehicle)->Register(pVM);
	}

	{ // ScriptCheckpoint
		static CScriptClass<CScriptCheckpoint>* pScriptCheckpoint = &(new CScriptClass<CScriptCheckpoint>("CCheckpointEntity"))->
			AddMethod("deleteCheckpoint", &CScriptCheckpoint::DeleteCheckpoint).
			AddMethod("showForPlayer", &CScriptCheckpoint::ShowForPlayer).
			AddMethod("hideForPlayer", &CScriptCheckpoint::HideForPlayer).
			AddMethod("showForAll", &CScriptCheckpoint::ShowForAll).
			AddMethod("hideForAll", &CScriptCheckpoint::HideForAll).
			AddMethod("setType", &CScriptCheckpoint::SetType).
			AddMethod("getType", &CScriptCheckpoint::GetType).
			AddMethod("setPosition", &CScriptCheckpoint::SetPosition).
			AddMethod("getPosition", &CScriptCheckpoint::GetPosition).
			AddMethod("setTargetPosition", &CScriptCheckpoint::SetTargetPosition).
			AddMethod("getTargetPosition", &CScriptCheckpoint::GetTargetPosition).
			AddMethod("setRadius", &CScriptCheckpoint::SetRadius).
			AddMethod("getRadius", &CScriptCheckpoint::GetRadius);
		(pScriptCheckpoint)->Register(pVM);
	}

	{ // ScriptBlip
		static CScriptClass<CScriptBlip>* pScriptBlip = &(new CScriptClass<CScriptBlip>("CBlipEntity"))->
			AddMethod("setPosition", &CScriptBlip::SetPosition).
			AddMethod("getPosition", &CScriptBlip::GetPosition).
			AddMethod("setIcon", &CScriptBlip::SetIcon).
			AddMethod("getIcon", &CScriptBlip::GetIcon).
			AddMethod("setColor", &CScriptBlip::SetColor).
			AddMethod("getColor", &CScriptBlip::GetColor).
			AddMethod("setRange", &CScriptBlip::SetRange).
			AddMethod("getRange", &CScriptBlip::GetRange).
			AddMethod("setVisible", &CScriptBlip::SetVisible).
			AddMethod("getVisible", &CScriptBlip::GetVisible).
			AddMethod("setName", &CScriptBlip::SetName).
			AddMethod("getName", &CScriptBlip::GetName);
		(pScriptBlip)->Register(pVM);
	}

	{ // ScriptTimer
		static CScriptClass<CScriptTimer>* pScriptTimer = &(new CScriptClass<CScriptTimer>("CTimer"))->
			AddMethod("start", &CScriptTimer::Start).
			AddMethod("stop", &CScriptTimer::Stop).
			AddMethod("pause", &CScriptTimer::Pause).
			AddMethod("resume", &CScriptTimer::Resume);
		(pScriptTimer)->Register(pVM);
	}
}
