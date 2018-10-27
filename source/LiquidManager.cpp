#include "LiquidManager.h"



LiquidManager::LiquidManager() : GameObject(0, 0)
{
	b2Vec2 gravity(0, -10);
	world = new b2World(gravity);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.SetZero();
	groundBody = world->CreateBody(&groundBodyDef);

	b2ChainShape shape;
	const int vertNum = 16;
	const double radius = 2;

	b2Vec2 vertices[vertNum];
	for (int i = 0; i < vertNum; i++) {
		auto angle = (i * 2 * b2_pi / vertNum);
		vertices[i] = b2Vec2(radius * std::cos(angle), radius * std::sin(angle) + 1);
	}
	shape.CreateLoop(vertices, vertNum);
	groundBody->CreateFixture(&shape, 0);

	b2ParticleSystemDef particleSystemDef;
	particleSystemDef.radius = 3;
	particleSystem = world->CreateParticleSystem(&particleSystemDef);

	b2ParticleGroupDef groupDef;
	//groupDef.shape = shape;
	groupDef.flags = b2_waterParticle;
	groupDef.color = b2ParticleColor(255, 0, 0, 255);
	groupDef.position.SetZero();
	seaGroup = particleSystem->CreateParticleGroup(groupDef);
}


LiquidManager::~LiquidManager()
{
	delete(world);
}

void LiquidManager::Update()
{
	world->Step(1.0 / 60.0, 5, 2, 1);
	void** userData = particleSystem->GetUserDataBuffer() + seaGroup->GetBufferIndex();
}
