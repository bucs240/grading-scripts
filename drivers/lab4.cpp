#include "Star.h"
#include "Star.h"
#include "Planet.h"
#include "Planet.h"
#include "Probe.h"
#include "Probe.h"
#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <vector>

using namespace std;

#define NUM_STARS 500

int main(){
	srand(time(NULL));
#ifndef TEST1
{
	cerr << "\n\tTEST #1: Verify Star and Planet Classes" << endl;

    Star s;
    vector<unsigned long> ids;
    for(int i = 0; i < 10; i++){
        unsigned long n = s.addPlanet();
        ids.push_back(n);
    }
    for(auto i: ids){
        Planet * p = s.getPlanet(i);
        assert(p->getDistance() > 0 && p->getDistance() < 3001);
        assert(p->getType() == 'r' || p->getType() == 'g' || p->getType() == 'h');
    }
    for(auto i: ids){
        assert(s.removePlanet(i));
    }
	cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST2
{
    cerr << "\n\tTEST #2: Verify you are using nullptr " << endl;
    Star s;
    assert(s.getPlanet(-1) == nullptr);

	cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST3
{
	cerr << "\n\tTEST #3: Check habitability algorithm" << endl;

    vector<Star> galaxy;
    for(int i = 0; i < NUM_STARS; i++){
        Star star;
        for(int j = 0; j < rand() % 30; j++){
            star.addPlanet();
        }
        galaxy.push_back(star);
    }
    Probe probe;
    vector <Planet> habitable;
    for(auto star : galaxy){
        vector<Planet> h = probe.getHabitable(star);
        for(auto planet: h){
            habitable.push_back(planet);
        }
    }
    for(auto h: habitable){
        assert(h.getType() == 'h' && h.getDistance() <= 140 && h.getDistance() >= 60);
    }

	cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST4
{
	cerr << "\n\tTEST #4: Correct Queue usage" << endl;
    vector<Star> galaxy;
    for(int i = 0; i < NUM_STARS; i++){
        Star star;
        for(int j = 0; j < rand() % 30; j++) star.addPlanet();
        galaxy.push_back(star);
    }
    Probe probe;
    vector <Planet> habitable;
    for(auto star : galaxy)
        for(auto planet: probe.getHabitable(star))
            habitable.push_back(planet);

    vector<unsigned long> pids;
    unsigned int num_habitable = 0;
    for(auto h: habitable){
        pids.push_back(h.getID());
        probe.addToQueue(h);
        num_habitable++;
    }

    for(unsigned int i = 0; i < num_habitable; i++){
        Planet p = probe.getNext();
        unsigned long q = pids.front();
        pids.erase(pids.begin());
        assert(q == p.getID());
    }

	cerr << "\n\t========================PASS========================\n" << endl;
}
#endif
#ifndef TEST5
{
	cerr << "\n\tTEST #5: Shuffle" << endl;
    vector<Star> galaxy;
    for(int i = 0; i < NUM_STARS; i++){
        Star star;
        for(int j = 0; j < rand() % 30; j++) star.addPlanet();
        galaxy.push_back(star);
    }
    Probe probe;
    vector <Planet> habitable;
    for(auto star : galaxy){
        for(auto planet: probe.getHabitable(star)){
            habitable.push_back(planet);
        }
    }
    Probe probeA, probeB, probeC;
    unsigned int num_habitable = 0;
    for(auto h: habitable){
        probeA.addToQueue(h);
        probeB.addToQueue(h);
        probeC.addToQueue(h);
        num_habitable++;
    }
    probeA.shuffle();
    probeB.shuffle();
    probeC.shuffle();
    unsigned int num_matches = 0;
    while(!(probeA.getQueue().empty()) ||
            !(probeB.getQueue().empty()) ||
            !(probeC.getQueue().empty())
            ){
        Planet a = probeA.getNext();
        Planet b = probeB.getNext();
        Planet c = probeC.getNext();
        if(a.getID() == b.getID() && b.getID() == c.getID()){
            num_matches++;
        }
    }
    cerr << "matches: " << num_matches << endl;
	assert(num_matches < 50);

	cerr << "\n\t========================PASS========================\n" << endl;
	cerr << "\n\tAll Tests Passed.\nDon't forget to run with Valgrind and submit your commit hash!\n" << endl;
}
#endif
	return 0;
}
