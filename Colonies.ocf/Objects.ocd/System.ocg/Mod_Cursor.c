#appendto Game_Cursor

func IsBase() // The cursor is a base, so that it receives callbacks from the base material
{
	return true;
}


func OnBaseMaterialChange(id material, int change)
{
	if (GetHUDController())
		GetHUDController()->~OnBaseMaterialChange(material, change);
}

