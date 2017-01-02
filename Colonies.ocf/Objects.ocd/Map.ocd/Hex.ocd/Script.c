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


/** The number chip that was added on top of a hex. */
local number_chip;


/**
 Adds a number chip to the hex.
 
 @par number The number. Usually this should be a number from 2 to 12,
             depending on the rules of your scenario.
             Setting the number to {@c nil} or to a number that cannot be
             achieved by the resource dice will turn the tile unproductive.

 @return object The hex itself, so that further functions can be called on it.
 */
func AddNumberChip(int number)
{
	this.number_chip = number;
	return this;
}


/**
 Gets the number chip that is on this hex.
 
 @return int The number. A number of {@c nil} indicates that this hex
             is not productive.
 */
func GetNumberChip()
{
	return this.number_chip;
}
