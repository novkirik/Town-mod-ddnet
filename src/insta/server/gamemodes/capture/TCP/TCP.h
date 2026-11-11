#ifndef INSTA_SERVER_GAMEMODES_TCP_TCP_H
#define INSTA_SERVER_GAMEMODES_TCP_TCP_H

#include "../base_capture.h"

#define SQL_COLUMN_FILE <insta/server/gamemodes/vanilla/dm/sql_columns.h>
#define SQL_COLUMN_CLASS CDmColumns
#include <insta/server/column_template.h>


class CGameControllerTCP : public CGameControllerCapture
{
private:


public:
	CGameControllerTCP(class CGameContext *pGameServer);
	~CGameControllerTCP() override;
	void OnCharacterSpawn(class CCharacter *pChr) override;
	void Tick() override;
};
#endif
