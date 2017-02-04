#include "TestSuper.h"

TestSuper::TestSuper()
{
    //ctor
}

TestSuper::~TestSuper()
{
    //dtor
}

void TestSuper::testAll()
{
    testGetDeltaValues();
    testCalculateDistance();
    testIsHit();
    testComputeDamage();
    testDamageTarget();
    testMoveForward();
    testMoveForward_2();
    testAttackTarget();
    testFindTheClosestTarget();
    testUseRandomPowerOrEquipment();
    testEffectPower();
    testIneffectPower();
    cout << "-------- You can also see the result in 'test_output.dat' --------" << endl << endl;
}

void TestSuper::testGetDeltaValues()
{
    fstream fout("test_output.dat", ios::out);
    if (fout.is_open()) {
        cout << "-------- Testing GetDeltaValues --------" << endl;
        fout << "-------- Testing GetDeltaValues --------" << endl;
        Super hero;
        Location loc1(50, 50, 50);
        hero.Setloc(loc1);
        vector<double> attr {50, 60, 70, 80};
        hero.Setattributes(attr);

        Super target;
        Location loc2(0, 100, 50);
        target.Setloc(loc2);
        vector<double> attr2 {60, 60, 80, 50};
        target.Setattributes(attr2);

        hero.addTarget(&target);

        vector<double> deltas = hero.getDeltaValues(target.Getloc());
        cout << "Expected Value: (-50, 50, 0)" << endl;
        fout << "Expected Value: (-50, 50, 0)" << endl;
        cout << "Result: (" << deltas[0] << ", " << deltas[1] << ", "
                                            << deltas[2] <<")" << endl << endl;
        fout << "Result: (" << deltas[0] << ", " << deltas[1] << ", "
                                            << deltas[2] <<")" << endl << endl;

    }
}

void TestSuper::testCalculateDistance()
{
    ofstream fout("test_output.dat", ios::app);
    if (fout.is_open()) {
        cout << "-------- Testing Calculate Distance --------" << endl;
        fout << "-------- Testing Calculate Distance --------" << endl;
        Super hero;
        Location loc1(50, 50, 50);
        hero.Setloc(loc1);
        vector<double> attr {50, 60, 70, 80};
        hero.Setattributes(attr);

        Super target;
        Location loc2(0, 100, 50);
        target.Setloc(loc2);
        vector<double> attr2 {60, 60, 80, 50};
        target.Setattributes(attr2);

        hero.addTarget(&target);

        vector<double> deltas = hero.getDeltaValues(target.Getloc());
        double distance = hero.calculateDistance(deltas);
        cout << "Hero ";
        hero.Getloc().displayLocation();
        cout << "Target#1 ";
        target.Getloc().displayLocation();
        cout << "Expected Value: 70.7107" << endl;
        fout << "Expected Value: 70.7107" << endl;
        cout << "Result: " << distance << endl << endl;
        fout << "Result: " << distance << endl << endl;

        Location loc3(-100, -100, -100);
        target.Setloc(loc3);
        deltas = hero.getDeltaValues(target.Getloc());
        distance = hero.calculateDistance(deltas);
        cout << "Hero ";
        hero.Getloc().displayLocation();
        cout << "Target#2 ";
        target.Getloc().displayLocation();
        cout << "Expected Value: 259.808" << endl;
        fout << "Expected Value: 259.808" << endl;
        cout << "Result: " << distance << endl << endl;
        fout << "Result: " << distance << endl << endl;
    }
}

void TestSuper::testComputeDamage()
{
    ofstream fout("test_output.dat", ios::app);
    if (fout.is_open()) {
        cout << "-------- Testing Compute Damage --------" << endl;
        fout << "-------- Testing Compute Damage --------" << endl;
        Super hero;
        Location loc1(50, 50, 50);
        hero.Setloc(loc1);
        vector<double> attr {50, 60, 70, 80};
        hero.Setattributes(attr);

        Super target;
        target.Setid("Target #1");
        Location loc2(0, 100, 50);
        target.Setloc(loc2);
        vector<double> attr2 {60, 60, 80, 50};
        target.Setattributes(attr2);

        hero.addTarget(&target);

        double damage = hero.computeDamage(target.Getattributes());
        cout << "Expected Value: 3.2" << endl;
        fout << "Expected Value: 3.2" << endl;
        cout << "Result: " << damage << endl << endl;
        fout << "Result: " << damage << endl << endl;
    }
}

