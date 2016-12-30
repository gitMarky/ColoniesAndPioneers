/**
 Functions for drawing the hex map in a OC scenario.

 @author Marky
 */

static const HEX_MAP_ALPHA = 30; // degrees
static const HEX_MAP_HEX_HEIGHT = 100; // pixels


/**
 Converts hex coordinates to a global x coordinate.
 
 @par x The x component in hex coordinates.
 @par y The y component in hex coordinates.
 @return int The x component in global coordinates.
 */
global func GetXFromHexCoordinates(int x, int y)
{
	return Sin(HEX_MAP_ALPHA, HEX_MAP_HEX_HEIGHT) * (x + y);
}


/**
 Converts hex coordinates to a global y coordinate.
 
 @par x The x component in hex coordinates.
 @par y The y component in hex coordinates.
 @return int The y component in global coordinates.
 */
global func GetYFromHexCoordinates(int x, int y)
{
	return Cos(HEX_MAP_ALPHA, HEX_MAP_HEX_HEIGHT) * (x - y);
}
