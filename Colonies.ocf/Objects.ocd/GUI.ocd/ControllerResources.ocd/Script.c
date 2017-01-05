/**
	Controller Resources

	Shows resources in the bottom part of the screen.
*/

local gui_menu_resources;
local gui_id_resources;


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
	};

	gui_id_resources = GuiOpen(gui_menu_resources);

	return _inherited(...);
}

private func Destruction()
{
	if (gui_id_resources) GuiClose(gui_id_resources);

	_inherited(...);
}

/* Callbacks */

