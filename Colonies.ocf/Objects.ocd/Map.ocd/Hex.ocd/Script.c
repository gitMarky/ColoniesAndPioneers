/**
  Representation of a hex in the map.
*/

#include GameMap_Element

/**
 Creates a hex with the given coordinates.
 
 @par x The x component in the hex coordinate system.
 @par y The y component in the hex coordinate system.
 
 @return proplist A proplist describing the hex.
 */
global func CreateHex(int x, int y)
{
	var hex = CreateObject(GameMap_Hex, 0, 0, NO_OWNER);
	hex.X = x;
	hex.Y = y;
	return hex;
}

