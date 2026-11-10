
#include "trigger_zone.h"
#include <game/server/gamecontext.h>
#include <game/server/player.h>
#include <game/server/entities/character.h>
#include <game/mapitems.h>
#include <engine/shared/config.h>
#include <game/server/gamecontroller.h>
#include <base/dbg.h>


int CTriggerZone::s_RedPlayersinZone = 0;
int CTriggerZone::s_BluePlayersinZone = 0;
int CTriggerZone::s_ScoreTickForRed = 0;
int CTriggerZone::s_ScoreTickForBlue = 0;
int CTriggerZone::s_MaxPlayersinZone = 0;
int CTriggerZone::m_ZonesPlayerIn[MAX_CLIENTS] = {0};      
int CTriggerZone::m_aLastTeam[MAX_CLIENTS]; 

int CTriggerZone::s_EntityTick=0;
int CTriggerZone::s_ServerTick=-1;

CTriggerZone::CTriggerZone(CGameWorld *pGameWorld, vec2 Pos) 
    : CEntity(pGameWorld, CGameWorld::ENTTYPE_TRIGGER_ZONE, false, Pos)
{
    m_Pos = Pos;
    m_ScoreTickForBlue=0;
    m_ScoreTickForRed=0;
    m_BluePlayersinZone=0;
    m_RedPlayersinZone=0;
    mem_zero(m_PlayerInZone, sizeof(m_PlayerInZone));
    for(int i =0; i<MAX_CLIENTS;i++)
    {
        m_aLastTeam[i] = TEAM_SPECTATORS;
    }



    GameWorld()->InsertEntity(this);
}

void CTriggerZone::Tick()
{

    int TickNow = Server()->Tick();

    if(TickNow != s_ServerTick)
    {
        s_ServerTick = TickNow;
        s_EntityTick = 0;
    }

    s_EntityTick++;

    bool FirstEntity = (s_EntityTick==1);

    for(int i=0;i<MAX_CLIENTS;i++)
    {
        CCharacter *pChr = GameServer()->GetPlayerChar(i);
        
        if(!pChr)
        {
            if(m_PlayerInZone[i])
            {
                m_PlayerInZone[i] = false;
                m_ZonesPlayerIn[i]--;
                if(m_ZonesPlayerIn[i] == 0)
                {
                    if(m_aLastTeam[i] == TEAM_RED) s_RedPlayersinZone--;
                    else if(m_aLastTeam[i] == TEAM_BLUE) s_BluePlayersinZone--;
                    m_aLastTeam[i] = TEAM_SPECTATORS;
                }
            }
            
            continue;
        }

        int Team = pChr->GetPlayer()->GetTeam();

        if(Team != m_aLastTeam[i])
        {
            if(m_ZonesPlayerIn[i] > 0)
            {
                
                if(m_aLastTeam[i] == TEAM_RED) s_RedPlayersinZone--;
                else if(m_aLastTeam[i] == TEAM_BLUE) s_BluePlayersinZone--;
                if(Team==TEAM_RED) s_RedPlayersinZone++;
                else if(Team==TEAM_BLUE) s_BluePlayersinZone++;
            }

            m_aLastTeam[i] = Team;
        }
        
        if(Team == TEAM_SPECTATORS)
        {
            if(m_PlayerInZone[i])
            {
                m_PlayerInZone[i] = false;
                m_ZonesPlayerIn[i]--;
                if(m_ZonesPlayerIn[i]==0)
                {
                    if(m_aLastTeam[i]==TEAM_RED)
                    {
                        s_RedPlayersinZone--;
                    }
                    else if(m_aLastTeam[i]==TEAM_BLUE)
                    {
                        s_BluePlayersinZone--;
                    }
                }
            }
            continue;
        }



        if(distance(m_Pos, pChr->m_Pos) < 28.0f && m_PlayerInZone[i] == false)
        {
            m_PlayerInZone[i] = true;
            m_ZonesPlayerIn[i]++;
            
            if(m_ZonesPlayerIn[i] == 1)
            {
                if(Team == TEAM_RED)
                {
                    s_RedPlayersinZone++;
                }
                else if(Team == TEAM_BLUE)
                {
                    s_BluePlayersinZone++;
                }
            }
        }
        else if(!(distance(m_Pos, pChr->m_Pos) < 28.0f) && m_PlayerInZone[i] == true)
        {
            m_PlayerInZone[i] = false;
            m_ZonesPlayerIn[i]--;
            
            if(m_ZonesPlayerIn[i] == 0)
            {
                if(Team == TEAM_RED)
                {
                    s_RedPlayersinZone--;
                }
                else if(Team == TEAM_BLUE)
                {
                    s_BluePlayersinZone--;
                }
            }
        }

    }
    if(FirstEntity)
    {
        if(s_RedPlayersinZone > s_BluePlayersinZone)
        {
            //dbg_msg("trigger_zone", "Красных = %i", s_RedPlayersinZone);
            
            s_ScoreTickForBlue = 0;
            s_ScoreTickForRed++;
            if(s_ScoreTickForRed >= 15)
            {
                s_ScoreTickForRed = 0;
                //dbg_msg("trigger_zone", "Красных больше");
                GameServer()->m_pController->m_aTeamscore[TEAM_RED]++;
            }
        }
        else if(s_BluePlayersinZone > s_RedPlayersinZone)
        {
            //dbg_msg("trigger_zone", "Синих = %i", s_BluePlayersinZone);
            s_ScoreTickForRed = 0;
            s_ScoreTickForBlue++;
            if(s_ScoreTickForBlue >= 15)
            {
                s_ScoreTickForBlue = 0;
                //dbg_msg("trigger_zone", "Синих больше");
                GameServer()->m_pController->m_aTeamscore[TEAM_BLUE]++;
            }
        }
        else
        {
            s_ScoreTickForRed = 0;
            s_ScoreTickForBlue = 0;
        }
    }

}