void TestSuper::testDamageTarget()
{
    ofstream fout("test_output.dat", ios::app);
    if (fout.is_open()) {
        cout << "-------- Testing Damage Target --------" << endl;
        fout << "-------- Testing Damage Target --------" << endl;
        Super hero;
        Location loc1(50, 50, 50);
        hero.Setloc(loc1);
        vector<double> attr {50, 60, 70, 80};
        hero.Setattributes(attr);

        Super target;
        target.Setid("Target #1");
        Location loc2(0, 100, 50);
        target.Setloc(loc2);
        vector<double> attr2 {60, 60, 80, 50};
        target.Setattributes(attr2);

        hero.addTarget(&target);

        double damage = hero.computeDamage(target.Getattributes());
        double result = target.getEndurance() - damage;
        hero.damageTarget(target);
        cout << "Expected Value: 56.8" << endl;
        fout << "Expected Value: 56.8" << endl;
        cout << "Result: " << result << endl << endl;
        fout << "Result: " << result << endl << endl;
    }
}

void TestSuper::testIsHit()
{
    ofstream fout("test_output.dat", ios::app);
    if (fout.is_open()) {
        cout << "-------- Testing Is Hit Target --------" << endl;
        fout << "-------- Testing Is Hit Target --------" << endl;
        Super hero;
        Location loc1(50, 50, 50);
        hero.Setloc(loc1);
        vector<double> attr {50, 60, 70, 80};
        hero.Setattributes(attr);

        Super target;
        target.Setid("Target #1");
        Location loc2(0, 100, 50);
        target.Setloc(loc2);
        vector<double> attr2 {60, 60, 80, 50};
        target.Setattributes(attr2);

        hero.addTarget(&target);
        bool isHit = hero.isHit(target);
        cout << "Is hit Trial #1" << endl;
        fout << "Is hit Trial #1" << endl;
        cout << "Result: " << isHit << endl;
        fout << "Result: " << isHit << endl;
        isHit = hero.isHit(target);
        cout << "Is hit Trial #2" << endl;
        fout << "Is hit Trial #2" << endl;
        cout << "Result: " << isHit << endl;
        fout << "Result: " << isHit << endl;
        isHit = hero.isHit(target);
        cout << "Is hit Trial #3" << endl;
        fout << "Is hit Trial #3" << endl;
        cout << "Result: " << isHit << endl;
        fout << "Result: " << isHit << endl;
        isHit = hero.isHit(target);
        cout << "Is hit Trial #4" << endl;
        fout << "Is hit Trial #4" << endl;
        cout << "Result: " << isHit << endl;
        fout << "Result: " << isHit << endl;
        isHit = hero.isHit(target);
        cout << "Is hit Trial #5" << endl;
        fout << "Is hit Trial #5" << endl;
        cout << "Result: " << isHit << endl << endl;
        fout << "Result: " << isHit << endl << endl;
    }
}

void TestSuper::testFindTheClosestTarget()
{
    ofstream fout("test_output.dat", ios::app);
    if (fout.is_open()) {
        cout << "-------- Testing Find the closest target --------" << endl;
        fout << "-------- Testing Find the closest target --------" << endl;

        Super hero;
        hero.Setid("Hero #1");
        Location loc1(50, 50, 50);
        hero.Setloc(loc1);

        Super target;
        target.Setid("Target #1");
        Location loc2(0, 150, 50);
        target.Setloc(loc2);

        Super target2;
        target2.Setid("Target #2");
        Location loc3(0, 150, 50);
        target2.Setloc(loc3);

        Super target3;
        target3.Setid("Target #3");
        Location loc4(0, 150, 50);
        target3.Setloc(loc4);

        hero.addTarget(&target);
        hero.addTarget(&target2);
        hero.addTarget(&target3);

        Super& t = hero.findTheClosestTarget();
        cout << "Result: " << t.Getid() << endl;
        fout << "Result: " << t.Getid() << endl;
        t.Getloc().displayLocation();
        cout << endl << endl;
    }
}

