#include "TestPower.h"

TestPower::TestPower()
{
    //ctor
}

TestPower::~TestPower()
{
    //dtor
}

void TestPower::testAll()
{
    testDisplayPower();
    testGetduration();
    testGeteffect();
    testGetrange();
    testGetname();
    testPopulatePower();

    cout << endl << endl;
}

void TestPower::testDisplayPower()
{
    cout << "-------- Testing Power display Method --------" << endl;

    Power pow;
    pow.Setname("Power #1");
    pow.Setduration(3);
    pow.Setrange(25.5);
    vector<double> effects { 10, -5, 4, -2 };
    pow.Seteffect(effects);

    cout << "-------- Expected Result: " << endl;
    cout << "Power #1: Effects: ( 10 -5 4 -2 ), Duration: 3, Range: 25.5"<< endl;

    cout << "-------- Result: " << endl;
    pow.displayPower();
    cout << endl;
}

void TestPower::testGetduration()
{
    cout << "-------- Testing Power Duration setter and getter Method --------" << endl;

    Power pow;
    pow.Setduration(3);

    cout << "-------- Expected Result: 3" << endl;
    cout << "-------- Result: " << pow.Getduration() << endl << endl;

}


void TestPower::testGeteffect()
{
    cout << "-------- Testing Power Effect setter and getter Method --------" << endl;

    Power pow;
    vector<double> effects { 10, -5, 4, -2 };
    pow.Seteffect(effects);
    cout << "-------- Expected Result: ( 10 -5 4 -2 )"<< endl;
    cout << "-------- Result: ";
    cout << "( " << pow.Geteffect()[0] << " " << pow.Geteffect()[1] << " "
              <<  pow.Geteffect()[2] << " " << pow.Geteffect()[3] << " )" << endl << endl;
}

void TestPower::testGetrange()
{
    cout << "-------- Testing Power range setter and getter Method --------" << endl;
    Power pow;
    pow.Setrange(25);

    cout << "-------- Expected Result: 25" << endl;
    cout << "-------- Result: " << pow.Getrange() << endl << endl;
}


void TestPower::testGetname()
{
    cout << "-------- Testing Power Name getter and setter Method --------" << endl;

    Power pow;
    pow.Setname("Power #1");
    cout << "-------- Expected Result: Power #1" << endl;
    cout << "-------- Result: " << pow.Getname() << endl << endl;
}

void TestPower::testPopulatePower()
{
    cout << "-------- Testing Power PopulatePower() Method --------" << endl;

    Power pow;
    pow.Setname("Power #1");
    pow.populatePower();
    cout << "Generating Random Result #1: " << endl;
    pow.displayPower();

    Power pow2;
    pow2.Setname("Power #2");
    pow2.populatePower();
    cout << "Generating Random Result #2: " << endl;
    pow2.displayPower();
    cout << endl;
}
