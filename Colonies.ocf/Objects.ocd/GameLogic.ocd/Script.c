
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
		if (!resource) continue;
	
		if (number == result)
		{
			DoBaseMaterial(TurnManager()->GetActivePlayer(), resource, 1);
			Log("* Got 1 %i from hex number %d", resource, number);
		}
	}
}
