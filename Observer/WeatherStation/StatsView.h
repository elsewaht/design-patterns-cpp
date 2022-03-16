#pragma once

#include "Observer.h"
#include "Subject.h"

class StatsView: public Observer
{
public:
	StatsView(Subject& su) { 
		ID = 1; 
		su.Register(*this);
	}
	
	virtual unsigned int GetID() override;

	virtual void Update() override;



private:
	unsigned int ID;
};

