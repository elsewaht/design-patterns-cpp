#include "WeatherObject.h"

#include "Observer.h"

#include <iostream>
#include <string>


WeatherObject::WeatherObject() {
	NotifyFunction = nullptr;

	ShouldUpdate = false;

	WeatherFile.open("weathernumbers.txt", std::ifstream::in);

	if (WeatherFile.is_open())
	{
		std::cout << "Weather Numbers file correctly opened.\n";
	}
	else
	{
		std::cout << "Error opening Weather Numbers file.\n";
	}
}

WeatherObject::~WeatherObject() {
	WeatherFile.close();
}

float WeatherObject::GetTemperature() const
{
	return StoredMeassures.Temperature;
}

float WeatherObject::GetHumidity() const
{
	return StoredMeassures.Humidity;
}

float WeatherObject::GetPressure() const
{
	return StoredMeassures.Pressure;
}

void WeatherObject::SetUpdateFunction(NotifyUpdate functToUpdate) 
{
	NotifyFunction = functToUpdate;
	std::cout << "UpdateFunction correctly setted.\n";
}

void WeatherObject::Run() 
{
	CheckAndUpdate();
}

void WeatherObject::Register(Observer& ob)
{
	Views.insert(std::pair<unsigned int, Observer&>(ob.GetID(), ob));
}

void WeatherObject::Detach(Observer& ob)
{
	Views.erase(ob.GetID());
}

void WeatherObject::PollMeasures()
{
	if (!WeatherFile.is_open())
	{
		WeatherFile.open("weathernumbers.txt", std::ifstream::in);	
	}

	if (WeatherFile.is_open())
	{
		std::string Line;
		
		while (!std::getline(WeatherFile, Line).eof())
		{
			size_t EqualPosition = Line.find('=');
			std::string Key = Line.substr(0, EqualPosition);
			std::string Value = Line.substr(EqualPosition + 1, Line.size() - EqualPosition - 1);

			if(Key == "temp")
				CurrentMeasures.Temperature = std::stof(Value);

			if (Key == "humidity")
			{
				CurrentMeasures.Humidity = std::stof(Value);
			}
				

			if (Key == "pressure")
			{
				CurrentMeasures.Pressure = std::stof(Value);
			}
				
			//std::cout << CurrentMeasures.Temperature << std::endl;
			//std::cout << CurrentMeasures.Humidity << std::endl;
			//std::cout << CurrentMeasures.Pressure << std::endl;
			//std::cout << "----------------------------" << std::endl;
		} 
		WeatherFile.close();
	}
	else
	{
		std::cout << "Read file not opened. Can't read.\n";
	}
}

void WeatherObject::CheckAndUpdate()
{
	PollMeasures();

	if (CurrentMeasures.Temperature != StoredMeassures.Temperature)
	{
		StoredMeassures.Temperature = CurrentMeasures.Temperature;
		ShouldUpdate = true;
	}

	if (CurrentMeasures.Humidity != StoredMeassures.Humidity)
	{
		StoredMeassures.Humidity = CurrentMeasures.Humidity;
		ShouldUpdate = true;
	}

	if (CurrentMeasures.Pressure != StoredMeassures.Pressure)
	{
		StoredMeassures.Pressure = CurrentMeasures.Pressure;
		ShouldUpdate = true;
	}

	if (ShouldUpdate)
	{
		for (auto View : Views)
		{
			View.second.Update();
		}

		NotifyFunction(*this);
		ShouldUpdate = false;
	}

}

