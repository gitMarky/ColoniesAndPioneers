/**
  Representation of the map.
*/

static const MAP_INDEX_OFFSET = 1;

local hexes; // vector that contains the hexes, each hex is a an object of type GameMap_Hex
local edges; // vector that contains the edges, each edge is a proplist
local nodes; // vector that contains the nodes, each node is a proplist

local coordinates = { // proplist, defines the coordinate system layout.
		orientation = MAP_HEX_NORTH_EAST,	// orientation of the x-axis
		max_x = nil,						// max number of hexes in x direction
		max_y = nil,						// max number of hexes in y direction
		max_set = false,					// maximum numbers were set?
		corners = [],						// coordinates of the outmost corners of the map
	};

local dimensions = { // proplist, defines the screen layout
		max_x = 0,	// max x coordinate of a hex component on screen, in pixels
		max_y = 0,	// max y coordinate of a hex component on screen, in pixels
		min_x = 0,	// min x coordinate of a hex component on screen, in pixels
		min_y = 0,	// min y coordinate of a hex component on screen, in pixels
		pos_x = 0,	// map position in x on screen, in pixels
		pos_y = 0,  // map position in y on screen, in pixels
	};

func Initialize()
{
	hexes = [];
	edges = [];
	nodes = [];

	this.coordinates = new coordinates{};
	
	this.dimensions = new dimensions{};
}


/**
 Gets the hex in the given coordinates.
 
 @par x The x component in hex coordinates.
 @par y The y component in hex coordinates.
 
 @return object A hex, as created by {@link Global#CreateHex}.
                Returns {@c nil} if the hex was not added before.
                Add the hex via {@link GameMap#AddHex}.
 */
func GetHex(int x, int y)
{
	EnsureCoordinates(x, y, hexes);	
	return GetCoordinates(x, y, hexes);
}


/**
 Gets all hexes.
 
 @return array An array of the hexes that exist.
 */
func GetHexes()
{
	return FindObjects(Find_ID(GameMap_HexID()));
}


/**
 Adds a hex in the given coordinates.

 @par x The x component in hex coordinates.
 @par y The y component in hex coordinates. 
 
 @return object The hex that was added.
 */
func AddHex(int x, int y)
{
	EnsureCoordinates(x, y, hexes);

	if (!GetHex(x, y))
	{
		SetCoordinates(x, y, hexes, CreateHex(x, y));
	}

	return GetHex(x, y);
}


/**
 Gets the edge in the given coordinates.
 
 @par x The x component in edge coordinates.
 @par y The y component in edge coordinates.
 
 @return proplist An edge, as created by {@link Global#CreateEdge}.
                  Returns {@c nil} if the edge was not added before.
                  Add the edge via {@link GameMap#AddEdge}.
 */
func GetEdge(int x, int y)
{
	EnsureCoordinates(x, y, edges);	
	return GetCoordinates(x, y, edges);
}


/**
 Adds an edge in the given coordinates.

 @par x The x component in edge coordinates.
 @par y The y component in edge coordinates. 

 @return proplist The edge that was added.
 */
func AddEdge(int x, int y)
{
	EnsureCoordinates(x, y, edges);

	if (!GetEdge(x, y))
	{
		SetCoordinates(x, y, edges, CreateEdge(x, y));
	}
	
	return GetEdge(x, y);
}


/**
 Gets the node in the given coordinates.
 
 @par x The x component in node coordinates.
 @par y The y component in node coordinates.
 
 @return proplist A node, as created by {@link Global#CreateNode}.
                  Returns {@c nil} if the node was not added before.
                  Add the edge via {@link GameMap#AddNode}.
 */
func GetNode(int x, int y)
{
	EnsureCoordinates(x, y, nodes);	
	return GetCoordinates(x, y, nodes);
}


/**
 Gets all nodes.
 
 @return array An array of the nodes that exist.
 */
func GetNodes()
{
	return FindObjects(Find_ID(GameMap_HexNodeID()));
}


/**
 Adds a node in the given coordinates.

 @par x The x component in node coordinates.
 @par y The y component in node coordinates. 

 @return proplist The node that was added.
 */
func AddNode(int x, int y)
{
	EnsureCoordinates(x, y, nodes);
	
	if (!GetNode(x, y))
	{
		SetCoordinates(x, y, nodes, CreateNode(x, y));
	}
	
	return GetNode(x, y);
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
	if ((GetType(list) == C4V_Array) && (GetType(list[x + MAP_INDEX_OFFSET]) != C4V_Array))
	{
		list[x + MAP_INDEX_OFFSET] = [];
	}
}


