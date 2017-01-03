/**
  Representation of the map.
*/

local hexes; // vector that contains the hexes, each hex is a an object of type GameMap_Hex
local edges; // vector that contains the edges, each edge is a proplist
local nodes; // vector that contains the nodes, each node is a proplist

func Initialize()
{
	hexes = [];
	edges = [];
	nodes = [];
}


/**
 Gets the hex in the given coordinates.
 
 @par x The x component in hex coordinates.
 @par y The y component in hex coordinates.
 
 @return proplist A hex, as created by {@link Global#CreateHex}.
                  Returns {@c nil} if the hex was not added before.
                  Add the hex via {@link GameMap#AddHex}.
 */
func GetHex(int x, int y)
{
	EnsureCoordinates(x, y, hexes);	
	
	return hexes[x][y];
}


/**
 Adds a hex in the given coordinates.

 @par x The x component in hex coordinates.
 @par y The y component in hex coordinates. 
 
 @return object The hex that was added.
 */
func AddHex(int x, int y)
{
	EnsureCoordinates(x, y);
	
	if (!GetHex(x, y))
	{
		hexes[x][y] = CreateHex(x, y);
	}
	
	return GetHex(x, y);
}


/**
 Returns a representation of the hex map.
 
 @return object The hex map. You can use functions on this object
                in order to manipulate the map, for example
                {@link GameMap#AddHex}.
 */
global func Map()
{
	var map = FindObject(Find_ID(GameMap));
	
	if (!map)
	{
		map = CreateObject(GameMap, 0, 0, NO_OWNER);
	}
	
	return map;
}


/**
 Ensures that the coordinates in a vector array can be filled, without
 causing script errors.
 */
func EnsureCoordinates(int x, int y, array list)
{
	if ((GetType(list) == C4V_Array) && (GetType(list[x]) != C4V_Array))
	{
		list[x] = [];
	}
}
