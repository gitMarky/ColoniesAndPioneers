#include Library_Map


// Called be the engine: draw the complete map here.
protected func InitializeMap(proplist map)
{
	var map_zoom = 10;
	
	var hex_max = 20;

	var y_max = HEX_MAP_HEX_HEIGHT * hex_max;
	var x_max = HEX_MAP_HEX_RADIUS * hex_max;

	var map_width = x_max / map_zoom;
	var map_height = y_max / map_zoom;

	map->Resize(map_width, map_height);

	// Return true to tell the engine a map has been successfully created.
	return true;
}
