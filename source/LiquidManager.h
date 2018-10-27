#pragma once
#include <Box2D/Box2D.h>
#include "GameObject.h"

class LiquidManager: public GameObject
{
private:
	b2World* world;
	b2Body* groundBody;
	b2ParticleSystem* particleSystem;
	b2ParticleGroup* seaGroup;
public:
	LiquidManager();
	~LiquidManager();
	void Update();
};

