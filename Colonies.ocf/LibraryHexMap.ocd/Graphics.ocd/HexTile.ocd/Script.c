
/**
 Gets the width factor for draw transformation.

 @return int The factor for this tile for use with SetObjDrawTransform();
 */
func GetTileWidth()
{
	return GetNodeFactor(1, 1000).X;
}

/**
 Gets the height factor for draw transformation.

 @return int The factor for this tile for use with SetObjDrawTransform();
 */
func GetTileHeight()
{
	return (GetNodeFactor(0, 1000).Y + GetNodeFactor(1, 1000).Y)/2;
}


func GetNodeFactor(int index, int precision)
{
	var nodes = [[0, -50], [42, -24], [252, 24], [0, 50], [-42, 24], [-42, -24]];
	var hex_node = GetNodeCoordinates(index);
	var node = nodes[index];
	
	var node_offset = {X = 50, Y = 0};
	var hex_offset = {X = HexMap_HexRadius() - 1, Y = 0};
	
	return {X = (hex_node.X + hex_offset.X) * precision / (node[0] + node_offset.X),
	        Y = (hex_node.Y + hex_offset.Y) * precision / (node[1] + node_offset.Y)};
}


func GetNodeCoordinates(int index)
{
	var node = GetNodesAdjacentToHex(0, 0)[index];
	
	var x = GetXFromNodeCoordinatesDefault(node.X, node.Y) - GetXFromHexCoordinatesDefault(0, 0);
	var y = GetYFromNodeCoordinatesDefault(node.X, node.Y) - GetYFromHexCoordinatesDefault(0, 0);
	
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
	
	var r = -Map()->GetDrawRotation();
	var prec = Map()->GetDrawRotationPrecision();
	
	var factor = 1000;

	var fsin = Sin(r, factor, prec);
	var fcos = Cos(r, factor, prec);

	SetGraphics(graphics_name, graphics_definition ?? GetID(), layer, GFXOV_MODE_Base);
//	SetObjDrawTransform(this->GetTileWidth(), 0, 0, 0, this->GetTileHeight(), 0, layer);
  	SetObjDrawTransform(+fcos * this->GetTileWidth() / factor,
  	                    +fsin * this->GetTileHeight() / factor, 0,
  	                    -fsin * this->GetTileWidth() / factor,
  	                    +fcos * this->GetTileHeight() / factor, 0, layer);
}
