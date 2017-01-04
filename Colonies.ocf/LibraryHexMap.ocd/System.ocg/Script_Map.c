/**
 Hex map coordinates and helper functions.

 @author Marky
 */

// Constants for hex tiles and edges
static const MAP_HEX_NORTH_EAST = 0;
static const MAP_HEX_EAST = 1;
static const MAP_HEX_SOUTH_EAST = 2;
static const MAP_HEX_SOUTH_WEST = 3;
static const MAP_HEX_WEST = 4;
static const MAP_HEX_NORTH_WEST = 5;

// Constants for hex nodes
static const MAP_NODE_NORTH = 0;
static const MAP_NODE_NORTH_EAST = 1;
static const MAP_NODE_SOUTH_EAST = 2;
static const MAP_NODE_SOUTH = 3;
static const MAP_NODE_SOUTH_WEST = 4;
static const MAP_NODE_NORTH_WEST = 5;

// Hexes and their surroundings

/** Coordinate modifiers for adjacent hexes of a hex. */
static const MAP_HEX_ADJACENT_HEX_COORDINATES = [{X = +0, Y = +2},
                                                 {X = +2, Y = +2},
                                                 {X = +2, Y = +0},
                                                 {X = +0, Y = -2},
                                                 {X = -2, Y = -2},
                                                 {X = -2, Y = +0}];

/** Coordinate modifiers for nodes of a hex. */
static const MAP_HEX_ADJACENT_NODE_COORDINATES = [{X = +0, Y = +1},
                                                  {X = +1, Y = +2},
                                                  {X = +2, Y = +1},
                                                  {X = +1, Y = +0},
                                                  {X = +0, Y = -1},
                                                  {X = -1, Y = +0}];

/** Coordinate modifiers for edges of a hex. */
static const MAP_HEX_ADJACENT_EDGE_COORDINATES = [{X = +0, Y = +1},
                                                  {X = +1, Y = +1},
                                                  {X = +1, Y = +0},
                                                  {X = +0, Y = -1},
                                                  {X = -1, Y = -1},
                                                  {X = -1, Y = +0}];

// Nodes and their surroundings

/** Coordinate modifiers for adjacent hexes of a node, where the x coordinate is even and the y coordinate is odd. */
static const MAP_NODE_EVEN_ODD_ADJACENT_HEX_COORDINATES = [{X = -1, Y = +0},
                                                           {X = +1, Y = +0},
                                                           {X = -1, Y = -1}];

/** Coordinate modifiers for adjacent nodes of a node, where the x coordinate is even and the y coordinate is odd. */
static const MAP_NODE_EVEN_ODD_ADJACENT_NODE_COORDINATES = [{X = -1, Y = -1},
                                                            {X = +1, Y = +1},
                                                            {X = +1, Y = -1}];

/** Coordinate modifiers for adjacent edges of a node, where the x coordinate is even and the y coordinate is odd. */
static const MAP_NODE_EVEN_ODD_ADJACENT_EDGE_COORDINATES = [{X = -1, Y = -1},
                                                            {X = +0, Y = +0},
                                                            {X = +0, Y = -1}];

/** Coordinate modifiers for adjacent hexes of a node, where the x coordinate is odd and the y coordinate is even. */
static const MAP_NODE_ODD_EVEN_ADJACENT_HEX_COORDINATES = [{X = -2, Y = -1},
                                                           {X = +0, Y = +1},
                                                           {X = +0, Y = -1}];

/** Coordinate modifiers for adjacent nodes of a node, where the x coordinate is odd and the y coordinate is even. */
static const MAP_NODE_ODD_EVEN_ADJACENT_NODE_COORDINATES = [{X = -1, Y = +1},
                                                            {X = +1, Y = +1},
                                                            {X = -1, Y = -1}];

/** Coordinate modifiers for adjacent edges of a node, where the x coordinate is odd and the y coordinate is even. */
static const MAP_NODE_ODD_EVEN_ADJACENT_EDGE_COORDINATES = [{X = -1, Y = +0},
                                                            {X = +0, Y = +0},
                                                            {X = -1, Y = -1}];

