/**
 Expansion of the hex data object.
 */

#include GameMap_Hex
#include Plugin_Element_GraphicsObject


/** The number chip that was added on top of a hex. */
local number_chip;

/** The resource that is produced by the hex. */
local resource;

/** Does the tile allow resource trade? */
local allow_trade;

/** Custom graphics base name. */
local graphics_base;

/** Custom graphics top name. */
local graphics_top;


/**
 The ID for the game hexes. Overload this f you want to create different tiles.
 
 @return id The ID for the game hexes.
 */
global func GameMap_HexID()
{
	return GameMap_HexExtended;
}


/**
 Adds a number chip to the hex.
 
 @par number The number. Usually this should be a number from 2 to 12,
             depending on the rules of your scenario.
             Setting the number to {@c nil} or to a number that cannot be
             achieved by the resource dice will turn the tile unproductive.

 @return object The hex itself, so that further functions can be called on it.
 */
func AddNumberChip(int number)
{
	this.number_chip = number;
	return this;
}


/**
 Gets the number chip that is on this hex.
 
 @return int The number. A number of {@c nil} indicates that this hex
             is not productive.
 */
func GetNumberChip()
{
	return this.number_chip;
}


/**
 Assigns a resource to the hex.
 
 @par resource This resource will be produced in that
               hex if the number is {@link GameMap_Hex#GetNumber}
               is rolled.

 @return object The hex itself, so that further functions can be called on it.
 */
func SetResource(id resource)
{
	this.resource = resource;
	return this;
}


/**
 Gets the resource that is produced on this hex.
 
 @return id The resource.
 */
func GetResource()
{
	return this.resource;
}


/**
 Determines whether resources can be traded on this hex.
 
 @par allow Set to {@c true} if you want to allow trade on this hex.
            The trade rules are defined elsewhere.

 @return object The hex itself, so that further functions can be called on it.
 */
func AllowTrade(bool allow)
{
	this.allow_trade = allow;
	return this;
}


/**
 Ask whether trade is allowed on this hex.
 
 @return bool Returns {@c true} if trade is allowed.
 */
func CanTrade()
{
	return this.allow_trade;
}


/**
 Sets the base graphics of this hex.
 
 @par name The graphics name.

 @return object The hex itself, so that further functions can be called on it.
 */
func SetBaseGraphics(string name)
{
	graphics_base = name;
	return this;
}


/**
 Sets the top graphics of this hex.
 
 @par name The graphics name.

 @return object The hex itself, so that further functions can be called on it.
 */
func SetTopGraphics(string name)
{
	graphics_top = name;
	return this;
}


/**
 Decides how to draw the hex. Overload this function if you want to draw it differently.
 */
func DrawElement()
{
	_inherited(...);

	
	if (GetResource() && GetNumberChip())
	{
		graphics_base = graphics_base ?? "Land";
		
		graphics_top = graphics_top ?? GetResourceGraphics();
	}
	else
	{
 		graphics_base = graphics_base ?? "Sea";
	}

	GetGraphicsObject()->DrawLayer(graphics_base, Graphics_MapTile, 1);
	GetGraphicsObject()->DrawLayer(graphics_top, Graphics_MapTile, 2);
}


func GetResourceGraphics()
{
	var res = GetResource();

	if (res == Resource_Brick) return "Loam";
	if (res == Resource_Grain) return "Field";
	if (res == Resource_Ore) return "Mountain";
	if (res == Resource_Wood) return "Forest";
	if (res == Resource_Wool) return "Pasture";

	return nil;
}
