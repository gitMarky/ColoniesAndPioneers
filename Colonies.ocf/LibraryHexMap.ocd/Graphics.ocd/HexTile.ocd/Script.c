
/**
 Gets the width factor for draw transformation.

 @return int The factor for this tile for use with SetObjDrawTransform();
 */
func GetTileWidth()
{
	return GetTileFactor(1000).X;
}

/**
 Gets the height factor for draw transformation.

 @return int The factor for this tile for use with SetObjDrawTransform();
 */
func GetTileHeight()
{
	return GetTileFactor(1000).Y;
}


func GetTileFactor(int precision)
{
	var nodes = [[0, -50], [42, -24], [42, 24], [0, 50], [-42, 24], [-42, -24]];
	
	var factor_x = 0;
	var factor_y = 0;
	
	for (var index = 0; index < 6; ++index)
	{
		var hex_node = GetNodeCoordinates(index);
		var node = nodes[index];
	
		var sign = Sign(node[0]);
		
		if (sign == 0) sign = 1;
		
		var node_offset = {X = 50 * sign, Y = 0};
		var hex_offset = {X = (HexMap_HexRadius() - 1) * sign, Y = 0};
	
		var factor = GetNodeFactor(node, node_offset, hex_node, hex_offset, precision);

		if (!factor_y || factor.Y > factor_y)
		{
			factor_y = factor.Y;
		}

		if (!factor_x || factor.X > factor_x)
		{
			factor_x = factor.X;
		}
	}
	
	return {X = factor_x, Y = factor_y};
}


func GetNodeFactor(array node, proplist node_offset, hex_node, proplist hex_offset, int precision)
{
	return {X = (hex_node.X + hex_offset.X) * precision / (node[0] + node_offset.X),
	        Y = (hex_node.Y + hex_offset.Y) * precision / (node[1] + node_offset.Y)};
}


func GetNodeCoordinates(int index)
{
	index += 6;
	index -= Map()->GetCoordinateOrientation();
	var node = GetNodesAdjacentToHex(0, 0)[index % 6];

	var x = Map()->GetXFromNodeCoordinates(node.X, node.Y) - Map()->GetXFromHexCoordinates(0, 0);
	var y = Map()->GetYFromNodeCoordinates(node.X, node.Y) - Map()->GetYFromHexCoordinates(0, 0);
	
	return {X = x, Y = y};
}


/**
 Draws a graphics layer of the tile in the correct size.
 
 @par graphics_name The graphics name.
 @par graphcis_definition The definition to take the graphics from.
 @par layer The overlay id. Defaults to 1.
 */
func DrawLayer(string graphics_name, id graphics_definition, int layer)
{
	layer = layer ?? 1;

	SetGraphics(graphics_name, graphics_definition ?? GetID(), layer, GFXOV_MODE_Base);
	SetObjDrawTransform(this->GetTileWidth(), 0, 0, 0, this->GetTileHeight(), 0, layer);
}
