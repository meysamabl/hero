#include "Super.h"

int Super::counter = 1;

Super::Super(bool autoGenerate)
{
    std::ostringstream ss;
    ss << counter;
    id = "Super #" + ss.str();
    counter++;
    if(autoGenerate)
    {
        Location * locPtr = new Location();
        loc = *locPtr;
        locPtr = nullptr;
        attributes = RandomGeneratorHelper::generateRandomAttributes(50, 15);
        populatePower(powers);
        populatePower(equipments);
    }
}

Super::Super(string id, bool autoGenerate) : id(id)
{
    if(autoGenerate)
    {
        Location * locPtr = new Location();
        loc = *locPtr;
        attributes = RandomGeneratorHelper::generateRandomAttributes(50, 15);
        populatePower(powers);
        populatePower(equipments);
    }
}

Super::~Super()
{
    powers.clear();
    equipments.clear();
    targets.clear();
    //cout << "Super destructor called" <<endl;
}

void Super::addTarget(Super* target)
{
    targets.push_back(target);
}

void Super::displaySuper(bool showPowers)
{
    cout << id << " from " << teamName << ": Strength: " << attributes[0] << ", Endurance: " << attributes[1]
                            << ", Agility: " << attributes[2] << ", Speed: " << attributes[3] <<endl;
    if(!showPowers) { return; }
    cout << "---- Location ----" <<endl;
    loc.displayLocation();
    cout << "---- List of Powers ----" <<endl;
    for(list<Power>::iterator it = powers.begin(); it != powers.end(); ++it)
    {
        it->displayPower();
    }
    cout << "---- List of Equipments ----" <<endl;
    for(list<Power>::iterator it = equipments.begin(); it != equipments.end(); ++it)
    {
        it->displayPower();
    }
    cout << endl;
}

void Super::removeDead()
{
    list<Super*>::iterator it = targets.begin();
    while(it != targets.end())
    {
        if((*it)->isAlive() == false) {
            targets.erase(it++);
        }
        else { ++it;}
    }
}

void Super::attack()
{
    if(targets.size() <= 0)
    {
        cout << "No more target. Victory!!" << endl;
        return;
    }
    Super& target = findTheClosestTarget();
    double diceResult = RandomGeneratorHelper::rollTheDice();
    /// ----------------- Check if older powers in use have still the ability to fly
    bool isAbleToFly = false;
    for(list<Power>::iterator it = powerInUse.begin(); it != powerInUse.end(); ++it)
    {
        if(it->isAbleToFly()) { isAbleToFly = true; break;}
    }
    ///-------------------------------------------------------
    if(diceResult > 50)
    {
        cout << "Dice decides to effect the random power on the target" << endl;
        Power pow = getFinalRandomPower();
        /// check if the power chosen is able to fly and if yes then we are able to fly
        /// else will be the result of our old powers in use
        isAbleToFly = pow.isAbleToFly() == true ? true : isAbleToFly;
        attackTarget(target, pow.Getrange(), isAbleToFly, pow);
    }
    else
    {
        cout << "Dice decides to effect the random power on the super himself" << endl;
        Power pow = useRandomPowerOrEquipment();
        /// check if the power chosen is able to fly and if yes then we are able to fly
        /// else will be the result of our old powers in use
        isAbleToFly = pow.isAbleToFly() == true ? true : isAbleToFly;
        attackTarget(target, pow.Getrange(), isAbleToFly);
    }
    /// target dies if the endurance is less than zero
    /// then set the flag to false;
    if(target.getEndurance() <= 0)
    {
        target.setAlive(false);
    }
}

Super& Super::findTheClosestTarget()
{
    list<Super*>::iterator it = targets.begin();


    /// temp vector to keep track of more than one occurances;
    it = targets.begin();
    vector<Super*> occurances;
    double tempDist;
    double minDist = calculateDistance(getDeltaValues((*it)->Getloc()));
    occurances.push_back(*it);
    it++;
    while(it != targets.end())
    {
        tempDist = calculateDistance(getDeltaValues((*it)->Getloc()));
        if(tempDist <= minDist)
        {
            if(tempDist == minDist)
            {
                cout << "Wow! targets at the same distance. Such a coincidence!" << endl;
                occurances.push_back(*it);
            }
            else
            {
                minDist = tempDist;
                occurances.clear();
                occurances.push_back(*it);
            }
        }
        ++it;
    }
    Super* superptr;
    /// in case two supers are in the same distance we randomly select one
    if(occurances.size() > 1)
    {
        int rand = RandomGeneratorHelper::generateRandomInt( 0,occurances.size());
        cout << "Rolling dice to choose the closest target" << endl;
        superptr = occurances[rand];
    } else {
        superptr = occurances[0];
    }
    return (*superptr);
}

