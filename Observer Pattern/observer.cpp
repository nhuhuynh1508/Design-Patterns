#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <time.h>

using namespace std;

class Observer
{
  public:
    virtual void update(float temp, float humidity, float pressure) = 0;
};

class DisplayElement
{
  public:
    virtual void display() = 0;
};

class Subject
{
  public:
    virtual void registerObserver(Observer* o) = 0;

    virtual void removeObserver(Observer* o) = 0;

    virtual void notifyObservers() = 0;
}; 

class WeatherData : public Subject
{
  private:
    vector <Observer*> observers;
    float temperature;
    float humidity;
    float pressure;

  public:
    WeatherData() {}

    void registerObserver(Observer* o) 
    {
      observers.push_back(o);
    }

    void removeObserver(Observer* o)
    {
      int i = 0;
      while (observers[i] != o)
      {
        i++;
      }
      
      if (i < observers.size())
      {
        observers.erase(observers.begin()+i);
      }
    }

    void notifyObservers()
    {
      for (int i = 0; i < observers.size(); i++)
      {
        observers[i]->update(temperature, humidity, pressure);
      }
    }

    void measurementsChanged()
    {
      notifyObservers();
    }

    void setMeasurement(float temperature, float humidity, float pressure)
    {
      this->temperature = temperature;
      this->humidity = humidity;
      this->pressure = pressure;
      measurementsChanged();
    }     
};

class CurrentConditionDisplay : public Observer, public DisplayElement
{
  private:
    float temperature;
    float humidity;
    float pressure;
    Subject* weatherData;

  public:
    CurrentConditionDisplay(Subject* weatherData)
    {
      this->weatherData = weatherData;
      weatherData->registerObserver(this);
    }

    void update(float temperature, float humidity, float pressure)
    {
      this->temperature = temperature;
      this->humidity = humidity;
      this->pressure = pressure;
      display();
    }

    void display()
    {
      time_t currentTime = time(0);
      char* timeString = ctime(&currentTime);
      cout << "Current date and time: " << timeString;
      cout << "Current condition: " << temperature << "F degrees and " << humidity << "\% humidity and " << pressure << " ''Hg" << endl << endl;
    }
};

int main() {
  srand(time(NULL));
  while (true) {
    WeatherData weatherData;
    CurrentConditionDisplay* currentDisplay = new CurrentConditionDisplay(&weatherData);

    int tem = rand() % 50 + 70;
    int hum = rand() % 70 + 30;
    float pres = (rand() % 100)/50 + 29;
    weatherData.setMeasurement(tem, hum, pres);

    sleep(5); // Sleep for 5 seconds
  }
  return 0;
}

