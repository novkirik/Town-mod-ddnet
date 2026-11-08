#include "town.h"

#include <game/server/entities/character.h>
#include <game/server/player.h>

CGameControllerTown::CGameControllerTown(class CGameContext *pGameServer) :
	CGameControllerCentry(pGameServer)
{
	m_GameFlags = GAMEFLAG_FLAGS | GAMEFLAG_TEAMS;
	m_pGameType = "town";
	m_DefaultWeapon = WEAPON_HAMMER;

	m_pStatsTable = "town";
	m_pExtraColumns = nullptr;

	Db()->Stats()->SetExtraColumns(m_pExtraColumns);
	Db()->Stats()->CreateTable(m_pStatsTable);
}

CGameControllerTown::~CGameControllerTown() = default;

void CGameControllerTown::Tick()
{
	CGameControllerCentry::Tick();


}

void CGameControllerTown::OnCharacterSpawn(class CCharacter *pChr)
{
	CGameControllerCentry::OnCharacterSpawn(pChr);
	OnlyOneUnFreeze=false;
	OnlyOneHP=false;

	// give default weapons
	pChr->GiveWeapon(WEAPON_HAMMER, false, -1);
	pChr->GiveWeapon(WEAPON_GUN, false, 10);
}

REGISTER_GAMEMODE(town, CGameControllerTown(pGameServer));