// Edges and their surroundings

/** Coordinate modifiers for adjacent hexes of an edge, where the x coordinate is even and the y coordinate is odd. */
static const MAP_EDGE_EVEN_ODD_ADJACENT_HEX_COORDINATES = [{X = -1, Y = +0},
                                                           {X = +1, Y = +0}];

/** Coordinate modifiers for adjacent nodes of an edge, where the x coordinate is even and the y coordinate is odd. */
static const MAP_EDGE_EVEN_ODD_ADJACENT_NODE_COORDINATES = [{X = +0, Y = +0},
                                                            {X = +1, Y = +1}];

/** Coordinate modifiers for adjacent edges of an edge, where the x coordinate is even and the y coordinate is odd. */
static const MAP_EDGE_EVEN_ODD_ADJACENT_EDGE_COORDINATES = [{X = -1, Y = -1},
                                                            {X = +0, Y = -1},
                                                            {X = +0, Y = +1},
                                                            {X = +1, Y = +1}];

/** Coordinate modifiers for adjacent hexes of an edge, where the x coordinate is odd and the y coordinate is even. */
static const MAP_EDGE_ODD_EVEN_ADJACENT_HEX_COORDINATES = [{X = +0, Y = -1},
                                                           {X = +0, Y = +1}];

/** Coordinate modifiers for adjacent nodes of an edge, where the x coordinate is odd and the y coordinate is even. */
static const MAP_EDGE_ODD_EVEN_ADJACENT_NODE_COORDINATES = [{X = +0, Y = +0},
                                                            {X = +1, Y = +1}];

/** Coordinate modifiers for adjacent edges of an edge, where the x coordinate is odd and the y coordinate is even. */
static const MAP_EDGE_ODD_EVEN_ADJACENT_EDGE_COORDINATES = [{X = -1, Y = -1},
                                                            {X = -1, Y = +0},
                                                            {X = +1, Y = +1},
                                                            {X = +1, Y = +0}];

/** Coordinate modifiers for adjacent hexes of an edge, where the x coordinate is even and the y coordinate is even. */
static const MAP_EDGE_EVEN_EVEN_ADJACENT_HEX_COORDINATES = [{X = -1, Y = -1}, 
                                                            {X = +1, Y = +1}];

/** Coordinate modifiers for adjacent nodes of an edge, where the x coordinate is even and the y coordinate is even. */
static const MAP_EDGE_EVEN_EVEN_ADJACENT_NODE_COORDINATES = [{X = +0, Y = +1},
                                                             {X = +1, Y = +0}];

/** Coordinate modifiers for adjacent edges of an edge, where the x coordinate is even and the y coordinate is even. */
static const MAP_EDGE_EVEN_EVEN_ADJACENT_EDGE_COORDINATES = [{X = -1, Y = +0},
                                                             {X = +0, Y = +1},
                                                             {X = +1, Y = +0},
                                                             {X = +0, Y = -1}];

// functions

/**
 Tells if a number is even.
 
 @par number the number.
 @return {@c true}, if the number is even.
 */
global func IsEven(int number)
{
	return (number % 2) == 0;
}


/**
 Creates an edge with the given coordinates.
 
 @par x The x component in the edge coordinate system.
 @par y The y component in the edge coordinate system.
 
 @return proplist A proplist describing the edge.
 */
global func CreateEdge(int x, int y)
{
	return {
		isEdge = true,
		X = x,
		Y = y,
	};
}


/**
 Creates a node with the given coordinates.
 
 @par x The x component in the node coordinate system.
 @par y The y component in the node coordinate system.
 
 @return proplist A proplist describing the node.
 */
global func CreateNode(int x, int y)
{
	return {
		isNode = true,
		X = x,
		Y = y,
	};
}


