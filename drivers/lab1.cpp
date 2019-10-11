#include "Star.h"
#include "Star.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>

#define TEST_PLANETS 20

using namespace std;

int main(){
    srand(time(NULL));
#ifndef TEST1
    {
        cerr << "\n\tTEST #1: Test Star Creation with 0 planets" << endl;
        Star sun(TEST_PLANETS);
        assert(sun.getCurrentNumPlanets() == 0);
        assert(sun.getMaxPlanets() == TEST_PLANETS);

        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST2
    {
        cerr << "\n\tTEST #2: Test Creating a Planet" << endl;
        Planet x(10, 1);
        assert(x.getID() == 1);
        for(int i = 1; i < 720; i++){
            unsigned int pos = x.orbit();
            assert(pos == i%360);
        }

        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST3
    {
        cerr << "\n\tTEST #3: Add Planets to a Star" << endl;
        Star sun(TEST_PLANETS);
        for(unsigned int i = 0; i < TEST_PLANETS + 5; i++){
            if(i < TEST_PLANETS){
                assert(sun.addPlanet());
                assert(sun.getCurrentNumPlanets() == i+1);
            }else{
                assert(!sun.addPlanet());
                assert(sun.getCurrentNumPlanets() == TEST_PLANETS);
            }
            assert(sun.getMaxPlanets() == TEST_PLANETS);
            Planet temp = sun.getFurthest();
            unsigned int count = 0;
            for(unsigned int j = 0; j < sun.getCurrentNumPlanets(); j++){
                if(temp.getID() == sun.planets[j].getID()) count++;
                assert(temp.getDistance() >= sun.planets[j].getDistance());
            }
            assert(count == 1);
        }
        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST4
    {
        cerr << "\n\tTEST #4: Test Star orbit" << endl;
        Star sun(TEST_PLANETS);
        for(int i = 0; i < TEST_PLANETS; i++) sun.addPlanet();
        unsigned int pos[TEST_PLANETS];
        for(unsigned int i = 0; i < sun.getCurrentNumPlanets(); i++){
            pos[i] = sun.planets[i].getPos();
        }
        sun.orbit();

        for(unsigned int i = 0; i < sun.getCurrentNumPlanets(); i++){
            assert(pos[i] + 1 == sun.planets[i].getPos());
        }

        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST5
    {
        cerr << "\n\tTEST #5: Print Star Information" << endl;
        Star sun(TEST_PLANETS);
        for(int i = 0; i < TEST_PLANETS/2; i++) sun.addPlanet();
        sun.printStarInfo();
        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
    cerr << "\n\tAll Tests Passed.\nDont forget to run with Valgrind and push to Github!\n" << endl;
    return 0;
}
