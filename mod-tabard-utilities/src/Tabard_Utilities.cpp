/*

Modified and adapted to AzerothCore by Voicot [2021]
*Implemented new features.
Based on Lightnig Blade's original work.

Description: Allow players to obtain reputation, gold, or certain items by simply equipping tabards while slaying creatures (in/out) of instances (Zones).

*/

#include "Creature.h"
#include "Player.h"
#include "ReputationMgr.h"
#include "ScriptMgr.h"
#include "WorldSession.h"



void LoadTabardInfo();

struct TabardInfo
{
    uint8 Function;
    uint8  Requirements;
    uint32 ZoneID;
    uint32 enemyFactionID;
    uint32 CreatureEntry;
    uint32 factionID;
    uint32 Value;
    uint32 Count;
};

typedef std::map<uint32, TabardInfo> TabardMap;
TabardMap m_TabardMap;

void LoadTabardInfo()
{
    uint32 oldMSTime = getMSTime();

    m_TabardMap.clear();

    QueryResult result = CharacterDatabase.Query("SELECT * FROM tabard_utilities");

    if (!result)
    {
        LOG_INFO("server.loading", ">> Loaded 0 rows from `tabard_utilities` table is empty!");
        LOG_INFO("server.loading", " ");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 TEntry = fields[0].GetUInt32();

        if (!sObjectMgr->GetItemTemplate(TEntry))
        {
            LOG_ERROR("sql.sql", "Tabard Utilities (Tabard: %u) does not exist but has a record in `tabard_utilities`", TEntry);
            continue;
        }
        TabardInfo data;
        data.Function       = fields[1].GetUInt32();
        data.Requirements   = fields[2].GetUInt32();
        data.ZoneID         = fields[3].GetUInt32();
        data.enemyFactionID = fields[4].GetUInt32();
        data.CreatureEntry  = fields[5].GetUInt32();
        data.factionID      = fields[6].GetUInt32();
        data.Value          = fields[7].GetUInt32();
        data.Count          = fields[8].GetUInt32();

        m_TabardMap.insert({TEntry, data});
        count++;
    } while (result->NextRow());

    LOG_INFO("server.loading", ">> Loaded %u Tabard Utilities rows in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    LOG_INFO("server.loading", " ");
}

class TU_WorldScript : public WorldScript
{
public:
    TU_WorldScript() : WorldScript("TU_WorldScript") {}

    void OnStartup() override
    {
        LOG_INFO("server.loading", "Initialize Tabard Utilities...");
        LoadTabardInfo();

    }
};



class Tabard_Utilities : public PlayerScript
{
public:
    Tabard_Utilities() : PlayerScript("Tabard_Utilities") {}

    void OnCreatureKill(Player* player, Creature* creature)
    {
        // Check if they have a tabard equipped
        if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_TABARD))
        {
            uint32 TabardEntry = item->GetEntry();
            
            // Find what tabard it is, and then see if it's valid 
            std::map<uint32, TabardInfo>::iterator it;
            it = m_TabardMap.find(TabardEntry);
            if (it != m_TabardMap.end())
            {
                uint32 Function       = it->second.Function;
                uint32 Requirements   = it->second.Requirements;
                uint32 enemyFactionID = it->second.enemyFactionID;
                uint32 ZoneID         = it->second.ZoneID;
                uint32 CreatureEntry  = it->second.CreatureEntry;
                uint32 factionID      = it->second.factionID;
                uint32 Value          = it->second.Value;
                uint32 Count          = it->second.Count;
                // Find out if the player is in the correct zone / area / instance to recieve the reputation from the tabard

                // Functions 0 = Reputation, 1 = Gold, 2 = Item[s]
                
                if (Function < 0 && Function > 2)
                    return;

                /*0 = No Requirements,
                  1 = EnemyFactionID requirement,
                  2 = ZoneID requirement
                  3 = Specific CreatureEntry
                  4 = ZoneID and EnemyFactionID requirements
                */ 
                
                if (Requirements < 0 && Requirements > 4)
                    return;

                if (Requirements == 1 || Requirements == 4)
                {
                    if (creature->GetFaction() != enemyFactionID)
                        return;

                    if (Requirements == 4)
                        if (player->GetZoneId() != ZoneID)
                            return;
                }

                if (Requirements == 2)
                    if (player->GetZoneId() != ZoneID)
                        return;

                if (Requirements == 3)
                    if (creature->GetEntry() != CreatureEntry)
                        return;

                // Reward Reputation
                if (Value <= 0)
                    return;

                switch (Function)
                {
                case 0:
                    {
                    FactionEntry const* factionEntry = sFactionStore.LookupEntry(factionID);
                    if (!factionEntry)
                        return;

                    if (player->GetReputationMgr().GetReputation(factionEntry) < 42000)
                    {
                        player->GetReputationMgr().SetOneFactionReputation(factionEntry, Value, true);
                        player->GetReputationMgr().SendState(player->GetReputationMgr().GetState(factionEntry));
                    }
                    }
                    break;
                case 1:
                    {
                        uint32 gold = Value * GOLD;
                        player->ModifyMoney(gold, true);
                    }
                    break;
                case 2:
                    {
						if (Count <= 0)
							return;
						
                    player->AddItem(Value, Count);
                    }
                    break;

                default:
                        break;


                }
            }
        }
    }
};


void AddTabard_UtilitiesScripts()
{
    new Tabard_Utilities();
    new TU_WorldScript();
}