/**
 Gets a coordinate array in global coordinates.
 
 @par x The global x component in the coordinate system.
 @par y The global y component in the coordinate system.
 @par modifiers An array of modifiers that contains coordinates
                that are relative to {@c x} and {@c y}.

 @return An array of proplists where {@c x} and {@c y} where added to each component
         in the {@c modifiers} array.
 */
global func GetCoordinateArray(int x, int y, array modifiers)
{
	var coordinates = [];
	for (var i = 0; i < GetLength(modifiers); ++i)
	{
		coordinates[i] = {X = modifiers[i].X + x, Y = modifiers[i].Y + y};
	}
	return coordinates;
}


/**
 Gets a coordinate array in global coordinates,
 with plausibility checks for nodes.
 
 @par x The global x component in the coordinate system.
 @par y The global y component in the coordinate system.
 @par x_even_y_odd An array of modifiers that contains coordinates
                that are relative to {@c x} and {@c y}.
                Is chosen of x is even and y is odd.
 @par x_odd_y_even An array of modifiers that contains coordinates
                that are relative to {@c x} and {@c y}.
                Is chosen of x is odd and y is even. 

 @return An array where {@c x} and {@c y} where added to each component
         in the {@c modifiers} array.
 */
global func GetNodeCoordinateArray(int x, int y, array x_even_y_odd, array x_odd_y_even)
{
	var is_x_even = IsEven(x);
	var is_y_even = IsEven(y);
	
	if  (is_x_even && !is_y_even)
	{
		return GetCoordinateArray(x, y, x_even_y_odd);
	}
	else if (!is_x_even && is_y_even)
	{
		return GetCoordinateArray(x, y, x_odd_y_even);
	}
	else
	{
		FatalError(Format("Invalid node coordinates: %d, %d - the coordinate pair must be even/odd, or odd/even, but it is even/even or odd/odd", x, y));
	}
}


/**
 Gets a coordinate array in global coordinates,
 with plausibility checks for edges.
 
 @par x The global x component in the coordinate system.
 @par y The global y component in the coordinate system.
 @par x_even_y_odd An array of modifiers that contains coordinates
                that are relative to {@c x} and {@c y}.
                Is chosen of x is even and y is odd.
 @par x_odd_y_even An array of modifiers that contains coordinates
                that are relative to {@c x} and {@c y}.
                Is chosen of x is odd and y is even. 
 @par x_even_y_even An array of modifiers that contains coordinates
                that are relative to {@c x} and {@c y}.
                Is chosen of x is even and y is even. 

 @return An array where {@c x} and {@c y} where added to each component
         in the {@c modifiers} array.
 */
global func GetEdgeCoordinateArray(int x, int y, array x_even_y_odd, array x_odd_y_even, array x_even_y_even)
{
	var is_x_even = IsEven(x);
	var is_y_even = IsEven(y);
	
	if  (is_x_even && !is_y_even)
	{
		return GetCoordinateArray(x, y, x_even_y_odd);
	}
	else if (!is_x_even && is_y_even)
	{
		return GetCoordinateArray(x, y, x_odd_y_even);
	}
	else if (is_x_even && is_y_even)
	{
		return GetCoordinateArray(x, y, x_even_y_even);
	}
	else
	{
		FatalError(Format("Invalid edge coordinates: %d, %d - the coordinate pair must not be odd/odd", x, y));
	}
}


/**
 Gets the hex coordinates that are adjacent to a hex.
 
 @par x The x component in the hex coordinate system.
 @par y The y component in the hex coordinate system.

 @return array The coordinates of adjacent hexes.
 */
global func GetHexesAdjacentToHex(int x, int y)
{
	return GetCoordinateArray(x, y, MAP_HEX_ADJACENT_HEX_COORDINATES);
}


/**
 Gets the node coordinates that are adjacent to a hex.
 
 @par x The x component in the hex coordinate system.
 @par y The y component in the hex coordinate system.

 @return array The coordinates of adjacent nodes.
 */
