#include <iostream>
#include <random>
#include <time.h>

#include "Location.h"
#include "Power.h"
#include "Super.h"
#include "TestSuper.h"
#include "TestPower.h"

using namespace std;

bool globalFlag = true;

void doTestCases();
void randomAppPlay();
void FromFileAppPlay();
void fillUpSuperList(int myRand, list<Super>& team);
list<Super> readSupersFromFile(string fileName);
void fight(list<Super>& teamA, list<Super>& teamB);
bool compareSupers(const Super& lhs, const Super& rhs);

/// random stuffs
default_random_engine gen;
uniform_int_distribution<int> distLoc;
uniform_real_distribution<double> distMinMax;
uniform_int_distribution<int> distInt;
normal_distribution<double> normDistEff;
normal_distribution<double> normDistAttr;

int main()
{
    gen.seed(time(nullptr));
    srand(time(nullptr));
    string str;
    int choice;
    while(globalFlag) {
        cout << "Choose From Menu: " << endl;
        cout << "1) Create random" << endl;
        cout << "2) Read from file" << endl;
        cout << "3) Go to test cases" << endl;
        cout << "Press -1 to quit" << endl;
        cout << "Please choose: ";
        getline(cin, str);
        stringstream(str) >> choice;
        switch(choice) {
        case 1:
            cout << "------ Your choice is 'Create random' ------" << endl;
            randomAppPlay();
            globalFlag = false;
            break;
        case 2:
            cout << "------ Your choice is 'Read From File' ------" << endl;
            FromFileAppPlay();
            globalFlag = false;
            break;
        case 3:
            cout << "------ Your choice is 'Test cases' ------" << endl;
            //flag = false;
            doTestCases();
            break;
        case -1:
            cout << "Quit the application" << endl;
            globalFlag = false;
            break;
        default:
            cout << "Please try again" << endl;
            break;
        }
    }
    return 0;
}

void doTestCases()
{
    string str;
    int choice;
    bool flag = true;
    while(flag) {
        cout << "Choose From Menu: " << endl;
        cout << "1) Test Super class" << endl;
        cout << "2) Test Power class" << endl;
        cout << "3) Go to main menu" << endl;
        cout << "Press -1 to quit" << endl;
        cout << "Please choose: ";
        getline(cin, str);
        stringstream(str) >> choice;
        switch(choice) {
            case 1:
                cout << "------ Your choice is 'Test Super class' ------" << endl;
                TestSuper::testAll();
                //flag = false;
                break;
            case 2:
                cout << "------ Your choice is 'Test Power class' ------" << endl;
                TestPower::testAll();
                //flag = false;
                break;
            case 3:
                cout << "------ Going back to main menu ------" << endl;
                flag = false;
                break;
            case -1:
                cout << "Quit the application" << endl;
                flag = false;
                globalFlag = false;
                break;
            default:
                cout << "Please try again" << endl;
                break;

        }
    }
}

bool compareSupers(const Super& lhs, const Super& rhs)
{
    return lhs.getSpeed() > rhs.getSpeed();
}

list<Super> readSupersFromFile(string fileName)
{
    fstream fin;
    double duraion, eff1, eff2, eff3, eff4, range;
    int locx, locy, locz;

    list<Super> team;
    list<Power> powers;
    vector<double> attr;

    Location* locptr;
    Super* superptr;
    Power* powerptr;
    //Equipment* eq;
    fin.open(fileName, ios::in);
    fin >> locx;
    while(!fin.eof())
    {
        fin >> locy;
        fin >> locz;
        locptr = new Location(locx, locy, locz);
        ///reading attributes (Strength, Endurance, Agility, Speed)
        fin >> eff1; fin >> eff2; fin >> eff3; fin >> eff4;
        superptr = new Super(false);
        attr.push_back(eff1);
        attr.push_back(eff2);
        attr.push_back(eff3);
        attr.push_back(eff4);
        superptr->Setattributes(attr);
        superptr->Setloc(*locptr);

        ///creating 3 powers
        for(int i = 0; i < 3; ++i)
        {
            fin >> duraion; fin >> eff1; fin >> eff2; fin >> eff3; fin >> eff4; fin >> range;
            powerptr = new Power(duraion, eff1, eff2, eff3, eff4, range);
            powers.push_back(*powerptr);
        }
        superptr->Setpowers(powers);
        team.push_back(*superptr);

        ///cleaning up everything
        powers.clear();
        attr.clear();
        locptr = nullptr;
        powerptr = nullptr;
        superptr = nullptr;
        /// refeed
        fin >> locx;
    }
    fin.close();
    return team;

}
void FromFileAppPlay()
{
    list<Super> teamA = readSupersFromFile("feed_teamA.dat");
    list<Super> teamB = readSupersFromFile("feed_teamB.dat");
    fight(teamA, teamB);
}

