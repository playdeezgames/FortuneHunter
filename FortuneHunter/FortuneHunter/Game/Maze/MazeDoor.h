#pragma once
class MazeDoor
{
private:
	bool open;
public:
	MazeDoor();
	bool IsOpen() const;
	void SetOpen(bool);
};