/**
 Ensures that the coordinates in a vector array can be filled, without
 causing script errors.
 */
func GetCoordinates(int x, int y, array list)
{
	return list[x + MAP_INDEX_OFFSET][y + MAP_INDEX_OFFSET];
}


/**
 Ensures that the coordinates in a vector array can be filled, without
 causing script errors.
 */
func SetCoordinates(int x, int y, array list, value)
{
	list[x + MAP_INDEX_OFFSET][y + MAP_INDEX_OFFSET] = value;
}


func DrawElements()
{
	for (var hex in GetHexes())
	{
		hex->DrawElement();
	}
}


/**
 Converts hex coordinates to a global x coordinate.
 
 @par x The x component in hex coordinates.
 @par y The y component in hex coordinates.
 
 @return int The x component in global coordinates.
 */
func GetXFromHexCoordinates(int x, int y)
{
	return this.dimensions.pos_x + GetXFromHexCoordinatesDefault(x, y, GetCoordinateOrientation() * HEX_MAP_ORIENTATION_STEP);
}


/**
 Converts hex coordinates to a global y coordinate.
 
 @par x The x component in hex coordinates.
 @par y The y component in hex coordinates.
 
 @return int The y component in global coordinates.
 */
func GetYFromHexCoordinates(int x, int y)
{
	return this.dimensions.pos_y + GetYFromHexCoordinatesDefault(x, y, GetCoordinateOrientation() * HEX_MAP_ORIENTATION_STEP);
}


/**
 Converts node coordinates to a global x coordinate.
 
 @par x The x component in node coordinates.
 @par y The y component in node coordinates.
 
 @return int The x component in global coordinates.
 */
func GetXFromNodeCoordinates(int x, int y)
{
	return this.dimensions.pos_x + GetXFromNodeCoordinatesDefault(x, y, GetCoordinateOrientation() * HEX_MAP_ORIENTATION_STEP, GetCoordinateOrientation());
}


/**
 Converts node coordinates to a global y coordinate.
 
 @par x The x component in node coordinates.
 @par y The y component in node coordinates.
 
 @return int The y component in global coordinates.
 */
func GetYFromNodeCoordinates(int x, int y)
{
	return this.dimensions.pos_y + GetYFromNodeCoordinatesDefault(x, y, GetCoordinateOrientation() * HEX_MAP_ORIENTATION_STEP, GetCoordinateOrientation());
}


/**
 Get the orientation of the x-axis of the hex coordinate system.
 
 @return int An integer from the constants {@c MAP_HEX_*}.
 */
func GetCoordinateOrientation()
{
	return this.coordinates.orientation;
}


/**
 Get the orientation of the x-axis of the hex coordinate system.
 
 @par orientation An integer from the constants {@c MAP_HEX_*}.
 */
func SetCoordinateOrientation(int orientation)
{
	this.coordinates.orientation = orientation % 6;
}


/**
 Get the number of hexes in the map in X direction.
 
 @return int The map will has this many hexes.
 */
func GetNumberOfHexesX()
{
	return this.coordinates.max_x;
}


/**
 Set the number of hexes in the map in X direction.
 
 @par amount The map will have this many hexes.
 */
func SetNumberOfHexesX(int amount)
{
	if (amount < 0)
	{
		FatalError(Format("Needs non-negative amount, got %d", amount));
	}
	
	this.coordinates.max_x = amount;
	this.coordinates.max_set = this.coordinates.max_x && this.coordinates.max_y;
}


/**
 Get the number of hexes in the map in Y direction.
 
 @return int The map will has this many hexes.
 */
func GetNumberOfHexesY()
{
	return this.coordinates.max_y;
}


/**
 Set the number of hexes in the map in Y direction.
 
 @par amount The map will have this many hexes.
 */
func SetNumberOfHexesY(int amount)
{
	if (amount < 0)
	{
		FatalError(Format("Needs non-negative amount, got %d", amount));
	}
	
	this.coordinates.max_y = amount;
	this.coordinates.max_set = this.coordinates.max_x && this.coordinates.max_y;
}


/**
 Clears the corners of the map.
 */
func ClearCorners()
{
	this.coordinates.corners = [];
}


/**
 Predefined corner setup for a rectangle.
 
 Note that the rectangle will appear as a parallelogram on screen.
 */
func SetupCornersRectangular()
{
	this.coordinates.corners = GetCornersRectangular(this.coordinates.max_x, this.coordinates.max_y);
}

