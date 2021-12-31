# Mod-Tabard Utilities

## Description:

Allows players to obtain reputation, gold, or certain items by simply equipping tabards while slaying creatures (in/out) of instances (Zones).



## Installation
```
1. Simply place the module under the `modules` directory of your AzerothCore source. 
1. Import the SQL manually to the right Database  (characters in this case).
1. Re-run cmake and launch a clean build of AzerothCore.
```

## Edit the SQL Table (tabard_utilities)

**Table Structure**

| Field               | Type         | Attributes | Key | Null | Default       | 
| ------------------  | ------------ | ---------- | --- | ---- | ------------- | 
| [TEntry][0]         | INT          | UNSIGNED   | PRI | NO   | NO            |      
| [Function][1]       | INT          | UNSIGNED   |     | NO   | NO            |      
| [Requirements][2]   | INT          | UNSIGNED   |     | NO   | 0             |       
| [ZoneID][3]         | INT          | UNSIGNED   |     | NO   | 0             |      
| [EnemyFactionID][4] | INT          | UNSIGNED   |     | NO   | 0             |      
| [FactionID][5]      | INT          | UNSIGNED   |     | NO   | 0             |      
| [Value][6]          | INT          | UNSIGNED   |     | NO   | 0             |      
| [Count][7]          | INT          | UNSIGNED   |     | NO   | 1             |      
| [Comment][8]        | VARCHAR      | UNSIGNED   |     | NO   | 'Description' |  


**Description of the fields**

### TEntry
The entry of the tabard from item_template (One tabard can be used only for one purpose)

### Function
What the Tabard will be used for.
0 = Get Reputation
1 = Get Gold
2 = Get Items

### Requirements
Contidions to trigger the functions above.

0 = No requirements
1 = Requires an enemy faction.
2 = Requires an area from AreaTable.dbc.
3 = Requires a specific Creature entry
4 = Requires both area and enemy faction.

### ZoneID
Specific area from AreaTable.dbc where the creature must be killed.
Used when Requirements is 2 or 4.

### EnemyFactionID
The faction that the killed creature must have.
Used when Requirements is 1 or 4.

### FactionID
The faction that will be increased if Function is 0

### Value
The amount of reputation to add if Function is 0
The amount of GOLD to add if Function is 1
The ENTRY of the item to add if Function is 2

### Count
This column only works with Value Column if Function is 2, and reflects the amount of items to add.
Can't be negative. 
Can't be 0

### Comment
This column doesn't effect the system, is only for you to add some notes about what the tabard does. 

*Tips: There are some examples inside the table*
*7725 - Tabard of the Scarlet Crusade DEPRECATED*
*23709 - Tabard of Frost*
*35279 - Tabard of Summer Skies*
*Works with Blizzlike Tabards, but you might want to create custom ones*

## Credits
-Modified and ported to AzerothCore by Voicot 2021
Implemented new features.

Base Script Author: Lightnig Blade(AC-WEB), Voidheart(Server Owner)

