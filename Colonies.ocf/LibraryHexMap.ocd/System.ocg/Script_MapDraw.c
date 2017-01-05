/**
 Functions for drawing the hex map in an OC scenario.
 
 The coordinate functions are defined here, but the actual functions are defined in the map.

 @author Marky
 */

static const HEX_MAP_ALPHA = 30; // degrees
static const HEX_MAP_ORIENTATION_STEP = 60; // degrees

global func HexMap_HexRadius()
{
	return 50; // pixels
}

global func HexMap_HexHeight()
{
	return 866 * HexMap_HexRadius() / 1000; // sqrt(3)*r/2 pixels;
}


/**
 The x offset of the hex map, in pixels.
 
 @return int The offset, in pixels.
 */
global func GetXOffsetMap()
{
	return 0;
}


/**
 The y offset of the hex map, in pixels.
 
 @return int The offset, in pixels.
 */
global func GetYOffsetMap()
{
	return LandscapeHeight() / 2;
}


/**
 Converts hex coordinates to a global x coordinate.
 
 @par x The x component in hex coordinates.
 @par y The y component in hex coordinates.
 @par delta Additional rotation of the coordinate system,
            usually in increments of 60°. Add 30° if the
            the hex should be with the flat side at the top.
 
 @return int The x component in global coordinates.
 */
global func GetXFromHexCoordinatesDefault(int x, int y, int delta)
{
	return Sin(HEX_MAP_ALPHA + delta, HexMap_HexHeight()) * x
	     + Sin(HEX_MAP_ALPHA - delta, HexMap_HexHeight()) * y;
}


/**
 Converts hex coordinates to a global y coordinate.
 
 @par x The x component in hex coordinates.
 @par y The y component in hex coordinates.
 @par delta Additional rotation of the coordinate system,
            usually in increments of 60°. Add 30° if the
            the hex should be with the flat side at the top.
 
 @return int The y component in global coordinates.
 */
global func GetYFromHexCoordinatesDefault(int x, int y, int delta)
{
	return -Cos(HEX_MAP_ALPHA + delta, HexMap_HexHeight()) * x
	      + Cos(HEX_MAP_ALPHA - delta, HexMap_HexHeight()) * y;
}


/**
 Converts node coordinates to a global x coordinate.
 
 @par x The x component in node coordinates.
 @par y The y component in node coordinates.
 @par delta Additional rotation of the coordinate system,
            usually in increments of 60°. Add 30° if the
            the hex should be with the flat side at the top.
 
 @return int The x component in global coordinates.
 */
global func GetXFromNodeCoordinatesDefault(int x, int y, int delta, int orientation)
{
	var mod = GetNodeCoordinateModifiers(x, y, orientation);
	return GetXFromHexCoordinatesDefault(mod.X, mod.Y, delta);
}


/**
 Converts node coordinates to a global y coordinate.
 
 @par x The x component in node coordinates.
 @par y The y component in node coordinates.
 @par delta Additional rotation of the coordinate system,
            usually in increments of 60°. Add 30° if the
            the hex should be with the flat side at the top.
 
 @return int The y component in global coordinates.
 */
global func GetYFromNodeCoordinatesDefault(int x, int y, int delta, int orientation)
{
	var mod = GetNodeCoordinateModifiers(x, y, orientation);
	return GetYFromHexCoordinatesDefault(mod.X, mod.Y, delta) + mod.Sign * HexMap_HexRadius();
}


/**
 Gets coordinate modifiers for the position of node coordinates
 relative to hex coordinates.
 
 @par x The x component in hex coordinates.
 @par y The y component in hex coordinates.
 
 @return proplist A data structure with the entries:
         X - the hex x coordinates.
         Y - the hex y coordinates.
         Sign - this is a modifier that can be used for calculations.
                Its main use is determining whether to add or subtract
                the radius of a hex to the y component.
 */
global func GetNodeCoordinateModifiers(int x, int y, int orientation)
{
	var x_even = IsEven(x);
	var y_even = IsEven(y);
	var sign;
	var y_mod;
	var x_mod;
	
	if (!x_even && y_even)
	{
		 sign = [-1, +1, -1, +1, -1, +1];
		x_mod = [-1, -1, +1, -1, -1, +1];
		y_mod = [+0, -2, +0, +0, -2, +0];
	}
	else if (x_even && !y_even)
	{
		 sign = [+1, -1, +1, -1, +1, -1];
		x_mod = [+0, +0, -2, +0, +0, -2];
		y_mod = [-1, +1, -1, -1, +1, -1];
	}
	else
	{
		FatalError(Format("Invalid node coordinates: %d, %d - the coordinate pair must be even/odd, or odd/even, but it is even/even or odd/odd", x, y));
	}
	
	return { X = x + x_mod[orientation], Y = y + y_mod[orientation], Sign = sign[orientation]};
}
