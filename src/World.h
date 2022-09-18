#ifndef VGARENDERER_WORLD_H
#define VGARENDERER_WORLD_H

#include <vector>
#include "Actor.h"

using namespace std;

class World {
public:
    void addActor(Actor *actor);
    vector<Actor*> getActors();
    void attachToController(Actor *actor);
    Actor* getControllableActor();
private:
    vector<Actor*> actors;
    Actor *controllableActor;
};

#endif //VGARENDERER_WORLD_H
