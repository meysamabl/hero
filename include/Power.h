#ifndef POWER_H
#define POWER_H

#include <iostream>
#include <vector>
#include <exception>
#include <string>
#include <sstream>

#include "RandomGeneratorHelper.h"

using namespace std;

class Power
{
    friend class TestPower;
    public:
        /** Default constructor */
        Power(bool generateRandom = true);

        Power(int duration, double eff1,
                        double eff2, double eff3, double eff4, double range);
        /** Default destructor */
        virtual ~Power();

        void displayPower();

        /** Access duration
         * \return The current value of duration
         */
        const int Getduration() const { return duration; }
        /** Set duration
         * \param val New value to set
         */
        void Setduration(int val) { duration = val; }
        /** Access effect
         * \return The current value of effect
         */
        const vector<double> Geteffect() const { return effect; }
        /** Set effect
         * \param val New value to set
         */
        void Seteffect(vector<double> val)
        {
            if(val.size() > 4)
            {
                throw exception();
            }
            effect = val;
        }
        /** Access range
         * \return The current value of range
         */
        const double Getrange() const { return range; }
        /** Set range
         * \param val New value to set
         */
        void Setrange(double val) { range = val; }

        const string Getname() const { return name; }

        void Setname(string theName) { name = theName; }

        bool isAbleToFly()const { return canFly; }
        void setFly(bool val) { canFly = val;}
    protected:
    private:
        string name;
        bool canFly = false;
        int duration; //!< Member variable "duration"
        vector<double> effect; //!< Member variable "effect"
        double range; //!< Member variable "range"
        static int counter;
        void populatePower();
};

#endif // POWER_H
