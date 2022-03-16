#pragma once
class Subject
{
public:
	virtual void Register(class Observer&) = 0;
	virtual void Detach(class Observer&) = 0;
};

