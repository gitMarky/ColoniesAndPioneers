
func Initialize()
{
	DefaultScenario();
	ScheduleCall(nil, this.DrawHexMap, 1, 1);
}


func InitializePlayer(int player, int x, int y, object base, int team, id extra_data)
{
	var cursor = GetHiRank(player);
	
	if (cursor)
	{
		cursor->SetPosition(LandscapeWidth() / 2, LandscapeHeight() / 2);
	}
}


func DefaultScenario()
{
	// 3 tiles, topmost land row
	Map()->AddHex( 8,  8)->SetResource(Resource_Grain)->AddNumberChip(4);
	Map()->AddHex(10, 10)->SetResource(Resource_Wood)->AddNumberChip(6);
	Map()->AddHex(12, 12)->SetResource(Resource_Grain)->AddNumberChip(9);

	// 4 tiles
	Map()->AddHex( 8,  6)->SetResource(Resource_Brick)->AddNumberChip(2);
	Map()->AddHex(10,  8)->SetResource(Resource_Wood)->AddNumberChip(5);
	Map()->AddHex(12, 10)->SetResource(Resource_Wool)->AddNumberChip(12);
	Map()->AddHex(14, 12)->SetResource(Resource_Wool)->AddNumberChip(4);

	// 5 tiles, middle row
	Map()->AddHex( 8,  4)->SetResource(Resource_Wool)->AddNumberChip(9);
	Map()->AddHex(10,  6)->SetResource(Resource_Brick)->AddNumberChip(8);
	Map()->AddHex(12,  8)->AddNumberChip(nil); // Desert
	Map()->AddHex(14, 10)->SetResource(Resource_Ore)->AddNumberChip(8);
	Map()->AddHex(16, 12)->SetResource(Resource_Wool)->AddNumberChip(10);

	// 4 tiles
	Map()->AddHex(10,  4)->SetResource(Resource_Wood)->AddNumberChip(3);
	Map()->AddHex(12,  6)->SetResource(Resource_Ore)->AddNumberChip(5);
	Map()->AddHex(14,  8)->SetResource(Resource_Brick)->AddNumberChip(10);
	Map()->AddHex(16, 10)->SetResource(Resource_Wood)->AddNumberChip(11);

	// 3 tiles, lowest row
	Map()->AddHex(12, 4)->SetResource(Resource_Grain)->AddNumberChip(3);
	Map()->AddHex(14, 6)->SetResource(Resource_Grain)->AddNumberChip(6);
	Map()->AddHex(16, 8)->SetResource(Resource_Ore)->AddNumberChip(11);

	// ports
	Map()->AddHex( 6,  8)->AllowTrade(true)->SetResource(Resource_Ore); // Rock, 2:1 
	Map()->AddHex(10, 12)->AllowTrade(true)->SetResource(Resource_Wool); // Sheep, 2:1 
	Map()->AddHex(14, 14)->AllowTrade(true)->SetResource(nil); // Any, 3:1 
	Map()->AddHex(18, 14)->AllowTrade(true)->SetResource(nil); // Any, 3:1 
	Map()->AddHex(18, 10)->AllowTrade(true)->SetResource(Resource_Grain); // Wheat, 2:1 
	Map()->AddHex(16,  6)->AllowTrade(true)->SetResource(nil); // Any, 3:1 
	Map()->AddHex(12,  2)->AllowTrade(true)->SetResource(Resource_Brick); // Loam, 2:1 
	Map()->AddHex( 8,  2)->AllowTrade(true)->SetResource(nil); // Any, 3:1 
	Map()->AddHex( 6,  4)->AllowTrade(true)->SetResource(Resource_Wood); // Wood, 2:1 

	// other sea tiles
	Map()->AddHex( 8, 10);
	Map()->AddHex(12, 14);
	Map()->AddHex(16, 14);
	Map()->AddHex(18, 12);
	Map()->AddHex(18,  8);
	Map()->AddHex(14,  4);
	Map()->AddHex(10,  2);
	Map()->AddHex( 6,  2);
	Map()->AddHex( 6,  6);
	
	// Create edges and nodes
	for (var hex in Map()->GetHexes())
	{
		var edges = GetEdgesAdjacentToHex(hex.X, hex.Y);
		var nodes = GetNodesAdjacentToHex(hex.X, hex.Y);

		for (var edge in edges)
		{
			Map()->AddEdge(edge.X, edge.Y);
		}

		for (var node in nodes)
		{
			Map()->AddNode(node.X, node.Y);
		}
	}
}

func DrawHexMap()
{

	Map()->DrawElements();

	//return;
	
	for (var node in FindObjects(Find_Or(Find_ID(Rock), Find_ID(Loam), Find_ID(Ore))))
	{
		if (node) node->RemoveObject();
	}

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
    	dummy->SetPosition(Map()->GetXFromHexCoordinates(hex_x, hex_y),
    	                   Map()->GetYFromHexCoordinates(hex_x, hex_y));
    	dummy->Message("@(%d/%d)", hex_x, hex_y);
    }

	for (var x = 0; x < 21; x += 1)
    for (var y = 0; y < 21; y += 1)
    {
    	if (Map()->GetEdge(x, y) == nil)
    	{
    		continue;
    	}

    	var edge = CreateObject(Loam);
    	edge->SetCategory(C4D_StaticBack);
    	edge->SetPosition(Map()->GetXFromHexCoordinates(x, y),
    	                  Map()->GetYFromHexCoordinates(x, y));
    	//edge->Message("@(%d/%d)", x, y);
    }
    	
	for (var x = 0; x < 21; x += 1)
    for (var y = 0; y < 21; y += 1)
    {
    	if (Map()->GetNode(x, y) == nil)
    	{
    		continue;
    	}

    	var node = CreateObject(Ore);
    	var x2 = Map()->GetXFromNodeCoordinates(x, y);
    	var y2 = Map()->GetYFromNodeCoordinates(x, y);
    	node->SetCategory(C4D_StaticBack);
    	node->SetPosition(x2,
    	                  y2);
    	node->Message("@(%d/%d) (%d/%d)", x, y, x2, y2);
    }
}


func OrientHexMap(int orientation)
{
	Map()->SetCoordinateOrientation(orientation);
	Map()->SetNumberOfHexesX(12);
	Map()->SetNumberOfHexesY(12);
	Map()->SetupCornersHexagonal();
	var dim = Map()->CalculateDimensions();
	DrawHexMap();
	
	Log("Dimensions: %d/%d, %d/%d", dim.x, dim.y, dim.wdt, dim.hgt);
}
