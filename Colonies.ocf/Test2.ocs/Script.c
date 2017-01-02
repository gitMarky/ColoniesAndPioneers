
func Initialize()
{
	DefaultScenario();
	DrawHexMap();
}


func DefaultScenario()
{
	// 3 tiles, topmost land row
	Map()->AddHex(4, 4); // Wheat, Nr 4
	Map()->AddHex(6, 6); // Wood, Nr 6
	Map()->AddHex(8, 8); // Wheat, Nr 9 

	// 4 tiles
	Map()->AddHex( 4, 2); // Loam, Nr 2
	Map()->AddHex( 6, 4); // Wood, Nr 5
	Map()->AddHex( 8, 6); // Sheep, Nr 12
	Map()->AddHex(10, 8); // Sheep, Nr 4

	// 5 tiles, middle row
	Map()->AddHex( 4, 0); // Sheep, Nr 9
	Map()->AddHex( 6, 2); // Loam, Nr 8
	Map()->AddHex( 8, 4); // Desert, Nr X
	Map()->AddHex(10, 6); // Rock, Nr 8
	Map()->AddHex(12, 8); // Sheep, Nr 10

	// 4 tiles
	Map()->AddHex( 6, 0); // Wood, Nr 3
	Map()->AddHex( 8, 2); // Rock, Nr 5
	Map()->AddHex(10, 4); // Loam, Nr 10
	Map()->AddHex(12, 6); // Wood, Nr 11

	// 3 tiles, lowest row
	Map()->AddHex( 8, 0); // Wheat, Nr 3
	Map()->AddHex(10, 2); // Wheat, Nr 6
	Map()->AddHex(12, 4); // Rock, Nr 11
	
	// ports
	Map()->AddHex( 2,  4); // Port, Rock, 2:1 
	Map()->AddHex( 6,  8); // Port, Sheep, 2:1 
	Map()->AddHex(10, 10); // Port, Any, 3:1 
	Map()->AddHex(14, 10); // Port, Any, 3:1 
	Map()->AddHex(14,  6); // Port, Wheat, 2:1 
	Map()->AddHex(12,  2); // Port, Any, 3:1 
	Map()->AddHex( 8, -2); // Port, Loam, 2:1 
	Map()->AddHex( 4, -2); // Port, Any, 3:1 
	Map()->AddHex( 2,  0); // Port, Wood, 2:1 

	// other sea tiles
	Map()->AddHex( 4,  6);
	Map()->AddHex( 8, 10);
	Map()->AddHex(12, 10);
	Map()->AddHex(14,  8);
	Map()->AddHex(14,  4);
	Map()->AddHex(10,  0);
	Map()->AddHex( 6, -2);
	Map()->AddHex( 2, -2);
	Map()->AddHex( 2,  2);
}

func DrawHexMap()
{
	for (var hex_x = 0; hex_x < 20; hex_x += 2)
    for (var hex_y = 0; hex_y < 20; hex_y += 2)
    {
    	if (Map()->GetHex(hex_x, hex_y) == nil)
    	{
    		continue;
    	}
    
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
    		var x = edge_centers[i][0];
    		var y = edge_centers[i][1];
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
    		var x = nodes[i][0];
    		var y = nodes[i][1];
	    	var node = CreateObject(Ore);
	    	node->SetCategory(C4D_StaticBack);
	    	node->SetPosition(GetXFromNodeCoordinates(x, y),
	    	                  GetYFromNodeCoordinates(x, y));
	    	node->Message("@(%d/%d)", x, y);
    	}
    }
}