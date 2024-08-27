#pragma once
#include "GameObject.h"
#include "CollisionObserver.h"

class PengoCollisionObserver : public dae::CollisionObserver
{
public:
	PengoCollisionObserver(dae::GameObject* gameObject) : m_pOwner(gameObject) {}
	~PengoCollisionObserver() override = default;

	PengoCollisionObserver(const PengoCollisionObserver& other) = delete;
	PengoCollisionObserver(PengoCollisionObserver&& other) = delete;
	PengoCollisionObserver& operator=(const PengoCollisionObserver& other) = delete;
	PengoCollisionObserver& operator=(PengoCollisionObserver&& other) = delete;

	void NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor) override;
private:
	dae::GameObject* m_pOwner;
};
