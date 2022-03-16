#pragma once
class Observer
{
public:
	virtual void Update() = 0;

	virtual unsigned int GetID() = 0;
};

