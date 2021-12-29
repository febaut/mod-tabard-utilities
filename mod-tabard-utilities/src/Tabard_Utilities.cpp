
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
            
            // Find what tabard it is, and then see if it's valid for reputation gain
            QueryResult ItemResult = CharacterDatabase.PQuery("SELECT * FROM tabard_utilities WHERE TEntry=%u", TabardEntry);

            if (ItemResult)
            {
                Field* ItemField      = ItemResult->Fetch();
                uint8  Function       = ItemField[1].GetUInt8();
                uint8  Requirements   = ItemField[2].GetUInt8();
                uint32 ZoneID         = ItemField[3].GetUInt32();
                uint32 enemyFactionID = ItemField[4].GetUInt32();
                uint32 CreatureEntry  = ItemField[5].GetUInt32();
                uint32 factionID      = ItemField[6].GetUInt32();
                uint32 Value          = ItemField[7].GetUInt32();
                uint32 Count          = ItemField[8].GetUInt32();


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
}