void Super::attackTarget(Super& target, const double range, const bool canFly, Power pow)
{
    cout << id << " is attacking now!" << endl;
    cout << "Target ";
    target.displaySuper();
    bool canHit = moveTowardTarget(target.Getloc(), range, canFly);
    if(canHit)
    {
        /// if can hit, then we are within the range to use the power on
        /// our target!! that makes sense!
        if(pow.Getrange() >= 0)
        {
            /// we are using our power on our target here
            useRandomPowerOrEquipmentOnTarget( pow, target);
        }
        if(isHit(target))
        {
            damageTarget(target);
        }
        else
        {
            cout << "Oops! The target dodged!" << endl << endl;
        }
    }
}

bool Super::isHit(const Super& target)
{
    ///50+(atk(speed + agility) – def(speed +agility))
    double comparisonVal = 50 + ((attributes[3] + attributes[2]) -
                                (target.Getattributes()[3] + target.Getattributes()[2]));
    return comparisonVal <= RandomGeneratorHelper::rollTheDice();
    //return comparisonVal > 65;
}

double Super::computeDamage(const vector<double>& targetAttr)
{

    /// raw damage = (50+(atk(str+spd) – def(agility+endurance)))
    double rawDamage = 50 + (attributes[0] + attributes[3]) - (targetAttr[2] + targetAttr[1]);
    /// Damage = RawDam*(100+atk(endurance))/2000
    double damage = rawDamage * (100 + attributes[1]) / 2000;
    return floor((damage + 0.005) * 100) / 100;
}

void Super::damageTarget(Super& target)
{
    vector<double> targetAttr = target.Getattributes();
    double damage = computeDamage(targetAttr);
    cout << "calculating the damage after attack... " << endl;
    if(damage > 0)
    {
        targetAttr[1] = targetAttr[1] - damage;
        target.Setattributes(targetAttr);
        cout<< "Damage: " << damage << ", The target " << target.Getid() <<
                "'s Endurance reduced to " <<  target.getEndurance() << endl << endl;
        //target.displaySuper();
    }
    else
    {
        cout << "The target " << target.Getid() << " was not damaged!" << endl << endl;
    }
}

bool Super::moveTowardTarget(const Location& targetLoc, const double range, const bool canFly)
{
    cout<<"Super's initial position: ("<<loc.Getx()<<", "<<loc.Gety()<<", "<<loc.Getz()<<")"<<endl;
    cout << "Super can fly? " << canFly << endl;
    if(canFly == true && loc.Getz() <95)
    {
        loc.Setz(loc.Getz()+ 5);
    }
    else if(!canFly)
    {
        if(loc.Getz() - 10 >= 0) {
            loc.Setz(loc.Getz() - 10);
        } else {
            loc.Setz(0);
        }
        cout << "Since super can not fly, then its Z location changes slowly to zero" << endl;
    }
    cout<<"Target's position: ("<<targetLoc.Getx()<<", "<<targetLoc.Gety()<<", "<<targetLoc.Getz()<<")"<<endl;
    //cout<<"Range: "<<range<<endl;
    double distance;
    vector<double> deltaValues = getDeltaValues(targetLoc);
    distance = calculateDistance(deltaValues);
    cout<<"Distance to target "<<distance<<endl;
    if(isWithinTheRange(distance,range))
    {
        cout<<"No need to move, Target is already within the range"<<endl;
        return true;
    }
    else
    {
        double speed = this->attributes[3];
        double t;
        /// calculating fake ground speed
        if(canFly == true)
        {
           speed = floor(((1 + (loc.Getz()/100)) * speed) * 100)/100;
        }
        double diceResult;
        cout<<"Super's speed: "<<speed<<endl;
        if((speed+range)< distance)
        {
            /// we roll the dice if we want to move towards our target or not
            diceResult = RandomGeneratorHelper::rollTheDice();
            cout << "The target is not within the range, no combat possible"<<endl;
            cout << "Rolling the dice whether to move or stay put" << endl;
            cout << "Dice Result: " << diceResult << endl;
            if(diceResult >= 50)
            {
                cout<<"Dice decides the super to move"<<endl;
                t = speed / distance;
                loc.Setx(floor(((loc.Getx() + deltaValues[0] * t) + 0.005) * 100) / 100);
                loc.Sety(floor(((loc.Gety() + deltaValues[1] * t) + 0.005) * 100) / 100);
                if(canFly)
                    loc.Setz(floor(((loc.Getz() + deltaValues[2] * t) + 0.005) * 100) / 100);
                cout<<"Super's new position: ("<<loc.Getx()<<", "<<loc.Gety()<<", "<<loc.Getz()<<")"<<endl << endl;
            }
            else
            {
                cout<<"Dice decides the super to stay put"<<endl << endl;
            }
            return false;
        }
        else
        {
            cout<<"After the move, target is within the range, Bingo!"<< endl;
            t = (distance - range) / distance;
            loc.Setx(floor(((loc.Getx() + deltaValues[0] * t) + 0.005) * 100) / 100);
            loc.Sety(floor(((loc.Gety() + deltaValues[1] * t) + 0.005) * 100) / 100);
            if(canFly)
                loc.Setz(floor(((loc.Getz() + deltaValues[2] * t) + 0.005) * 100) / 100);
            cout<<"Super's new position: ("<<loc.Getx()<<", "<<loc.Gety()<<", "<<loc.Getz()<<")"<<endl;
            return true;
        }

    }
}

