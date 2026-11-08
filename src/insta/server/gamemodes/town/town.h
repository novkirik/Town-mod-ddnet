#ifndef INSTA_SERVER_GAMEMODES_TOWN_TOWN_H
#define INSTA_SERVER_GAMEMODES_TOWN_TOWN_H

#include "base_centry.h"

#define SQL_COLUMN_FILE <insta/server/gamemodes/vanilla/dm/sql_columns.h>
#define SQL_COLUMN_CLASS CDmColumns
#include <insta/server/column_template.h>


class CGameControllerTown : public CGameControllerCentry
{
private:


public:
	CGameControllerTown(class CGameContext *pGameServer);
	~CGameControllerTown() override;
	void OnCharacterSpawn(class CCharacter *pChr) override;
	void Tick() override;
};
#endif