/**
 Gets the corners of a rectangular map with given dimensions.
 
 @par hexes_x The number of hexes in x direction.
 @par hexes_y The number of hexes in y direction.
 */
func GetCornersRectangular(int hexes_x, int hexes_y)
{
	var x = hexes_x * 2;
	var y = hexes_y * 2;
	this.coordinates.corners = [{X = 0, Y = 0},
	                            {X = x, Y = 0},
	                            {X = 0, Y = y},
	                            {X = x, Y = y}];
}


/**
 Predefined corner setup for a rectangle hexagon.
 */
func SetupCornersHexagonal()
{
	this.coordinates.corners = GetCornersHexagonal(this.coordinates.max_x, this.coordinates.max_y);
}


/**
 Gets the corners of a hexagonal map with given dimensions.

 @par hexes_x The number of hexes in x direction.
 @par hexes_y The number of hexes in y direction.
 */
func GetCornersHexagonal(int hexes_x, int hexes_y)
{
	var x = hexes_x;
	var y = hexes_y;
	var x2 = hexes_x * 2;
	var y2 = hexes_y * 2;
	return [{X =  0, Y =  0},
	        {X =  x, Y =  0},
	        {X =  x, Y = y2},
	        {X =  0, Y =  y},
	        {X = x2, Y =  y},
	        {X = x2, Y = y2}];
}


/**
 Adds a corner to the map. Corners are relevant for determining the
 dimensions of the map.
 
 @par corner A corner. This must be a proplist {X, Y} with values.
 */
func AddCorner(proplist corner)
{
	PushBack(this.coordinates.corners, corner);
}


/**
 Calculates the map dimensions, so that they can be queried
 with {@link GameMap#GetDimensions}.
 
 @par corners An array of corners. If no parameter is passed this
              uses the internal corners of the map that were set
              up by the functions {@link GameMap#SetupCornersHexagonal},
              {@link GameMap#SetupCornersRectangular}, or
              {@link GameMap#AddCorner}.
 
 @return proplist See {@link GameMap#GetDimensions}.
 */
func CalculateDimensions(array corners)
{
	corners = corners ?? this.coordinates.corners;

	if (GetLength(corners) == 0)
	{
		FatalError("The map has no corners. Define corners with SetupCorners*() or AddCorner()");
	}
	
	var max_x = 0, max_y = 0, min_x = 0, min_y = 0;
	
	for (var corner in corners)
	{
		var corner_nodes = GetNodesAdjacentToHex(corner.X, corner.Y);
		
		for (var node in corner_nodes)
		{
			var x = GetXFromNodeCoordinates(node.X, node.Y);
			var y = GetYFromNodeCoordinates(node.X, node.Y);
			
			if (max_x == 0) max_x = x; else max_x = Max(x, max_x);
			if (min_x == 0) min_x = x; else min_x = Min(x, min_x);
			if (max_y == 0) max_y = y; else max_y = Max(y, max_y);
			if (min_y == 0) min_y = y; else min_y = Min(y, min_y);
		}
	}

	if (GetType(this) == C4V_C4Object)
	{
		this.dimensions.min_x = min_x;
		this.dimensions.max_x = max_x;
		this.dimensions.min_y = min_y;
		this.dimensions.max_y = max_y;
	
		return GetDimensions();
	}
	else
	{
		return Rectangle(min_x, min_y, max_x - min_x, max_y - min_y);
	}
}


/**
 Gets the map dimenions, in pixels.
 
 @return proplist A rectangle definition, see {@link Global#Rectangle}
 */
func GetDimensions()
{
	return Rectangle(this.dimensions.min_x,
	                 this.dimensions.min_y,
	                 this.dimensions.max_x - this.dimensions.min_x,
	                 this.dimensions.max_y - this.dimensions.min_y);
}


/**
 Sets the map onscreen position.
 
 @par x The x component in pixels on screen.
 @par y The y component in pixels on screen.
 */
func SetMapPosition(int x, int y)
{
	this.dimensions.pos_x = x - this.dimensions.min_x;
	this.dimensions.pos_y = y - this.dimensions.min_y;
}


/**
 Gets the map onscreen position.
 
 @return proplist A proplist with the components
         X The x component in pixels on screen.
         Y The y component in pixels on screen.
 */
func GetMapPosition(int x, int y)
{
	return {X = this.dimensions.pos_x + this.dimensions.min_x,
	        Y = this.dimensions.pos_y + this.dimensions.min_y};
}
