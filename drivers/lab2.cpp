#include "Star.h"
#include "Star.h"
#include "Planet.h"
#include "Planet.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

#define NUM_PLANETS_TO_TEST 500

int main(){
    srand(time(NULL));
#ifndef TEST1
    {
        cerr << "\n\tTEST #1: Test Star Creation with 0 planets" << endl;
        Star * sun = new Star();
        assert(sun->getCurrentNumPlanets() == 0);
        delete sun->planets;
        delete sun;
        sun = NULL;
        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST2
    {
        cerr << "\n\tTEST #2: Test Add 1 Planet " << endl;
        Star * sun = new Star();
        int id = sun->addPlanet();
        assert(sun->getCurrentNumPlanets() == 1);
        Planet * p = sun->getPlanet(id);
        unsigned int pos = p->getPos();
        assert(p->orbit() - 1 == pos);
        assert(p->orbit() >= 0 && p->orbit() < 360);
        delete sun;
        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST3
    {
        cerr << "\n\tTEST #3: Add Many Planets" << endl;
        Star * sun = new Star();
        int all_ids[NUM_PLANETS_TO_TEST] = {0};
        int prev_id = -1;
        for(unsigned int i = 0; i < NUM_PLANETS_TO_TEST; i++){
            all_ids[i] = sun->addPlanet();
            assert(sun->getCurrentNumPlanets() == i+1);
            if(i == 0) continue;
            prev_id = all_ids[rand() % i];
            assert(all_ids[i] != prev_id);
        }
        delete sun;
        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST4
    {
        cerr << "\n\tTEST #4: Delete Planets" << endl;
        Star * sun = new Star();
        int all_ids[NUM_PLANETS_TO_TEST] = {0};
        for(int i = 0; i < NUM_PLANETS_TO_TEST; i++) all_ids[i] = sun->addPlanet();
        for(unsigned int i = 0; i < 10; i++){
            assert(sun->getCurrentNumPlanets() == (NUM_PLANETS_TO_TEST-i));
            assert(sun->removePlanet(all_ids[i]) == true);
            all_ids[i] = -1;
            assert(sun->getCurrentNumPlanets() == (NUM_PLANETS_TO_TEST-i-1));
        }
        //delete 10 random planets in the sun
        for(unsigned int i = 0; i < 10; i++){
            int rand_id = (rand() % (NUM_PLANETS_TO_TEST - 10)) + 10;
            unsigned int num_planets = sun->getCurrentNumPlanets();
            if(sun->removePlanet(all_ids[rand_id]) == true){
                all_ids[rand_id] = -1;
                assert(sun->getCurrentNumPlanets() == --num_planets);
            }else{
                assert(sun->getCurrentNumPlanets() == num_planets);
            }
        }
        assert(sun->removePlanet(-1) == false);
        delete sun;
        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST5
    {
        cerr << "\n\tTEST #5: Orbit Planets Still Works" << endl;
        Star * sun = new Star();
        int all_ids[NUM_PLANETS_TO_TEST] = {0};
        for(int i = 0; i < NUM_PLANETS_TO_TEST; i++) all_ids[i] = sun->addPlanet();
        for(int i = 0; i < NUM_PLANETS_TO_TEST; i++){
            Planet * temp = sun->getPlanet(all_ids[i]);
            if(temp == NULL) continue;
            int pos = temp->getPos();
            sun->orbit();
            int new_pos = temp->getPos();
            (pos == 359) ? assert(new_pos == 0) : assert(new_pos == pos + 1);
        }
        delete sun;
        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
#ifndef TEST6
    {
        cerr << "\n\tTEST #6: Print Hill Information and Free Memory" << endl;
        Star * sun = new Star();
        for(int i = 0; i < NUM_PLANETS_TO_TEST; i++) {
            sun->addPlanet();
            sun->orbit();
        }
        sun->printStarInfo();
        delete sun;
        sun = NULL;
        cerr << "\n\t========================PASS========================\n" << endl;
    }
#endif
    cerr << "\n\tAll Tests Passed.\nDon't forget to run with Valgrind and submit your commit hash to MyCourses!\n" << endl;
    return 0;
}
