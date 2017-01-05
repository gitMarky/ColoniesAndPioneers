/**
	Controller Resources

	Shows resources in the bottom part of the screen.
*/

local gui_menu_resources;
local gui_id_resources;

static const GUI_Controller_Resource_IconSize = 25;
static const GUI_Controller_Resource_IconMargin = 5;


/* Creation / Destruction */

func Construction()
{
	var player = GetOwner();

	gui_menu_resources =
	{
		Target = this,
		Player = player,
		Style = GUI_Multiple,
		Left = "0%",
		Right = "100%",
		Top = "0%",
		Bottom = ToEmString(GUI_Controller_Resource_IconSize + GUI_Controller_Resource_IconMargin * 2),
		Priority = -1,
		BackgroundColor = RGBa(1, 1, 1, 128),
	};
	
	for (var i = 0; i < GetLength(GetResourceList()); ++i)
	{
		var resource = GetResourceList()[i];
		gui_menu_resources[GetResourceProperty(resource)] = AssembleResourceIcon(resource, i);
	}

	gui_id_resources = GuiOpen(gui_menu_resources);

	return _inherited(...);
}


func Destruction()
{
	if (gui_id_resources) GuiClose(gui_id_resources);

	_inherited(...);
}


func AssembleResourceIcon(id resource, int slot)
{
	var width =  GUI_Controller_Resource_IconMargin + GUI_Controller_Resource_IconSize;
	var left =   width * slot + GUI_Controller_Resource_IconMargin;
	var right =  width * (slot + 1);
	var top =    GUI_Controller_Resource_IconMargin;
	var bottom = GUI_Controller_Resource_IconMargin + GUI_Controller_Resource_IconSize;
	return {
		Priority = 3,
		Symbol = resource,
		Left = ToEmString(left),
		Right = ToEmString(right),
		Top = ToEmString(top),
		Bottom = ToEmString(bottom),
		Style = GUI_TextBottom | GUI_TextRight,
		Text = GetResourceAmountText(0),
	};
}


func GetResourceList()
{
	return [Resource_Wood, Resource_Brick, Resource_Grain, Resource_Wool, Resource_Ore];
}


func GetResourceProperty(id resource)
{
	return Format("%i", resource);
}


func GetResourceAmountText(int amount)
{
	return Format("%dx", amount);
}


/* Callbacks */

func OnBaseMaterialChange(id material, int change)
{
	if (IsValueInArray(GetResourceList(), material))
	{
		var amount = GetBaseMaterial(GetOwner(), material);
		gui_menu_resources[GetResourceProperty(material)].Text = GetResourceAmountText(amount);
		
		GuiUpdate(gui_menu_resources, gui_id_resources);
	}
	
	_inherited(material, change, ...);
}


