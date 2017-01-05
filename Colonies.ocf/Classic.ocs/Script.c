
func Initialize()
{
	DefaultScenario();
	SetupHexMap();
	DrawHexMap();
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
	// row 0: sea tiles
	Map()->AddHex( 0,  0)->AllowTrade(true)->SetResource(Resource_Ore); // Rock, 2:1
	Map()->AddHex( 2,  0);
	Map()->AddHex( 4,  0)->AllowTrade(true)->SetResource(Resource_Wool); // Sheep, 2:1 
	Map()->AddHex( 6,  0);

	// row 1: sea tiles, topmost land row
	Map()->AddHex( 0,  2);
	Map()->AddHex( 2,  2)->SetResource(Resource_Grain)->AddNumberChip(4);
	Map()->AddHex( 4,  2)->SetResource(Resource_Wood)->AddNumberChip(6);
	Map()->AddHex( 6,  2)->SetResource(Resource_Grain)->AddNumberChip(9);
	Map()->AddHex( 8,  2)->AllowTrade(true)->SetResource(nil); // Any, 3:1 

	// row 2: land 4 tiles
	Map()->AddHex( 0,  4)->AllowTrade(true)->SetResource(Resource_Wood); // Wood, 2:1 
	Map()->AddHex( 2,  4)->SetResource(Resource_Brick)->AddNumberChip(2);
	Map()->AddHex( 4,  4)->SetResource(Resource_Wood)->AddNumberChip(5);
	Map()->AddHex( 6,  4)->SetResource(Resource_Wool)->AddNumberChip(12);
	Map()->AddHex( 8,  4)->SetResource(Resource_Wool)->AddNumberChip(4);
	Map()->AddHex(10,  4);

	// row 3: 5 tiles, middle row
	Map()->AddHex( 0,  6);
	Map()->AddHex( 2,  6)->SetResource(Resource_Wool)->AddNumberChip(9);
	Map()->AddHex( 4,  6)->SetResource(Resource_Brick)->AddNumberChip(8);
	Map()->AddHex( 6,  6)->AddNumberChip(nil); // Desert
	Map()->AddHex( 8,  6)->SetResource(Resource_Ore)->AddNumberChip(8);
	Map()->AddHex(10,  6)->SetResource(Resource_Wool)->AddNumberChip(10);
	Map()->AddHex(12,  6)->AllowTrade(true)->SetResource(nil); // Any, 3:1 

	// row 4: 4 tiles
	Map()->AddHex( 2,  8)->AllowTrade(true)->SetResource(nil); // Any, 3:1 
	Map()->AddHex( 4,  8)->SetResource(Resource_Wood)->AddNumberChip(3);
	Map()->AddHex( 6,  8)->SetResource(Resource_Ore)->AddNumberChip(5);
	Map()->AddHex( 8,  8)->SetResource(Resource_Brick)->AddNumberChip(10);
	Map()->AddHex(10,  8)->SetResource(Resource_Wood)->AddNumberChip(11);
	Map()->AddHex(12,  8);

	// row 5: 3 tiles, lowest row
	Map()->AddHex( 4, 10);
	Map()->AddHex( 6, 10)->SetResource(Resource_Grain)->AddNumberChip(3);
	Map()->AddHex( 8, 10)->SetResource(Resource_Grain)->AddNumberChip(6);
	Map()->AddHex(10, 10)->SetResource(Resource_Ore)->AddNumberChip(11);
	Map()->AddHex(12, 10)->AllowTrade(true)->SetResource(Resource_Grain); // Wheat, 2:1 

	// ports
	Map()->AddHex( 6, 12)->AllowTrade(true)->SetResource(Resource_Brick); // Loam, 2:1 
	Map()->AddHex( 8, 12);
	Map()->AddHex(10, 12)->AllowTrade(true)->SetResource(nil); // Any, 3:1 
	Map()->AddHex(12, 12);
	
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
    	//dummy->Message("@(%d/%d)", hex_x, hex_y);
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
    	//node->Message("@(%d/%d) (%d/%d)", x, y, x2, y2);
    }
}


func SetupHexMap()
{
	Map()->SetCoordinateOrientation(1);
	Map()->SetNumberOfHexesX(6);
	Map()->SetNumberOfHexesY(6);
	Map()->SetupCornersHexagonal();
	Map()->CalculateDimensions();
	Map()->SetMapPosition(0, 0);
}


func OrientHexMap(int orientation)
{
	Map()->SetCoordinateOrientation(orientation);
	Map()->SetNumberOfHexesX(12);
	Map()->SetNumberOfHexesY(12);
	Map()->SetupCornersHexagonal();
	var dim = Map()->CalculateDimensions();
	Map()->SetMapPosition(0, 0);
	DrawHexMap();
	
	Log("Dimensions: %d/%d, %d/%d", dim.x, dim.y, dim.wdt, dim.hgt);
}