void TestSuper::testUseRandomPowerOrEquipment()
{
    ofstream fout("test_output.dat", ios::app);
    if (fout.is_open()) {
        cout << "-------- Testing UseRandomPowerOrEquipment --------" << endl;
        fout << "-------- Testing UseRandomPowerOrEquipment --------" << endl;
        Super hero;
        hero.Setid("Hero #1");
        Location loc1(50, 50, 50);
        hero.Setloc(loc1);
        vector<double> attr {50, 60, 70, 80};
        hero.Setattributes(attr);
        Power pow;
        pow.Setname("power #1");
        pow.Setduration(3);
        pow.Setrange(20);
        vector<double> effects {10, 10, -5, -5};
        pow.Seteffect(effects);
        hero.addPower(&pow);
        Power eq;
        hero.addEquipment(&eq);
        cout << "Result: " << endl;
        fout << "Result: " << endl;
        hero.useRandomPowerOrEquipment();
        cout << endl << endl;
    }
}

void TestSuper::testEffectPower()
{

}

void TestSuper::testIneffectPower()
{

}


void TestSuper::testMoveForward()
{
    ofstream fout("test_output.dat", std::ios_base::app);
    fout << "-------- Testing Move towards Target#1 --------" << endl;
    cout << "-------- Testing Move towards Target#1 --------" << endl;
    Super hero;
    Location loc1(0, 100, 50);
    hero.Setloc(loc1);
    vector<double> attr {50, 60, 70, 80};
    hero.Setattributes(attr);

    Super target;
    Location loc2(0, 100, 50);
    target.Setloc(loc2);
    vector<double> attr2 {60, 60, 80, 50};
    target.Setattributes(attr2);

    hero.addTarget(&target);
    cout << "Hero ";
    hero.Getloc().displayLocation();
    cout << "Target ";
    target.Getloc().displayLocation();
    cout << endl;
    bool needTomove = hero.moveTowardTarget(target.Getloc(), 10, true);
    fout << "******* Expected result: 1 \n******* Result: " <<  needTomove << endl <<endl;
    cout << "******* Expected result: 1 \n******* Result: " <<  needTomove << endl << endl;

}

void TestSuper::testMoveForward_2()
{
    ofstream fout("test_output.dat", std::ios_base::app);
    if (fout.is_open()) {
        cout << "-------- Testing Move towards Target#2 --------" << endl;
        fout << "-------- Testing Move towards Target#2 --------" << endl;
        Super hero;
        Location loc1(0, 0, 0);
        hero.Setloc(loc1);
        vector<double> attr {50, 60, 70, 80};
        hero.Setattributes(attr);

        Super target;
        Location loc2(0, 100, 50);
        target.Setloc(loc2);
        vector<double> attr2 {60, 60, 80, 50};
        target.Setattributes(attr2);

        hero.addTarget(&target);
        cout << "Hero ";
        hero.Getloc().displayLocation();
        cout << "Target ";
        target.Getloc().displayLocation();
        cout << endl;
        bool needTomove = hero.moveTowardTarget(target.Getloc(), 10, true);
        cout << "******* Expected result: 0 \n******* Result: " <<  needTomove << endl;
        fout << "******* Expected result: 0 \n******* Result: " <<  needTomove << endl;
    }
}

void TestSuper::testAttackTarget()
{
    ofstream fout("test_output.dat", ios::app);
    if (fout.is_open()) {
        cout << "-------- Testing Attack Target --------" << endl;
        fout << "-------- Testing Atatck Target --------" << endl;
        Super hero;
        hero.Setid("Hero #1");
        Location loc1(50, 50, 50);
        hero.Setloc(loc1);
        vector<double> attr {50, 60, 70, 80};
        hero.Setattributes(attr);
        Power pow;
        pow.Setname("power #1");
        pow.Setduration(3);
        pow.Setrange(20);
        vector<double> effects {10, 10, -5, -5};
        pow.Seteffect(effects);
        hero.addPower(&pow);

        Super target;
        target.Setid("Target #1");
        Location loc2(0, 100, 50);
        target.Setloc(loc2);
        vector<double> attr2 {60, 60, 80, 50};
        target.Setattributes(attr2);

        hero.addTarget(&target);
        Power power2 = hero.useRandomPowerOrEquipment();
        cout << "Trial #1" << endl;
        fout << "Trial #1" << endl;
        hero.attackTarget(target, power2.Getrange(), power2.isAbleToFly());
        cout << "Trial #2" << endl;
        fout << "Trial #2" << endl;
        power2 = hero.useRandomPowerOrEquipment();
        hero.attackTarget(target, power2.Getrange(), power2.isAbleToFly());
        cout << "Trial #3" << endl;
        fout << "Trial #3" << endl;
        power2 = hero.useRandomPowerOrEquipment();
        hero.attackTarget(target, power2.Getrange(), power2.isAbleToFly());

        cout << endl << endl;
    }
}
