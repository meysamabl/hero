#include "Location.h"

Location::Location(const int minRange,const int maxRange)
{
    vector<int> myloc = RandomGeneratorHelper::generateRandomLocation(minRange, maxRange);
    x = myloc[0];
    y = myloc[1];
    z = myloc[2];
    //uniform_int_distribution<int> dist(minRange, maxRange);
    //x = dist(gen);
    //y = dist(gen);
    //z = dist(gen);
}

Location::Location(int x, int y, int z) : x(x), y(y), z(z)
{

}

Location::~Location()
{
    //dtor
}

void Location::displayLocation()
{
    cout<<"Location: " << "x: " << x << ", y: " << y << ", z: " << z << endl;
}
