/**
	Victory points
	
	A certain amount of victory points must be collected
	
	@author Marky
*/

#include Goal_Script

local victory_point_limit;

func Initialize()
{
	victory_point_limit = 10;
	return inherited(...);
}

func SetVictoryPointGoal(int amount)
{
	victory_point_limit = amount;
}


func GetVictoryPointGoal()
{
	return victory_point_limit;
}


func SaveScenarioObject(proplist props)
{
	if (!inherited(props, ...)) return false;
	if (victory_point_limit) props->AddCall("Goal", this, "SetVictoryPointGoal", victory_point_limit);
	return true;
}


/*-- Goal interface --*/


func GetDescription(int player)
{
	if (IsFulfilled())
		return Format("$MsgGoalFulfilled$");	
	else
		return Format("$MsgGoalUnFulfilled$", GetVictoryPointMessage());
}


func GetVictoryPointMessage()
{
	var message = "";
	return message;
}


// Shows or hides a message window with information.
func Activate(int player)
{
	// If goal message open -> hide it.
	if (GetEffect("GoalMessage", this))
	{
		CustomMessage("", nil, player, nil, nil, nil, nil, nil, MSG_HCenter);
		RemoveEffect("GoalMessage", this);
		return;
	}

	// Otherwise open a new message.
	AddEffect("GoalMessage", this, 100, 0, this);

	var message;
	if (IsFulfilled())
		message = Format("@$MsgGoalFulfilled$");	
	else
		message = Format("@$MsgGoalUnFulfilled$", GetVictoryPointMessage());
		
	CustomMessage(message, nil, player, 0, 16 + 64, 0xffffff, GUI_MenuDeco, this, MSG_HCenter);
	return;
}

protected func FxGoalMessageStart() {}

public func GetShortDescription(int player)
{
	var msg = "";
	return msg;
}


/*-- Proplist --*/

local Name = "$Name$";
local Visibility = VIS_Editor;
