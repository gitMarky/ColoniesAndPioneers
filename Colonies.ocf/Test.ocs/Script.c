
func Initialize()
{
    for (var hex_x = 0; hex_x < 20; hex_x += 2)
    for (var hex_y = 0; hex_y < 20; hex_y += 2)
    {
	    // Create hex centers
    	var dummy = CreateObject(Rock);
    	dummy->SetCategory(C4D_StaticBack);
    	dummy->SetPosition(GetXFromHexCoordinates(hex_x, hex_y),
    	                   GetYFromHexCoordinates(hex_x, hex_y));
    	dummy->Message("@(%d/%d)", hex_x, hex_y);
    	
    	// Create edge centers
    	var edge_centers = GetEdgesAdjacentToHex(hex_x, hex_y);
    	for (var i = 0; i < 3; ++i)
    	{
    		var x = edge_centers[i].X;
    		var y = edge_centers[i].Y;
	    	var edge = CreateObject(Loam);
	    	edge->SetCategory(C4D_StaticBack);
	    	edge->SetPosition(GetXFromHexCoordinates(x, y),
	    	                  GetYFromHexCoordinates(x, y));
	    	edge->Message("@(%d/%d)", x, y);
    	}
    	
    	// Create nodes
    	var nodes = GetNodesAdjacentToHex(hex_x, hex_y);
    	for (var i = 0; i < 2; ++i)
    	{
    		var x = nodes[i].X;
    		var y = nodes[i].Y;
	    	var node = CreateObject(Ore);
	    	node->SetCategory(C4D_StaticBack);
	    	node->SetPosition(GetXFromNodeCoordinates(x, y),
	    	                  GetYFromNodeCoordinates(x, y));
	    	node->Message("@(%d/%d)", x, y);
    	}
    }
}