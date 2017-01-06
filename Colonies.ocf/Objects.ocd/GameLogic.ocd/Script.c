
func DetermineResources()
{
	// determine resources
	
	var die1 = RandomX(1, 6);
	var die2 = RandomX(1, 6);
	
	var result = die1 + die2;

	Log("* Die result is %d (%d, %d)", result, die1, die2);
	
	// collect
	for (var hex in Map()->GetHexes())
	{
		var resource = hex->~GetResource();
		var number = hex->~GetNumberChip();
		
		// exclude hexes that were not rolled
		if (!resource) continue;
		if (number != result) continue;
		
		var nodes = hex->GetAdjacentNodes();
		
		for (var node in nodes)
		{
			var structure = node->GetStructure();

			if (structure)
			{
				var production = structure->GetResourceProduction();
				DoBaseMaterial(TurnManager()->GetActivePlayer(), resource, production);
				Log("* Resource production of hex %d: %d %i from %s on %d %d", number, production, resource, structure->GetName(), node.X, node.Y);
			}
		}
	}
}
