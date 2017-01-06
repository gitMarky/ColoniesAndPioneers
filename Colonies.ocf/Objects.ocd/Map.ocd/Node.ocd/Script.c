/**
 Expansion of the node data object.
 */

#include GameMap_HexNode


local structure; // a structure that is built on this hex.


/**
 The ID for the game nodes. Overload this f you want to create different tiles.
 
 @return id The ID for the game hexes.
 */
global func GameMap_HexNodeID()
{
	return GameMap_HexNodeExtended;
}


/**
 Gets any structure that is built on this node.
 
 @return object The structure.
 */
func GetStructure()
{
	return this.structure;
}


/**
 Adds a structure to the node.
 
 @par type The type of the structure.
 @par for_player The owner of the structure.
 
 @return object The node itself, so that it can be further modified. 
 */
func AddStructure(id type, int for_player)
{
	if (type)
	{
		DestroyStructure(); // Safety
		
		this.structure = CreateObject(type, 0, 0, for_player);
		this->DrawElement();
	}
	return this;
}


/**
 Removes a structure from the node.
 
 @return object The node itself, so that it can be further modified. 
 */
func DestroyStructure()
{
	if (GetStructure())
	{
		GetStructure()->RemoveObject();
	}
	return this;
}


/**
 Decides how to draw the node. Overload this function if you want to draw it differently.
 */
func DrawElement()
{
	_inherited(...); // does nothing special at the moment

	if (GetStructure())
	{
		GetStructure()->SetPosition(Map()->GetXFromNodeCoordinates(this.X, this.Y),
		                         	Map()->GetYFromNodeCoordinates(this.X, this.Y));
	}
}
