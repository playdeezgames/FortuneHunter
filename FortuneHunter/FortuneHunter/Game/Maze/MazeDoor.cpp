#include "MazeDoor.h"
MazeDoor::MazeDoor()
	: open(false)
{

}

bool MazeDoor::IsOpen() const
{
	return open;
}

void MazeDoor::SetOpen(bool state)
{
	open = state;
}
