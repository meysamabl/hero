This program compiles and runs with c++11. 

The environment this program was developed was code::block in ubuntu 14.04 but tested in Windows environment as well;

compiler version 4.81;

Make sure you setup your compiler before compile and run.



Steps to setup for c11++ in Codeblock IDE: 

Settings -> Compiler... -> Compiler Settings tab -> Compiler flags tab -> check "Have g++ follow the C++11 ISO C++ language standard [-std=c++11]"




Helper class: 

RandomGeneratorHelper => Class to help generate all the randoms in the application with all the methods defined static;


*** because the new random methods (default_random_engine) was discussed after most parts were already developed, thus, 
some of the methods are still using the old random (rand());




New Addition to Super class: 



1) string TeamName => differensiate the team members inside the class;

2) bool isAlive => to know when the user is alive;

3) list<Power> powerInUse => to keep track of the powers in use and remove the power when its duration is finished;

4) list<Power> powerEffected => to keep track of the powers used on the target;



Assumptions: 



1) Power effects can not make the attributes negative;

2) Random number of 1 to 3 is given to each power as duration;

3) Duration is decremented by each round and when it is zero, the power in use will be removed;

4) Power range is a random number from 5 to 35;

5) if, after distance calculation, the Hero was not within the range to hit its target, dice will decide whether the hero moves or not;

6) if two or more targets are at the exact same distance, a random number would choose the target;

7) Dice will decide whether to effect the power on the super or use it to affect the target. 




*** Some extra explanation: 


1) A Menu was implemented for different cases. 1) generating heros at random 2) reading the heros from the file 3) test cases;






2) In the first version of the fight simulation, both teams were to be merged into one list called OneRoundGame making it much easier and lesser code to handle the turn of each hero, but then I changed it to compare from the two lists just in case that was not part of the requirement. predicate method called "compareSupers" was defined for sorting the merged list. 
In case the are two occurances with the same speed, rolling dice decided which one goes first. 

Sorting the list is called after each round, in case power effects had changed the speed of heros.  