void randomAppPlay()
{
    list<Super> teamA, teamB;

    //Super* superptr;
    cout << "Rolling the dice for number of supers in each team: "  << endl;
    int myRand = rand() % 5 + 1;

    cout << "Number of players in each team: " << myRand << endl << endl;

    fillUpSuperList(myRand, teamA);
    fillUpSuperList(myRand, teamB);
    fight(teamA, teamB);
}


void fillUpSuperList(int myRand, list<Super>& team)
{
    Super* superPtr;
    for(int i = 0; i < myRand; ++i)
    {
        superPtr = new Super();
        team.push_back(*superPtr);
        superPtr = nullptr;
    }
}

void fight(list<Super>& teamA, list<Super>& teamB)
{
    list<Super>::iterator itA, itB;
    //list<Super> oneRoundGame;
    cout << "------ Members in Team A ------" << endl << endl;
    for(itA = teamA.begin(); itA != teamA.end(); ++itA)
    {
        itA->displaySuper(true);
        itA->setTeamName("Team A");
        for(list<Super>::iterator itr = teamB.begin(); itr != teamB.end(); itr++)
        {
            itA->addTarget(&(*itr));
        }
        //std::this_thread::sleep_for (std::chrono::milliseconds(500));
    }

    cout << "------ Members in Team B ------" << endl << endl;
    for(itB = teamB.begin(); itB != teamB.end(); ++itB)
    {
        itB->displaySuper(true);
        itB->setTeamName("Team B");
        for(list<Super>::iterator itr = teamA.begin(); itr != teamA.end(); itr++)
        {
            itB->addTarget(&(*itr));
        }
        //std::this_thread::sleep_for (std::chrono::milliseconds(500));
    }
    //oneRoundGame.merge(teamA);
    //oneRoundGame.merge(teamB);
    //oneRoundGame.sort(compareSupers);
    teamA.sort(compareSupers);
    teamB.sort(compareSupers);
    cout << "-------- The Game Begins --------" << endl << endl;

    ///The first seed attack should be implemented
    bool flag = true;
    double diceResult;
    Super* attacker = nullptr;
    //it = oneRoundGame.begin();
    itA = teamA.begin();
    itB = teamB.begin();
    if(itA->getSpeed() == itB->getSpeed())
    {
        diceResult = rand() % 100 + 1;
        if(diceResult > 50)
        {
            attacker = (&(*itB));
            ++itB;
        } else {
            attacker = (&(*itA));
            ++itA;
        }
    }
    else if(itA->getSpeed() > itB->getSpeed())
    {
         attacker = (&(*itA));
         ++itA;
    }
    else
    {
        attacker = (&(*itB));
        ++itB;
    }
    attacker->attack();
    attacker->removeDead();
    if(attacker->Gettargets().size() <= 0)
    {
        flag = false;
        cout << "-------- The Game Ends --------" << endl << endl;
        cout << attacker->getTeamName() << " Wins " << endl;
    }
    int tempStop, roundCount =1;
    while(flag) {
        while(itA != teamA.end() && itB != teamB.end())
        {
            if(itA->getSpeed() == itB->getSpeed())
            {
                diceResult = rand() % 100 + 1;
                if(diceResult > 50)
                {
                    //attacker = (&(*itB));
                    itB->removeDead();
                    if(itB->Gettargets().size() <= 0)
                    {
                        flag = false;
                        tempStop = -1;
                        cout << "-------- The Game Ends --------" << endl << endl;
                        cout << itB->getTeamName() << " Wins " << endl;
                        break;
                    }
                    if(itB->isAlive() == false) {
                        cout << "-------- " << itB->Getid() << " is dead --------" << endl << endl;
                        teamB.erase(itB++);
                    }
                    else
                    {
                        itB->attack();
                        //std::this_thread::sleep_for (std::chrono::milliseconds(200));
                        ++itB;
                    }

                } else {
                    //attacker = (&(*itA));
                    itA->removeDead();
                    if(itA->Gettargets().size() <= 0)
                    {
                        flag = false;
                        tempStop = -1;
                        cout << "-------- The Game Ends --------" << endl << endl;
                        cout << itA->getTeamName() << " Wins " << endl;
                        break;
                    }
                    if(itA->isAlive() == false) {
                        cout << "-------- " << itA->Getid() << " is dead --------" << endl << endl;
                        teamA.erase(itA++);
                    }
                    else
                    {
                        itA->attack();
                        //std::this_thread::sleep_for (std::chrono::milliseconds(200));
                        ++itA;
                    }
                }
            }
            else if(itA->getSpeed() > itB->getSpeed())
            {
                itA->removeDead();
                if(itA->Gettargets().size() <= 0)
                {
                    flag = false;
                    tempStop = -1;
                    cout << "-------- The Game Ends --------" << endl << endl;
                    cout << itA->getTeamName() << " Wins " << endl;
                    break;
                }
                if(itA->isAlive() == false) {
                     cout << "-------- " << itA->Getid() << " is dead --------" << endl << endl;
                     teamA.erase(itA++);
                }
                else
                {
                     itA->attack();
                     //std::this_thread::sleep_for (std::chrono::milliseconds(200));
                     ++itA;
                }
            }
            else
            {
                itB->removeDead();
                if(itB->Gettargets().size() <= 0)
                {
                    flag = false;
                    tempStop = -1;
                    cout << "-------- The Game Ends --------" << endl << endl;
                    cout << itB->getTeamName() << " Wins " << endl;
                    break;
                }
                if(itB->isAlive() == false) {
                     cout << "-------- " << itB->Getid() << " is dead --------" << endl << endl;
                     teamB.erase(itB++);
                }
                else
                {
                     itB->attack();
                     //std::this_thread::sleep_for (std::chrono::milliseconds(200));
                     ++itB;
                }
            }
        }

        //oneRoundGame.sort(compareSupers);
        /// take care of the rest of the team members
        /// that did not have the chance to get their turns
        if(itA != teamA.end())
        {
            while(itA != teamA.end())
            {
                itA->removeDead();
                if(itA->Gettargets().size() <= 0)
                {
                    flag = false;
                    tempStop = -1;
                    cout << "-------- The Game Ends --------" << endl << endl;
                    cout << itA->getTeamName() << " Wins " << endl;
                    break;
                }
                if(itA->isAlive() == false) {
                     cout << "-------- " << itA->Getid() << " is dead --------" << endl << endl;
                     teamA.erase(itA++);
                }
                else
                {
                     itA->attack();
                     //std::this_thread::sleep_for (std::chrono::milliseconds(200));
                     ++itA;
                }
            }
        }
        else if(itB != teamB.end())
        {
            while(itB != teamB.end())
            {
                itB->removeDead();
                if(itB->Gettargets().size() <= 0)
                {
                    flag = false;
                    tempStop = -1;
                    cout << "-------- The Game Ends --------" << endl << endl;
                    cout << itB->getTeamName() << " Wins " << endl;
                    break;
                }
                if(itB->isAlive() == false) {
                     cout << "-------- " << itB->Getid() << " is dead --------" << endl << endl;
                     teamB.erase(itB++);
                }
                else
                {
                     itB->attack();
                     //std::this_thread::sleep_for (std::chrono::milliseconds(200));
                     ++itB;
                }
            }
        }
        /// after the round maybe the powers made supers lose their speed that's why
        /// it needs to be sorted. not necessarily need to be sorted! even if they were not sorted,
        /// the algorithm should take care of the fastest super!
        teamA.sort(compareSupers);
        teamB.sort(compareSupers);
        /// we set the pointers back to the beginning for the next round
        itA = teamA.begin();
        itB = teamB.begin();

        if(!teamA.size() <= 0 && !teamB.size() <=0 && tempStop != -1)
        {
            cout << "This is a pause to see the fight result for the round --- " << roundCount << " ---!" << endl;
            cout << "Please enter any value to continue the fight or -1 if you want no more pause!" << endl;
            roundCount++;
            cin >> tempStop;
        }
    }

}
