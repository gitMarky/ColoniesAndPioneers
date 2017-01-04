/**
 Functions for drawing the hex map in a OC scenario.

 @author Marky
 */

static const HEX_MAP_ALPHA = 30; // degrees

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
 
 @return int The x component in global coordinates.
 */
global func GetXFromHexCoordinates(int x, int y)
{
	return Sin(HEX_MAP_ALPHA, HexMap_HexHeight()) * (y + x) + GetXOffsetMap();
}


/**
 Converts hex coordinates to a global y coordinate.
 
 @par x The x component in hex coordinates.
 @par y The y component in hex coordinates.
 
 @return int The y component in global coordinates.
 */
global func GetYFromHexCoordinates(int x, int y)
{
	return Cos(HEX_MAP_ALPHA, HexMap_HexHeight()) * (y - x) + GetYOffsetMap();
}


/**
 Converts node coordinates to a global x coordinate.
 
 @par x The x component in hex coordinates.
 @par y The y component in hex coordinates.
 
 @return int The x component in global coordinates.
 */
global func GetXFromNodeCoordinates(int x, int y)
{
	var mod = GetNodeCoordinateModifiers(x, y);
	return GetXFromHexCoordinates(mod.X, mod.Y);
}


/**
 Converts node coordinates to a global y coordinate.
 
 @par x The x component in hex coordinates.
 @par y The y component in hex coordinates.
 
 @return int The y component in global coordinates.
 */
global func GetYFromNodeCoordinates(int x, int y)
{
	var mod = GetNodeCoordinateModifiers(x, y);
	return GetYFromHexCoordinates(mod.X, mod.Y) + mod.Sign * HexMap_HexRadius();
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
global func GetNodeCoordinateModifiers(int x, int y)
{
	var x_even = IsEven(x);
	var y_even = IsEven(y);
	var sign;
	var y_mod;
	var x_mod;
	
	if (!x_even && y_even)
	{
		sign = -1;
		x_mod = -1;
		y_mod = +0;
	}
	else if (x_even && !y_even)
	{
		sign = +1;
		x_mod = +0;
		y_mod = -1;
	}
	else
	{
		FatalError(Format("Invalid node coordinates: %d, %d - the coordinate pair must be even/odd, or odd/even, but it is even/even or odd/odd", x, y));
	}
	
	return { X = x + x_mod, Y = y + y_mod, Sign = sign};
}
