
/**
 Gets the width factor for draw transformation.

 @return int The factor for this tile for use with SetObjDrawTransform();
 */
func GetTileWidth()
{
	return GetNodeFactor(1, 1000)[0];
}

/**
 Gets the height factor for draw transformation.

 @return int The factor for this tile for use with SetObjDrawTransform();
 */
func GetTileHeight()
{
	return (GetNodeFactor(0, 1000)[1] + GetNodeFactor(1, 1000)[1])/2;
}


func GetNodeFactor(int index, int precision)
{
	var nodes = [[0, -50], [42, -24], [252, 24], [0, 50], [-42, 24], [-42, -24]];
	var hex_node = GetNodeCoordinates(index);
	var node = nodes[index];
	
	var node_offset = [50, 0];
	var hex_offset = [HexMap_HexRadius() - 1, 0];
	
	return [(hex_node[0] + hex_offset[0]) * precision / (node[0] + node_offset[0]),
	        (hex_node[1] + hex_offset[1]) * precision / (node[1] + node_offset[1])];
}


func GetNodeCoordinates(int index)
{
	var node = GetNodesAdjacentToHex(0, 0)[index];
	
	var x = GetXFromNodeCoordinates(node[0], node[1]) - GetXFromHexCoordinates(0, 0);
	var y = GetYFromNodeCoordinates(node[0], node[1]) - GetYFromHexCoordinates(0, 0);
	
	return [x, y];
}