/**
 Handles the way the turn manager behaves
 */

#appendto Environment_TurnManager

local active_player_index; // this player is currently playing


/**
 Tells which player number is currently active.
 @return the active player number.
 */
public func GetActivePlayer()
{
	if (active_player_index[0] >= GetPlayerCount())
	{
		FatalError(Format("Called when active player is %d, but only %d is allowed.", active_player_index[0], GetPlayerCount() - 1));
	}

	return GetPlayerByIndex(active_player_index[0]);
}


/**
 Callback from this object, when the turn is reset and before a new turn starts.
 */
func OnTurnReset(int turn_number)
{
	_inherited(turn_number);
	
	Log("Turn reset: %d", turn_number);

	// cycle the active player when the round is reset
	if (RoundManager()->IsRoundActive())
	{
		// Let the round end
		if (GetLength(active_player_index) == 0)
		{
			RegisterTurnStartBlocker(RoundManager());
			RoundManager()->RemoveRoundEndBlocker(this);
		}
		else // Cycle through the players
		{
			PopFront(active_player_index);
		}
	}
}

func OnTurnStart(int turn_number)
{
	_inherited(turn_number);

	Log("Turn start: %d, active player is %s", turn_number, GetPlayerName(GetActivePlayer()));

	GameLogic->DetermineResources();
}

func OnTurnEnd(int turn_number)
{
	Log("Turn end: %d", turn_number);
	_inherited(turn_number);
}

func OnRoundReset(int round_number)
{
	Log("Round reset: %d", round_number);
	
	// Add all players for the next round
	active_player_index = [];
	
	for (var i = 0; i < GetPlayerCount(); ++i)
	{
		PushBack(active_player_index, i);
	}

	RegisterTurnStartBlocker(RoundManager());
}


/**
 Callback from the round object, when the round starts.
 */
func OnRoundStart(int round_number)
{
	Log("Round %d starts", round_number);
	RemoveTurnStartBlocker(RoundManager());
	RoundManager()->RegisterRoundEndBlocker(this);
}