global func GetNodesAdjacentToHex(int x, int y)
{
	return GetCoordinateArray(x, y, MAP_HEX_ADJACENT_NODE_COORDINATES);
}


/**
 Gets the edge coordinates that are adjacent to a hex.
 
 @par x The x component in the hex coordinate system.
 @par y The y component in the hex coordinate system.

 @return array The coordinates of adjacent edges.
 */
global func GetEdgesAdjacentToHex(int x, int y)
{
	return GetCoordinateArray(x, y, MAP_HEX_ADJACENT_EDGE_COORDINATES);
}


/**
 Gets the hex coordinates that are adjacent to a node.
 
 @par x The x component in the node coordinate system.
 @par y The y component in the node coordinate system.

 @return array The coordinates of adjacent hexes.
 */
global func GetHexesAdjacentToNode(int x, int y)
{
	return GetNodeCoordinateArray(x, y, MAP_NODE_EVEN_ODD_ADJACENT_HEX_COORDINATES,
	                                    MAP_NODE_ODD_EVEN_ADJACENT_HEX_COORDINATES);
}


/**
 Gets the node coordinates that are adjacent to a node.
 
 @par x The x component in the node coordinate system.
 @par y The y component in the node coordinate system.

 @return array The coordinates of adjacent nodes.
 */
global func GetNodesAdjacentToNode(int x, int y)
{
	return GetNodeCoordinateArray(x, y, MAP_NODE_EVEN_ODD_ADJACENT_NODE_COORDINATES,
	                                    MAP_NODE_ODD_EVEN_ADJACENT_NODE_COORDINATES);
}


/**
 Gets the edge coordinates that are adjacent to a node.
 
 @par x The x component in the node coordinate system.
 @par y The y component in the node coordinate system.

 @return array The coordinates of adjacent edges.
 */
global func GetEdgesAdjacentToNode(int x, int y)
{
	return GetNodeCoordinateArray(x, y, MAP_NODE_EVEN_ODD_ADJACENT_EDGE_COORDINATES,
	                                    MAP_NODE_ODD_EVEN_ADJACENT_EDGE_COORDINATES);
}


/**
 Gets the hex coordinates that are adjacent to an edge.
 
 @par x The x component in the edge coordinate system.
 @par y The y component in the edge coordinate system.

 @return array The coordinates of adjacent hexes.
 */
global func GetHexesAdjacentToEdge(int x, int y)
{
	return GetEdgeCoordinateArray(x, y, MAP_EDGE_EVEN_ODD_ADJACENT_HEX_COORDINATES, 
	                                    MAP_EDGE_ODD_EVEN_ADJACENT_HEX_COORDINATES,
	                                    MAP_EDGE_EVEN_EVEN_ADJACENT_HEX_COORDINATES);
}


/**
 Gets the node coordinates that are adjacent to an edge.
 
 @par x The x component in the edge coordinate system.
 @par y The y component in the edge coordinate system.

 @return array The coordinates of adjacent nodes.
 */
global func GetNodesAdjacentToEdge(int x, int y)
{
	return GetEdgeCoordinateArray(x, y, MAP_EDGE_EVEN_ODD_ADJACENT_NODE_COORDINATES,
	                                    MAP_EDGE_ODD_EVEN_ADJACENT_NODE_COORDINATES,
	                                    MAP_EDGE_EVEN_EVEN_ADJACENT_NODE_COORDINATES);
}


/**
 Gets the edge coordinates that are adjacent to an edge.
 
 @par x The x component in the edge coordinate system.
 @par y The y component in the edge coordinate system.

 @return array The coordinates of adjacent edges.
 */
global func GetEdgesAdjacentToEdge(int x, int y)
{
	return GetEdgeCoordinateArray(x, y, MAP_EDGE_EVEN_ODD_ADJACENT_EDGE_COORDINATES,
	                                    MAP_EDGE_ODD_EVEN_ADJACENT_EDGE_COORDINATES,
	                                    MAP_EDGE_EVEN_EVEN_ADJACENT_EDGE_COORDINATES);
}
