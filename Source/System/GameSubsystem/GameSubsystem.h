#pragma once

class GameSubsystem
{
public:
	static GameSubsystem& Get() { return Instance; }

	virtual void Initialize();

private:
	static GameSubsystem Instance;
};