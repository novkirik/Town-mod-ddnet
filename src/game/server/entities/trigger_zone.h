#ifndef GAME_SERVER_ENTITIES_TRIGGER_ZONE_H
#define GAME_SERVER_ENTITIES_TRIGGER_ZONE_H

#include <game/server/entity.h>

class CTriggerZone : public CEntity
{
    private:


        int m_ScoreTickForRed;
        int m_ScoreTickForBlue;
        bool m_PlayerInZone[MAX_CLIENTS];
        static int m_ZonesPlayerIn[MAX_CLIENTS];
        static int m_aLastTeam[MAX_CLIENTS];
        int m_RedPlayersinZone;
        int m_BluePlayersinZone;

        static int s_RedPlayersinZone;
        static int s_BluePlayersinZone;
        static int s_MaxPlayersinZone;
        static int s_ScoreTickForRed;
        static int s_ScoreTickForBlue;
        static int s_ServerTick;
        static int s_EntityTick;
    
    public:
        CTriggerZone(CGameWorld * pGameWorld, vec2 Pos);

        virtual void Tick() override;
};
#endif