#include "GameData.h"
#include "..\Constants\Room.h"
GameData::GameData()
	: room(Constants::Room::COLUMNS, Constants::Room::ROWS)
{

}

const Room& GameData::GetRoom() const
{
	return room;
}

Room& GameData::GetRoom()
{
	return room;
}
