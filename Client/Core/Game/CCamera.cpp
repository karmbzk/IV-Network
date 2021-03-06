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

#include <Common.h>

#include "CCamera.h"
#include <Game/EFLC/CScript.h>
#include <Ptrs.h>

#include <CCore.h>

extern CCore* g_pCore;


CCamera::CCamera() :
	m_bUsingScriptingCam(false)
{
	// Create the game cam instance
	m_pGameCam = new EFLC::CCam(*(EFLC::ICam**) ((unsigned char*)COffsets::RAGE_Camera__UnkownVoidPtr + 12));

	// Create the script cam
	unsigned int uiScriptCam;
	EFLC::CScript::CreateCam(14, &uiScriptCam);
	EFLC::CScript::SetCamPropagate(uiScriptCam, true);

	// Create the script cam instance
	m_pScriptCam = new EFLC::CCam(g_pCore->GetGame()->GetPools()->GetCamPool()->AtHandle(uiScriptCam));
}

CCamera::~CCamera()
{
	// Remove the camera
	EFLC::CScript::DestroyCam(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()));
}

void CCamera::Reset()
{ }

void CCamera::SetCameraPosition(CVector3 &vecPosition)
{
	if(!m_bUsingScriptingCam)
	{
		EFLC::CScript::ActivateScriptedCams(true, true);
		EFLC::CScript::SetCamActive(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), true);
		m_bUsingScriptingCam = true;
	}

	EFLC::CScript::SetCamPos(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), vecPosition.fX, vecPosition.fY, vecPosition.fZ);
}

void CCamera::GetCameraPosition(CVector3 &vecPosition)
{
	if(!m_bUsingScriptingCam)
	{
		EFLC::CScript::ActivateScriptedCams(true, true);
		EFLC::CScript::SetCamActive(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), true);
		m_bUsingScriptingCam = true;
	}

	EFLC::CScript::GetCamPos(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), &vecPosition.fX, &vecPosition.fY, &vecPosition.fZ);
}

void CCamera::SetLookAtPosition(CVector3 &vecPosition)
{
	if(!m_bUsingScriptingCam)
	{
		EFLC::CScript::ActivateScriptedCams(true, true);
		EFLC::CScript::SetCamActive(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), true);
		m_bUsingScriptingCam = true;
	}

	CGameFunction::LoadWorldAtPosition(vecPosition);

	EFLC::CScript::PointCamAtCoord(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), vecPosition.fX, vecPosition.fY, vecPosition.fZ);
}

void CCamera::SetCamBehindPed(unsigned int uiPed)
{
	if(m_bUsingScriptingCam)
	{
		EFLC::CScript::ActivateScriptedCams(false, false);
		EFLC::CScript::SetCamActive(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), true);
		m_bUsingScriptingCam = false;
	}

	EFLC::CScript::SetCamBehindPed(uiPed);
}

void CCamera::GetAimPosition(CVector3 *vecPosition)
{
	if(m_bUsingScriptingCam)
	{
		EFLC::CScript::ActivateScriptedCams(false, false);
		EFLC::CScript::SetCamActive(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), true);
		m_bUsingScriptingCam = false;
	}

	// Define all vectors.
	CVector3 vecCamPosition;
	CVector3 vecCamForward;

	// Get all data from game camera.
	EFLC::CScript::GetCamPos(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), &vecCamPosition.fX, &vecCamPosition.fY, &vecCamPosition.fZ);

	// Get cam forward.
	vecCamForward = CVector3(m_pGameCam->GetCam()->m_data1.m_matMatrix.vecForward.fX,m_pGameCam->GetCam()->m_data1.m_matMatrix.vecForward.fY,m_pGameCam->GetCam()->m_data1.m_matMatrix.vecForward.fZ);

	// Scale calc.
	CVector3 vecFinalCamLookAt = Math::GetOffsetDegrees(vecCamPosition,vecCamForward);
	float fScale = (vecFinalCamLookAt.Length()/2);

	vecPosition->fX = (vecCamPosition.fX + (vecCamForward.fX * fScale));
	vecPosition->fY = (vecCamPosition.fY + (vecCamForward.fY * fScale));
	vecPosition->fZ = (vecCamPosition.fZ + (vecCamForward.fZ * fScale));
}

void CCamera::GetLookAt(CVector3& vecLookAt)
{
	EFLC::CCam * pGameCam = GetGameCam();
	CVector3 vecCamPosition;
	CVector3 vecCamForward;
	CVector3 vecCamLookAt;

	pGameCam->GetPosition(vecCamPosition);
	pGameCam->GetCam()->m_data1.m_matMatrix.vecForward.ToVector3(vecCamForward);
	vecCamLookAt.fX = vecCamPosition.fX + vecCamForward.fX;
	vecCamLookAt.fY = vecCamPosition.fY + vecCamForward.fY;
	vecCamLookAt.fZ = vecCamPosition.fZ + vecCamForward.fZ;

	CVector3 vecFinalCamLookAt = Math::GetOffsetDegrees(vecCamPosition, vecCamForward);
	float fScale = (vecFinalCamLookAt.Length() / 2);

	vecCamLookAt.fX = vecCamPosition.fX + (vecCamForward.fX * fScale);
	vecCamLookAt.fY = vecCamPosition.fY + (vecCamForward.fY * fScale);
	vecCamLookAt.fZ = vecCamPosition.fZ + (vecCamForward.fZ * fScale);

	memcpy(&vecLookAt, &vecCamLookAt, sizeof(CVector3));
}

bool CCamera::IsOnScreen(const CVector3& vecPosition)
{
	CVector3 vecCamPos;
	GetGameCam()->GetPosition(vecCamPos);

	CVector3 vecCamLookAt;
	GetLookAt(vecCamLookAt);

	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, CVEC_TO_D3DVEC(vecCamPos), CVEC_TO_D3DVEC(vecCamLookAt), CVEC_TO_D3DVEC(CVector3(0, 0, 1)));

	D3DVIEWPORT9 viewport;
	g_pCore->GetGraphics()->GetDevice()->GetViewport(&viewport);

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, GetGameCam()->GetCam()->m_data1.m_fFOV, (float) viewport.Width / (float) viewport.Height, GetGameCam()->GetCam()->m_data1.m_fNear, GetGameCam()->GetCam()->m_data1.m_fFar);

	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXVECTOR3 vecSPos;
	D3DXVec3Project(&vecSPos, CVEC_TO_D3DVEC(vecPosition), &viewport, &matProj, &matView, &matWorld);

	return (vecSPos.z < 1.f);
}
