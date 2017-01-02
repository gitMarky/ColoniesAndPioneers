
func Initialize()
{
	DefaultScenario();
	DrawHexMap();
}


func DefaultScenario()
{
	// 3 tiles, topmost land row
	Map()->AddHex(4, 4)->AddNumberChip(4); // Wheat
	Map()->AddHex(6, 6)->AddNumberChip(6); // Wood
	Map()->AddHex(8, 8)->AddNumberChip(9); // Wheat 

	// 4 tiles
	Map()->AddHex( 4, 2)->AddNumberChip(2); // Loam
	Map()->AddHex( 6, 4)->AddNumberChip(5); // Wood
	Map()->AddHex( 8, 6)->AddNumberChip(12); // Sheep
	Map()->AddHex(10, 8)->AddNumberChip(4); // Sheep

	// 5 tiles, middle row
	Map()->AddHex( 4, 0)->AddNumberChip(9); // Sheep
	Map()->AddHex( 6, 2)->AddNumberChip(8); // Loam
	Map()->AddHex( 8, 4)->AddNumberChip(nil); // Desert
	Map()->AddHex(10, 6)->AddNumberChip(8); // Rock
	Map()->AddHex(12, 8)->AddNumberChip(10); // Shee

	// 4 tiles
	Map()->AddHex( 6, 0)->AddNumberChip(3); // Wood
	Map()->AddHex( 8, 2)->AddNumberChip(5); // Rock
	Map()->AddHex(10, 4)->AddNumberChip(10); // Loam
	Map()->AddHex(12, 6)->AddNumberChip(11); // Wood

	// 3 tiles, lowest row
	Map()->AddHex( 8, 0)->AddNumberChip(3); // Wheat
	Map()->AddHex(10, 2)->AddNumberChip(6); // Wheat
	Map()->AddHex(12, 4)->AddNumberChip(11); // Rock
	
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