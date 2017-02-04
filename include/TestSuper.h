#ifndef TESTSUPER_H
#define TESTSUPER_H

#include <random>
#include "Super.h"
#include <fstream>

class TestSuper
{
    public:
        /** Default constructor */
        TestSuper();
        /** Default destructor */
        virtual ~TestSuper();

        static void testAll();
        static void testMoveForward();
        static void testMoveForward_2();
        static void testCalculateDistance();
        static void testGetDeltaValues();
        static void testDamageTarget();
        static void testIsHit();
        static void testComputeDamage();
        static void testAttackTarget();
        static void testFindTheClosestTarget();
        static void testUseRandomPowerOrEquipment();
        static void testEffectPower();
        static void testIneffectPower();
};

#endif // TESTSUPER_H
