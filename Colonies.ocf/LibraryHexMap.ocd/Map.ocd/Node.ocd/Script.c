/**
  Representation of a hex in the map.
  
  This is a data structure, the graphical representation happens via another object.
*/

#include GameMap_Element


/**
 Creates a node with the given coordinates.
 
 @par x The x component in the node coordinate system.
 @par y The y component in the node coordinate system.
 
 @return proplist A proplist describing the node.
 */
global func CreateNode(int x, int y)
{
	var node = CreateObject(GameMap_HexNodeID(), 0, 0, NO_OWNER);
	node.X = x;
	node.Y = y;
	return node;
}


/**
 The ID for the game nodes. Overload this f you want to create different nodes.
 
 @return id The ID for the game nodes.
 */
global func GameMap_HexNodeID()
{
	return GameMap_HexNode;
}

