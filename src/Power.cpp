#include "Power.h"

int Power::counter = 1;

Power::Power(bool generateRandom)
{
    range = -1;
     std::ostringstream ss;
    ss << counter;
    name = "Power #" + ss.str();
    counter++;
    if(generateRandom) { populatePower(); }
    //displayPower();
}

Power::Power(int duration, double eff1,
                    double eff2, double eff3, double eff4, double range) : duration(duration),range(range)
{
    std::ostringstream ss;
    ss << counter;
    name = "Power #" + ss.str();
    counter++;
    effect.push_back(eff1); effect.push_back(eff2); effect.push_back(eff3); effect.push_back(eff4);
}

Power::~Power()
{
    this->effect.clear();
}

void Power::populatePower()
{
    this->duration = RandomGeneratorHelper::generateRandomInt(1, 3);
    canFly = RandomGeneratorHelper::generateRandomInt(0, 2) == 0 ? false : true;
        //floor(RandomGeneratorHelper::randomMinToMax(1, 5) * 100) / 100;
    this->Seteffect(RandomGeneratorHelper::generateRandomEffect());
    this->range = floor(RandomGeneratorHelper::randomMinToMax(5, 35)  * 100) / 100;
}

void Power::displayPower()
{
    cout << name << ": Effects: ( ";
    for(vector<double>::iterator it = this->effect.begin(); it < effect.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << ")" << ", Duration: " << duration << ", Range: " << range << ", Can fly: " << canFly << endl;

}
