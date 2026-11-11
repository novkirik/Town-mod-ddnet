#include "TCP.h"

#include <game/server/entities/character.h>
#include <game/server/player.h>

CGameControllerTCP::CGameControllerTCP(class CGameContext *pGameServer) :
	CGameControllerCapture(pGameServer)
{
	m_GameFlags = GAMEFLAG_FLAGS | GAMEFLAG_TEAMS;
	m_pGameType = "TCP";
	m_DefaultWeapon = WEAPON_HAMMER;

	m_pStatsTable = "TCP";
	m_pExtraColumns = nullptr;

	Db()->Stats()->SetExtraColumns(m_pExtraColumns);
	Db()->Stats()->CreateTable(m_pStatsTable);
}

CGameControllerTCP::~CGameControllerTCP() = default;

void CGameControllerTCP::Tick()
{
	CGameControllerCapture::Tick();


}

void CGameControllerTCP::OnCharacterSpawn(class CCharacter *pChr)
{
	CGameControllerCapture::OnCharacterSpawn(pChr);
	OnlyOneUnFreeze=false;
	OnlyOneHP=false;

	// give default weapons
	pChr->GiveWeapon(WEAPON_HAMMER, false, -1);
	pChr->GiveWeapon(WEAPON_GUN, false, 10);
}

REGISTER_GAMEMODE(TCP, CGameControllerTCP(pGameServer));
