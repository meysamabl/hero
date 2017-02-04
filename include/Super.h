#ifndef SUPER_H
#define SUPER_H

#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include "Power.h"
#include "Location.h"
#include "RandomGeneratorHelper.h"

using namespace std;


class Super
{
    friend class TestSuper;
    public:
        Super(bool autoGenerate = true);
        Super(string id, bool autoGenerate = true);
        virtual ~Super();
        void attack();
        void removeDead();
        void displaySuper(bool showPowers = false);
        void addTarget(Super* target);
        void addPower(Power* pow);
        void addEquipment(Power* eq);
        double getEndurance() const { return attributes[1]; }
        double getSpeed() const { return attributes[3]; }

        /// overloaded to be able to do sort function
        bool operator< (const Super& rh)
        {
            return attributes[3] < rh.attributes[3];
        }

        bool operator== (const Super& rhs)
        {
            return id == rhs.id;
        }

        ///getter and setters----------------------------------
        string Getid() const { return id; }

        void Setid(string val) { id = val; }

        Location Getloc() const { return loc; }

        void Setloc(Location val) { loc = val; }

        vector<double> Getattributes() const { return attributes; }

        void Setattributes(vector<double> val) { attributes = val; }

        list<Power> Getpowers() const { return powers; }

        void Setpowers(list<Power> val) { powers = val; }

        list<Power> Getequipments() const { return equipments; }

        void Setequipments(list<Power> val) { equipments = val; }

        list<Super*>& Gettargets() { return targets; }

        void Settargets(list<Super*>& val) { targets = val; }

        bool isAlive() const { return alive;}
        void setAlive(bool val) { alive = val;}

        string getTeamName() const { return teamName;}
        void setTeamName(string val) { teamName = val;}
    protected:
    private:
        static int counter;
        string id;
        Location loc;
        list<Power> powerInUse;
        list<Power> powerEffected;
        /*
            The attributes are as follow:
            attributes[0] = Strength,
            attributes[1] = Endurance,
            attributes[2] = Agility,
            attributes[3] = Speed

            We assume the aggregate of all the attributes
            is equal to 400 to play fair;
        */
        vector<double> attributes;
        list<Power> powers;
        list<Power> equipments;
        list<Super*> targets;
        bool alive = true;
        string teamName;
        ///private methods
        bool moveTowardTarget(const Location& targetLoc, const double range, const bool canFly);

        bool isWithinTheRange(const double distance, const double range);

        double calculateDistance(const vector<double> deltaValues);

        const vector<double> getDeltaValues(const Location& targetLoc);

        void damageTarget(Super& target);

        bool isHit(const Super& target);

        double computeDamage(const vector<double>& targetAttr);

        void attackTarget(Super& target, const double range, const bool canFly, Power pow = Power(false));

        Super& findTheClosestTarget();

        Power useRandomPowerOrEquipment();

        void useRandomPowerOrEquipmentOnTarget(Power& pow, Super& target);

        void effectPower(Power& power);

        void effectPowerOnTarget(Power& power, Super& target);

        void ineffectPowerOnTarget(Super& target);

        void ineffectPower();

        Power& chooseRandomPower();

        Power getFinalRandomPower();

        Power& chooseRandomEquipment();

        void populatePower(list<Power>& pows);

        bool isPowerInUser(const Power& power);

        bool isPowerEffectedInUse(const Power& pow, Super& target);

};

#endif // SUPER_H
