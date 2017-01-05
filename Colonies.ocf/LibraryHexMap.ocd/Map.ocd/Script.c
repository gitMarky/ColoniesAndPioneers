/**
  Representation of the map.
*/

static const MAP_INDEX_OFFSET = 1;

local hexes; // vector that contains the hexes, each hex is a an object of type GameMap_Hex
local edges; // vector that contains the edges, each edge is a proplist
local nodes; // vector that contains the nodes, each node is a proplist

local coordinates; // proplist, defines the coordinate system layout.

func Initialize()
{
	hexes = [];
	edges = [];
	nodes = [];

	coordinates = {
		orientation = MAP_HEX_NORTH_EAST,
	};
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
	return GetXFromHexCoordinatesDefault(x, y, GetCoordinateOrientation() * HEX_MAP_ORIENTATION_STEP);
}


/**
 Converts hex coordinates to a global y coordinate.
 
 @par x The x component in hex coordinates.
 @par y The y component in hex coordinates.
 
 @return int The y component in global coordinates.
 */
func GetYFromHexCoordinates(int x, int y)
{
	return GetYFromHexCoordinatesDefault(x, y, GetCoordinateOrientation() * HEX_MAP_ORIENTATION_STEP);
}


/**
 Converts node coordinates to a global x coordinate.
 
 @par x The x component in node coordinates.
 @par y The y component in node coordinates.
 
 @return int The x component in global coordinates.
 */
func GetXFromNodeCoordinates(int x, int y)
{
	return GetXFromNodeCoordinatesDefault(x, y, GetCoordinateOrientation() * HEX_MAP_ORIENTATION_STEP, GetCoordinateOrientation());
}


/**
 Converts node coordinates to a global y coordinate.
 
 @par x The x component in node coordinates.
 @par y The y component in node coordinates.
 
 @return int The y component in global coordinates.
 */
func GetYFromNodeCoordinates(int x, int y)
{
	return GetYFromNodeCoordinatesDefault(x, y, GetCoordinateOrientation() * HEX_MAP_ORIENTATION_STEP, GetCoordinateOrientation());
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
