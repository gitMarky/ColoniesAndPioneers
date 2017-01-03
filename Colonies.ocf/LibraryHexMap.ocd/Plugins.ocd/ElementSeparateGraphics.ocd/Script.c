
/** The object graphics. */
local graphics_object;


func GetGraphicsDefinition()
{
	return Graphics_HexTile;
}


func GetGraphicsObject()
{
	if (!graphics_object)
	{
		graphics_object = CreateObject(this->GetGraphicsDefinition(), 0, 0, NO_OWNER);
		graphics_object->SetPosition(GetXFromHexCoordinates(this.X, this.Y),
		                             GetYFromHexCoordinates(this.X, this.Y));
	}
	
	return graphics_object;
}
