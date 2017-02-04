#include "TestEquipment.h"

TestEquipment::TestEquipment()
{
    //ctor
}

TestEquipment::~TestEquipment()
{
    //dtor
}

void TestEquipment::testAll(default_random_engine& gen)
{
    testDisplayEquipment(gen);
    testPopulatePowers(gen);
    testAddPower(gen);
    cout << endl << endl;
}

void TestEquipment::testPopulatePowers(default_random_engine& gen)
{
    cout << "-------- Testing Equipment populatePowers Method --------" << endl;
    cout << "-------- Generate list of random powers #1: " << endl;
    Equipment eq(gen,false);
    eq.populatePowers(gen);
    eq.displayEquipment();
    cout << "-------- Generate list of random powers #2: " << endl;
    Equipment eq2(gen,false);
    eq2.populatePowers(gen);
    eq2.displayEquipment();
    cout << endl;
}

void TestEquipment::testAddPower(default_random_engine& gen)
{
    cout << "-------- Testing Equipment AddPower Method --------" << endl;
    Equipment eq(gen, false);
    cout << "Before Adding the power-------------------" << endl;
    eq.displayEquipment();
    cout << "After Adding the power-------------------" << endl;
    Power pow(gen);
    eq.addPower(&pow);
    eq.displayEquipment();
    cout << endl;
}

void TestEquipment::testDisplayEquipment(default_random_engine& gen)
{
    cout << "-------- Testing Equipment display Method --------" << endl;

    Equipment eq(gen);
    eq.displayEquipment();
    cout << endl;
}
