#include "Physics.h"
#include "RigidBody.h"
#include "Framework/Actor.h"

bool Physics::Initialize()
{
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = b2Vec2{ 0.0f, 10.0f };
	m_worldId = b2CreateWorld(&worldDef);

	return true;
}

void Physics::Shutdown()
{
	b2DestroyWorld(m_worldId);
}

void Physics::Update(float dt)
{
	// update simulation
	b2World_Step(m_worldId, 1.0f / 60.0f, 4);
	// update collision
	UpdateCollision();
}

void Physics::UpdateCollision()
{
	b2ContactEvents contactEvents = b2World_GetContactEvents(m_worldId);

	// begin contact
	for (int i = 0; i < contactEvents.beginCount; ++i)
	{
		b2ContactBeginTouchEvent* contactEvent = contactEvents.beginEvents + i;

		b2BodyId bodyIdA = b2Shape_GetBody(contactEvent->shapeIdA);
		b2BodyId bodyIdB = b2Shape_GetBody(contactEvent->shapeIdB);

		Actor* actorA = static_cast<Actor*>(b2Body_GetUserData(bodyIdA));		
		if (!actorA || actorA->IsDestroyed() || !actorA->IsActive()) continue;

		Actor* actorB = static_cast<Actor*>(b2Body_GetUserData(bodyIdB));
		if (!actorB || actorB->IsDestroyed() || !actorB->IsActive()) continue;

		if (actorA->OnCollisionEnter) actorA->OnCollisionEnter(actorB);
		if (actorB->OnCollisionEnter) actorB->OnCollisionEnter(actorA);
	}

	// end contact
	for (int i = 0; i < contactEvents.endCount; ++i)
	{
		b2ContactEndTouchEvent* contactEvent = contactEvents.endEvents + i;

		b2BodyId bodyIdA = b2Shape_GetBody(contactEvent->shapeIdA);
		b2BodyId bodyIdB = b2Shape_GetBody(contactEvent->shapeIdB);

		Actor* actorA = static_cast<Actor*>(b2Body_GetUserData(bodyIdA));
		if (!actorA || actorA->IsDestroyed() || !actorA->IsActive()) continue;

		Actor* actorB = static_cast<Actor*>(b2Body_GetUserData(bodyIdB));
		if (!actorB || actorB->IsDestroyed() || !actorB->IsActive()) continue;

		if (actorA->OnCollisionExit) actorA->OnCollisionExit(actorB);
		if (actorB->OnCollisionExit) actorB->OnCollisionExit(actorA);
	}

	// sensors
	b2SensorEvents sensorEvents = b2World_GetSensorEvents(m_worldId);
	for (int i = 0; i < sensorEvents.beginCount; ++i)
	{
		b2SensorBeginTouchEvent* sensorEvent = sensorEvents.beginEvents + i;

		b2BodyId bodyIdA = b2Shape_GetBody(sensorEvent->sensorShapeId);
		b2BodyId bodyIdB = b2Shape_GetBody(sensorEvent->visitorShapeId);

		Actor* actorA = static_cast<Actor*>(b2Body_GetUserData(bodyIdA));
		if (!actorA || actorA->IsDestroyed() || !actorA->IsActive()) continue;

		Actor* actorB = static_cast<Actor*>(b2Body_GetUserData(bodyIdB));
		if (!actorB || actorB->IsDestroyed() || !actorB->IsActive()) continue;

		if (actorA->OnCollisionEnter) actorA->OnCollisionEnter(actorB);
		if (actorB->OnCollisionEnter) actorB->OnCollisionEnter(actorA);
	}
}
