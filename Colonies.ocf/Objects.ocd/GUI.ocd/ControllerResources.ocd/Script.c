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
		Top = "80%",
		Bottom = "100%",
		Priority = 1,
		BackgroundColor = RGBa(1, 1, 1, 128),
		
		menu_resource_grid = 
		{
			Priority = 2,
			Left = "5%",
			Right = "95%",
			Top = "5%",
			Bottom = "95%",
			BackgroundColor = RGBa(255, 255, 0, 128),
		},
	};
	
	for (var i = 0; i < GetLength(GetResourceList()); ++i)
	{
		var resource = GetResourceList()[i];

		gui_menu_resources.menu_resource_grid[Format("%i",resource)] = AssembleResourceIcon(resource, i);
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
		Text = "0x",
	};
}


func GetResourceList()
{
	return [Resource_Wood, Resource_Brick, Resource_Grain, Resource_Wool, Resource_Ore];
}

/* Callbacks */

