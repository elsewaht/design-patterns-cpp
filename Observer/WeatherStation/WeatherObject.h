#pragma once

#include <fstream>
#include <map>
#include "Subject.h"

// Ref to function to notify changes
typedef void (*NotifyUpdate)(class WeatherObject&);

struct Measures {
	float Temperature = 0.0f;
	float Humidity = 0.0f;
	float Pressure = 0.0f;
};

class WeatherObject: public Subject
{
public:
	WeatherObject();
	~WeatherObject();

	float GetTemperature() const;
	
	float GetHumidity() const;

	float GetPressure() const;

	void SetUpdateFunction(NotifyUpdate funcToNotify) ;

	void Run();

public:
	virtual void Register(class Observer& ob) override;

	virtual void Detach(class Observer& ob) override;

private:
	void PollMeasures();

	void CheckAndUpdate();

private:
	Measures StoredMeassures;

	Measures CurrentMeasures;

	std::ifstream WeatherFile;

	bool ShouldUpdate;

	NotifyUpdate NotifyFunction;

	std::map<unsigned int ,class Observer&> Views;
};