bool Super::isWithinTheRange(const double distance, const double range)
{
    return range >= distance;
}

/// this method calculate the distance by passing the delta values
/// of super's location and target's location
double Super::calculateDistance(const vector<double> deltaValues)
{
    double a = deltaValues[0];
    double b = deltaValues[1];
    double c = deltaValues[2];
    double d = sqrt(pow(a , 2.0) + pow(b , 2.0) + pow(c, 2.0));
    return d;
}

/// calculating the delta values of super's location and target's location
const vector<double> Super::getDeltaValues(const Location& targetLoc)
{
    vector<double> deltaValues;
    deltaValues.push_back(targetLoc.Getx() - loc.Getx());
    deltaValues.push_back(targetLoc.Gety() - loc.Gety());
    deltaValues.push_back(targetLoc.Getz() - loc.Getz());
    return deltaValues;
}

void Super::useRandomPowerOrEquipmentOnTarget(Power& pow, Super& target)
{
    cout<< "Target's attributes before being affected by the power: " << endl;
    target.displaySuper();
    ineffectPowerOnTarget(target);
    cout << pow.Getname() << " is chosen to be used on target" << endl;
    pow.displayPower();
    bool inUse = isPowerEffectedInUse(pow, target);
    if(!inUse) {
        effectPowerOnTarget(pow, target);
    } else {
        cout << pow.Getname() << " is already affected on target on previous round(s)!" << endl;
    }
    //cout<< "After Power effect: " << endl;
    //displaySuper();
    cout<< "Target's attributes after being affected by the power: " << endl;
    target.displaySuper();
}

void Super::effectPowerOnTarget(Power& power, Super& target)
{
    double str, endu, agil, spd;
    vector<double> attr = target.Getattributes();
    target.powerEffected.push_back(power);

    /// only effect the effects that have negative effect on the target
    /// meaning only the positive ones
    if(power.Geteffect()[0] > 0)
    {
        str = attr[0] - power.Geteffect()[0];
        /// if less than zero, then just set it to the minimum
        if(str > 0) { attr[0] = str;} else {attr[0] = 1;}
    }
    if(power.Geteffect()[1] > 0)
    {
        endu = attr[1] - power.Geteffect()[1];
        /// if less than zero, then just set it to the minimum
        if(endu > 0) { attr[1] = endu;} else {attr[1] = 1;}
    }
    if(power.Geteffect()[2] > 0)
    {
        agil = attr[2] - power.Geteffect()[2];
        /// if less than zero, then just set it to the minimum
        if(agil > 0) { attr[2] = agil;} else {attr[2] = 1;}
    }
    if(power.Geteffect()[3] > 0)
    {
        spd = attr[3] - power.Geteffect()[3];
        /// if less than zero, then just set it to the minimum
        if(spd > 0) { attr[3] = spd;} else {attr[3] = 1;}
    }
    target.Setattributes(attr);
}

void Super::ineffectPowerOnTarget(Super& target)
{
    if(target.powerEffected.empty())
    {
        return;
    }
    int duration;
    vector<double> attr, powEffect;
    list<Power>::iterator powit = target.powerEffected.begin();
    attr = target.Getattributes();
    bool flag = false;
    while(powit != target.powerEffected.end())
    {
        duration = (powit)->Getduration();
        duration--;
        (powit)->Setduration(duration);
        if((powit)->Getduration() <= 0)
        {
            powEffect = (powit)->Geteffect();
            if(powEffect[0] > 0)
            {
                attr[0] = attr[0] + powEffect[0];
            }
            if(powEffect[1] > 0)
            {
                 attr[1] = attr[1] + powEffect[1];
            }
            if(powEffect[2] > 0)
            {
                 attr[2] = attr[2] + powEffect[2];
            }
            if(powEffect[3] > 0)
            {
                 attr[3] = attr[3] + powEffect[3];
            }
            cout << "Previous power " << (powit)->Getname() << " lost its effect on target!" << endl;
            target.powerEffected.erase(powit++);
            flag = true;
        }
        else {++powit;}
    }
    target.Setattributes(attr);
    if(flag) {
        cout << target.id << " after recovering from the previous effected power(s)" << endl;
        target.displaySuper();
    }
}

