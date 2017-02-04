#ifndef RANDOMGENERATORHELPER_H
#define RANDOMGENERATORHELPER_H

#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class RandomGeneratorHelper
{
    public:
        /** Default constructor */
        RandomGeneratorHelper();
        /** Default destructor */
        virtual ~RandomGeneratorHelper();

        static const vector<double> generateRandomEffect();

        static const int generateRandomInt(const int minimum, const int maximum);

        static const vector<double> generateRandomAttributes(double const mean, double const stddev);

        static double randomMinToMax(double minimum, double maximum);

        static const double rollTheDice();

        static const vector<int> generateRandomLocation(const int minRange, const int maxRange);
};

#endif // RANDOMGENERATORHELPER_H
