#include "Equipment.h"
#include <sstream>

int Equipment::counter = 1;

Equipment::Equipment(default_random_engine& gen, bool autoGenerate)
{
    std::ostringstream ss;
    ss << counter;
    name = "Equipment #" + ss.str();
    counter++;
    if(autoGenerate) { populatePowers(gen);}
}

Equipment::Equipment(default_random_engine& gen, string name, bool autoGenerate) : name(name)
{
    if(autoGenerate) { populatePowers(gen);}
}

Equipment::~Equipment()
{
    powers.clear();
}

void Equipment::populatePowers(default_random_engine& gen)
{
    if(powers.size() > 0) { return;}
    int maximum = RandomGeneratorHelper::generateRandomInt(1, 6);
    Power * pow;
    for(int i = 0; i < maximum; ++i)
    {
        pow = new Power(gen);
        addPower(pow);
        pow = nullptr;
    }
}

void Equipment::displayEquipment()
{

    cout << "List of powers in the " << name << ": " << "\n";
    for(list<Power>::iterator it = powers.begin(); it != powers.end(); ++it)
    {
        it->displayPower();
        cout << endl;
    }

}

void Equipment::addPower(Power* pow)
{
    powers.push_back(*pow);
}
/*
void Equipment::removePower()
{
    powers.pop_back();
}
*/
