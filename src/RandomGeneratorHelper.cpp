#include "RandomGeneratorHelper.h"

extern default_random_engine gen;
extern uniform_int_distribution<int> distLoc;
extern uniform_real_distribution<double> distMinMax;
extern uniform_int_distribution<int> distInt;
extern normal_distribution<double> normDistEff;
extern normal_distribution<double> normDistAttr;

RandomGeneratorHelper::RandomGeneratorHelper()
{
    //ctor
}

RandomGeneratorHelper::~RandomGeneratorHelper()
{
    //dtor
}

const vector<int> RandomGeneratorHelper::generateRandomLocation(const int minRange, const int maxRange)
{
    vector<int> loc;
    //uniform_int_distribution<int> dist(minRange, maxRange);
    distLoc.param(uniform_int_distribution<int>(minRange, maxRange).param());
    loc.push_back(distLoc(gen));
    loc.push_back(distLoc(gen));
    loc.push_back(distLoc(gen));
    random_shuffle(loc.begin(), loc.end());
    return loc;
}

const double RandomGeneratorHelper::rollTheDice()
{
    return randomMinToMax(0.0, 100.0);
}

double RandomGeneratorHelper::randomMinToMax(double minimum, double maximum)
{
    //uniform_real_distribution<double> dist(minimum, maximum);
    distMinMax.param(uniform_real_distribution<double>(minimum, maximum).param());
    return distMinMax(gen);
}

/// random [minimum, maximum)
const int RandomGeneratorHelper::generateRandomInt(const int minimum, const int maximum)
{
    //uniform_int_distribution<int> dist(minimum, maximum - 1);
    distInt.param(uniform_int_distribution<int>(minimum, maximum-1).param());
    return distInt(gen);
}

const vector<double> RandomGeneratorHelper::generateRandomEffect()
{
    vector<double> myEffects;
    //double sum;
    double tempVal;
    //std::normal_distribution<double> dist(3, 5);
    normDistEff.param(normal_distribution<double>(3,3).param());
    for (int i = 0; i < 4; ++i)
    {
        tempVal = floor((normDistEff(gen) + 0.005) * 100) / 100 ;
        //sum += tempVal;
        myEffects.push_back(tempVal);
    }
    random_shuffle(myEffects.begin(), myEffects.end());
    return myEffects;
}

const vector<double> RandomGeneratorHelper::generateRandomAttributes(double mean, double stddev)
{
    vector<double> myAttr;
    double tempVal;
    //std::normal_distribution<double> dist(mean, stddev);
    normDistAttr.param(normal_distribution<double>(mean, stddev).param());
    for(int i = 0; i < 4; ++i)
    {
        tempVal = floor((normDistAttr(gen) + 0.005) * 100) / 100;
        myAttr.push_back(tempVal);
    }
    random_shuffle(myAttr.begin(), myAttr.end());
    return myAttr;
}
