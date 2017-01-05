#include Library_Map


// Called be the engine: draw the complete map here.
protected func InitializeMap(proplist map)
{
	var map_zoom = 1;
	
	//var hex_max = 20;

	//var y_max = HexMap_HexHeight() * hex_max;
	//var x_max = HexMap_HexRadius() * hex_max;

	//var map_width = x_max / map_zoom;
	//var map_height = y_max / map_zoom;

	var corners = GameMap->GetCornersHexagonal(6, 6);
	var dimensions = GameMap->CalculateDimensions(corners);

	map->Resize(dimensions.wdt / map_zoom, dimensions.hgt / map_zoom);

	// Return true to tell the engine a map has been successfully created.
	return true;
}
