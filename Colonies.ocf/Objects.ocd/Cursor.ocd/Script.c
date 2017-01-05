/**
 Cursor

 @author Marky	
*/


// selectable by HUD and some performance optimizations for the HUD updates
#include Library_HUDAdapter
// standard controls
//#include Library_ClonkControl
#include Library_ClonkGamepadControl
#include Library_ClonkUseControl
#include Library_ClonkMenuControl


/* Initialization */

func Construction()
{
	_inherited(...);

	// Broadcast for rules
	GameCallEx("OnClonkCreation", this);
}

/* When adding to the crew of a player */

protected func Recruitment(int iPlr)
{
	// Broadcast for crew
	GameCallEx("OnClonkRecruitment", this, iPlr);
	
	return _inherited(iPlr,...);
}

protected func DeRecruitment(int iPlr) {
	// Broadcast for crew
	GameCallEx("OnClonkDeRecruitment", this, iPlr);
	
	return _inherited(iPlr,...);
}


protected func ControlCommand(szCommand, pTarget, iTx, iTy, pTarget2, Data)
{
	// RejectConstruction Callback for building via Drag'n'Drop form a building menu
	// TODO: Check if we still need this with the new system
	if(szCommand == "Construct")
	{
		if(Data->~RejectConstruction(iTx - GetX(), iTy - GetY(), this) )
		{
			return 1;
		}
	}
	// No overloaded command
	return _inherited(szCommand, pTarget, iTx, iTy, pTarget2, Data, ...);
}



/* Events */


protected func Death(int killed_by)
{
	// this must be done first, before any goals do funny stuff with the clonk
	_inherited(killed_by,...);
	
	// Info-broadcasts for dying clonks.
	GameCallEx("OnClonkDeath", this, killed_by);
	
	// The broadcast could have revived the clonk.
	if (GetAlive())
		return;
		
	return true;
}

protected func Destruction(...)
{
	_inherited(...);
	// If the clonk wasn't dead yet, he will be now.
	// Always kill clonks first. This will ensure relaunch scripts, enemy kill counters, etc. are called
	// even if clonks die in some weird way that causes direct removal
	// (To prevent a death callback, you can use SetAlive(false); RemoveObject();)
	if (GetAlive()) { this.silent_death=true; Kill(); }
	return true;
}


/* Status */

local Name = "Cursor";
local Description = "$Description$";
local BorderBound = C4D_Border_Sides;

/* Main control function */
public func ObjectControl(int plr, int ctrl, int x, int y, int strength, bool repeat, int status)
{
	if (!this) 
		return false;
		
	
	/* aiming with mouse:
	   The CON_Aim control is transformed into a use command. Con_Use if
	   repeated does not bear the updated x,y coordinates, that's why this
	   other control needs to be issued and transformed. CON_Aim is a
	   control which is issued on mouse move but disabled when not aiming
	   or when HoldingEnabled() of the used item does not return true.
	   For the rest of the control code, it looks like the x,y coordinates
	   came from CON_Use.
	  */
	if (this.control.current_object && ctrl == CON_Aim)
	{
		if (this.control.alt) ctrl = CON_UseAlt;
		else     ctrl = CON_Use;
				
		repeat = true;
		status = CONS_Down;
	}
	// controls except a few reset a previously given command
	else if (status != CONS_Moved)
		SetCommand("None");
	
	/* aiming with analog pad or keys:
	   This works completely different. There are CON_AimAxis* and CON_Aim*,
	   both work about the same. A virtual cursor is created which moves in a
	   circle around the clonk and is controlled via these CON_Aim* functions.
	   CON_Aim* is normally on the same buttons as the movement and has a
	   higher priority, thus is called first. The aim is always done, even if
	   the clonk is not aiming. However this returns only true (=handled) if
	   the clonk is really aiming. So if the clonk is not aiming, the virtual
	   cursor aims into the direction in which the clonk is running and e.g.
	   CON_Left is still called afterwards. So if the clonk finally starts to
	   aim, the virtual cursor already aims into the direction in which he ran
	*/
	if (ctrl == CON_AimAxisUp || ctrl == CON_AimAxisDown || ctrl == CON_AimAxisLeft || ctrl == CON_AimAxisRight)
	{
		var success = VirtualCursor()->Aim(ctrl,this,strength,repeat,status);
		// in any case, CON_Aim* is called but it is only successful if the virtual cursor is aiming
		return success && VirtualCursor()->IsAiming();
	}
	
	var use = (ctrl == CON_Use || ctrl == CON_UseAlt);

	// Simulate a mouse cursor for gamepads.
	if (HasVirtualCursor())
	{
		x = this.control.mlastx;
		y = this.control.mlasty;
	}
	// save last mouse position:
	// if the using has to be canceled, no information about the current x,y
	// is available. Thus, the last x,y position needs to be saved
	else if (use)
	{
		this.control.mlastx = x;
		this.control.mlasty = y;
	}

		
	// menu
	if (this.control.menu)
	{
		return Control2Menu(ctrl, x, y, strength, repeat, status);
	}
	
	// usage
	if (use)
	{
		// Release commands are always forwarded even if contents is 0, in case we
		// need to cancel use of an object that left inventory
		if (status == CONS_Up && GetUsedObject())
		{
			if (ControlUse2Script(ctrl, x, y, strength, repeat, status, GetUsedObject()))
				return true;
		}
		
		if (ControlUse2Script(ctrl, x, y, strength, repeat, status, this))
		{
			return true;
		}
	}
	
		
	// Movement controls (defined in PlayerControl.c, partly overloaded here)
	if (ctrl == CON_Left || ctrl == CON_Right || ctrl == CON_Up || ctrl == CON_Down || ctrl == CON_Jump)
	{	
		return ObjectControlMovement(plr, ctrl, strength, status);
	}	
	
	// Unhandled control
	return _inherited(plr, ctrl, x, y, strength, repeat, status, ...);
}

/* ---------- Using the cursor ------------ */


protected func ControlUseStart(object user, int x, int y)
{
	var target_x = x + GetX();
	var target_y = y + GetY();
	
	var fx = GetEffect("FxMoveCursor", this);
	
	if (!fx)
	{
		fx = CreateEffect(FxMoveCursor, 1, 1);
	}
	
	fx.TargetX = target_x;
	fx.TargetY = target_y;

	return true;
}

local FxMoveCursor = new Effect
{
	Timer = func()
	{
		if (!this.TargetX && !this.TargetY)
		{
			return;
		}

		var speed = 4;
		var start_x = this.Target->GetX();
		var start_y = this.Target->GetY();
		var dx = this.TargetX - start_x;
		var dy = this.TargetY - start_y;
		
		var x = start_x + dx / speed;
		var y = start_y + dy / speed;

		this.Target->SetPosition(x, y);
		
		if (Abs(dx) <= 1 && Abs(dy) <= 1) return FX_Execute_Kill;
	}
};
