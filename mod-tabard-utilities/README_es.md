#Mod Tabard Utilities

##Descripción:
Permite a los jugadores obtenere reputación, oro o ciertos items con solo equipar un tabardo en especifico al matar creaturas dentro o fuera de las dungeons.


## Instalación
```
1. Ubique el modulo en la carpeta `modules` de la fuente de AzerothCore. 
1. Importe el SQL manualmente en la base de datos correspondiente (characters en este caso).
1. Vuelva a ejecutar Cmake y haga una nueva build de AzerothCore.
```

## Edite la tabla SQL (tabard_utilities)

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


**Descripción de los campos**

### TEntry
El entry del tabardo, obtenido de item_template (Un tabardo solo puede ser usado para un propósito a la vez)

### Function
Para qué se va a usar el tabardo:
0 = Reputación
1 = Obtener Oro
2 = Obtener Items

### Requirements
Las condiciones necesarias para que el tabardo funcione.

0 = Sin requisitos
1 = Requiere una facción enemiga para la creatura
2 = Requiere un area de AreaTable.dbc.
3 = Requiere una creatura especifica (entry).
4 = Requiere tanto area como facción enemiga.

### ZoneID
Area especifica de AreaTable.dbc en donde debe estar la creatura.
Se usa cuando Requirements es 2 o 4.

### EnemyFactionID
La facción que la creatura debe tener.
Se usa cuando Requirements es 1 or 4.

### FactionID
La facción de la que se obtendrán puntos de reputación si Function es 0

### Value
La cantidad de reputación que se añadirá si Function es 0
La cantidad de ORO que se obtendrá si Function es 1
El *ENTRY* del item que se obtendrá si Function es 2

### Count
Esta columna funciona en conjunto con la columna Value y solo si Function es 2, es la cantidad de items que se añadirá.
No puede ser un valor negativo. 
No puede ser 0

### Comment
Esta columna no afecta en nada, está hecha para agregar comentarios sobre lo que hace el tabardo. 

*Nota: Hay algunos ejemplos en la tabla SQL por defecto*
*7725 - Tabard of the Scarlet Crusade DEPRECATED*
*23709 - Tabard of Frost*
*35279 - Tabard of Summer Skies*
*Funciona con tabardos Blizzlike, pero se sugiere crear tabardos custom*

## Creditos
-Moficiado y adaptado para AzerothCore por Voicot 2021
Se implementaron nuevas funcionalidades.

Autor del script base: Lightnig Blade(AC-WEB), Voidheart(Server Owner)