bool Super::isPowerEffectedInUse(const Power& pow, Super& target)
{
    for(list<Power>::iterator it = target.powerEffected.begin(); it != target.powerEffected.end(); ++it)
    {
        if(it->Getname() == pow.Getname())
        {
            return true;
        }
    }
    return false;
}

Power Super::getFinalRandomPower()
{
    if(RandomGeneratorHelper::rollTheDice() < 50)
    {
        return chooseRandomPower();
    }
    else
    {
        /// this is because the read from file I didn't create equipments(Just being lazy)
        /// an if statement to choose from powers instead of equipments
        if(!equipments.empty()) {
            return chooseRandomEquipment();
        } else {
            return chooseRandomPower();
        }
    }
}

Power Super::useRandomPowerOrEquipment()
{
    cout<< id << "'s attributes before Power effect: " << endl;
    displaySuper();
    ineffectPower();
    Power pow = getFinalRandomPower();
    cout << pow.Getname() << " is chosen to be effected " << endl;
    pow.displayPower();
    bool inUse = isPowerInUser(pow);
    if(!inUse) {
        effectPower(pow);
    } else {
        cout << pow.Getname() << " is already in use in previous round(s)!" << endl;
    }
    //cout<< "After Power effect: " << endl;
    //displaySuper();
    cout<< id << "'s attributes after gaining new power: " << endl;
    displaySuper();
    return pow;

}

bool Super::isPowerInUser(const Power& power)
{
    for(list<Power>::iterator pit = powerInUse.begin(); pit != powerInUse.end(); ++pit)
    {
        if(power.Getname() == (pit)->Getname()) { return true;}
    }
    return false;
}

Power& Super::chooseRandomEquipment()
{
    int random = RandomGeneratorHelper::generateRandomInt(0, equipments.size());
    list<Power>::iterator it = equipments.begin();
    std::advance (it,random);
    return (*it);
}

Power& Super::chooseRandomPower()
{
    int random = RandomGeneratorHelper::generateRandomInt(0, powers.size());
    list<Power>::iterator it = powers.begin();
    std::advance (it,random);
    return (*it);
}

void Super::effectPower(Power& power)
{
    double str, endu, agil, spd;
    vector<double> attr = this->Getattributes();
    powerInUse.push_back(power);
    str = attr[0] + power.Geteffect()[0];
    if(str > 0) { attr[0] = str;}
    endu = attr[1] + power.Geteffect()[1];
    if(endu > 0) { attr[1] = endu;}
    agil = attr[2] + power.Geteffect()[2];
    if(agil > 0) { attr[2] = agil;}
    spd = attr[3] + power.Geteffect()[3];
    if(spd > 0) { attr[3] = spd;}

    this->Setattributes(attr);
}

void Super::ineffectPower()
{
    if(powerInUse.empty())
    {
        return;
    }
    int duration;
    vector<double> attr, powEffect;
    list<Power>::iterator powit = powerInUse.begin();
    attr = this->Getattributes();
    double str, endu, agil, spd;
    bool flag = false;
    while(powit != powerInUse.end())
    {
        duration = (powit)->Getduration();
        duration--;
        (powit)->Setduration(duration);
        (powit)->isAbleToFly();
        if((powit)->Getduration() <= 0)
        {
            powEffect = (powit)->Geteffect();
            str = attr[0] - powEffect[0];
            if(str > 0) { attr[0] = str; }
            endu = attr[1] - powEffect[1];
            if(endu > 0) { attr[1] = endu; }
            agil = attr[2] - powEffect[2];
            if(agil > 0 ) { attr[2] = agil; }
            spd = attr[3] - powEffect[3];
            if(spd > 0) { attr[3] =  spd; }
            cout << "Previous " << (powit)->Getname() << " lost its effect on super!" << endl;
            powerInUse.erase(powit++);
            flag = true;
        }
        else { ++powit;}
    }
    this->Setattributes(attr);
    if(flag) {
        cout << id << " after losing the old power(s) effect: " << endl;
        displaySuper();
    }
}

void Super::populatePower(list<Power>& pows)
{
    if(pows.size() > 0) { return;}
    /// random number between 1 to 5, [1,6)
    int maximum = RandomGeneratorHelper::generateRandomInt(1, 6);
    Power * pow;
    for(int i = 0; i < maximum; ++i)
    {
        pow = new Power();
        pows.push_back(*pow);
        pow = nullptr;
    }
}

void Super::addPower(Power* pow)
{
    powers.push_back(*pow);
}
void Super::addEquipment(Power* eq)
{
    equipments.push_back(*eq);
}
