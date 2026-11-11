#ifndef INSTA_SERVER_GAMEMODES_CAPTURE_BASE_CAPTURE_H
#define INSTA_SERVER_GAMEMODES_CAPTURE_BASE_CAPTURE_H

#include "../base_pvp/base_pvp.h"


class CGameControllerCapture : public CGameControllerBasePvp
{
private:
	

public:
	CGameControllerCapture(class CGameContext *pGameServer);
	~CGameControllerCapture() override;
	bool OnlyOneHP;
	bool OnlyOneUnFreeze;
	void AddedHP(CCharacter *pCharacter) override;

	int SnapGameInfoExFlags(int SnappingClient, int DDRaceFlags) override;
	void OnFreeze(CPlayer *pPlayer) override;
	void OnUnfreeze(CPlayer *pPlayer) override;
	bool DecreaseHealthAndKill(int Dmg, int From, int Weapon, CCharacter *pCharacter) override;
	bool OnCharacterTakeDamage(vec2 &Force, int &Dmg, int &From, int &Weapon, CCharacter &Character) override;
	void OnAnyDamage(vec2 &Force, int &Dmg, int &From, int &Weapon, CCharacter *pCharacter) override;
	bool OnEntity(int Index, int x, int y, int Layer, int Flags, bool Initial, int Number) override;
	bool IsCaptureGameType() const override { return true; }
};
#endif
