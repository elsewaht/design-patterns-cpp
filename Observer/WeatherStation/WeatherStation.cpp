
#include <iostream>

#include "WeatherObject.h" 
#include "StatsView.h"

void test(WeatherObject& weathobj)
{
    std::cout << "----------------------------" << std::endl;
    std::cout << "Measures: " << std::endl;
    std::cout << "Temperature: " << weathobj.GetTemperature() << std::endl;
    std::cout << "Humidity: " << weathobj.GetHumidity() << std::endl;
    std::cout << "Pressure: " << weathobj.GetPressure() << std::endl;
    std::cout << "----------------------------" << std::endl;
}

int main()
{
    std::cout << "Hello World!\n";
    WeatherObject weather;
    weather.SetUpdateFunction(test);
    StatsView statsView(weather);

    while (true)
    {
        weather.Run();
    }

}
