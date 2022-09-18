#include "World.h"

using namespace std;

void World::addActor(Actor *actor) {
    this->actors.push_back(actor);
}

vector<Actor*> World::getActors() {
    return this->actors;
}

void World::attachToController(Actor *actor) {
    this->controllableActor = actor;
}

Actor* World::getControllableActor() {
    return this->controllableActor;
}
