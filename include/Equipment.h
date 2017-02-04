#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <list>
#include <string>
#include "Power.h"
#include "RandomGeneratorHelper.h"
#include <iostream>

using namespace std;

class Equipment
{
    friend class TestEquipment;
    public:
        /** Default constructor */
        Equipment(default_random_engine& gen, bool autoGenerate = true);

        Equipment(default_random_engine& gen, string name, bool autoGenerate = true);
        /** Default destructor */
        virtual ~Equipment();

        bool operator== (const Equipment& rhs)
        {
            return name == rhs.name;
        }
        /// Accessors and mutators -----------------
        /** Access powers
         * \return The current value of powers
         */
        list<Power> Getpowers() { return powers; }
        /** Set powers
         * \param val New value to set
         */
        void Setpowers(list<Power> val) { powers = val; }
        void addPower(Power* pow);
        //void removePower();
        void displayEquipment();
    protected:
    private:
        static int counter;
        string name;
        list<Power> powers; //!< Member variable "powers"
        void populatePowers(default_random_engine& gen);
};

#endif // EQUIPMENT_H
