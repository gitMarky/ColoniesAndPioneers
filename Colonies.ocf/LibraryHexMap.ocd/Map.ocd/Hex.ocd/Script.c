/**
  Representation of a hex in the map.
  
  This is a data structure, the graphical representation happens via another object.
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
	var hex = CreateObject(GameMap_HexID(), 0, 0, NO_OWNER);
	hex.X = x;
	hex.Y = y;
	return hex;
}


/**
 The ID for the game hexes. Overload this f you want to create different tiles.
 
 @return id The ID for the game hexes.
 */
global func GameMap_HexID()
{
	return GameMap_Hex;
}


/**
 Gets all nodes that are adjacent to this hex.
 
 @return array An array of objects {@link Global#GameMap_HexNodeID}.
 */
func GetAdjacentNodes()
{
	var nodes = GetNodesAdjacentToHex(this.X, this.Y);
	
	var adjacent = [];
	
	for (var node in nodes)
	{
		var found = Map()->GetNode(node.X, node.Y);
		if (found)
		{
			PushBack(adjacent, found);
		}
	}
	
	return adjacent;
}

