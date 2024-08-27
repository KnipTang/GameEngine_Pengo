#include "Scene.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_pendingAdditions.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
	m_pendingAdditions.clear();
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::LateUpdate(float deltaTime)
{
	for (auto& object : m_objects)
	{
		if (object == nullptr) continue;
		object->LateUpdate(deltaTime);
	}

	for (auto& object : m_objects)
	{
		if (object == nullptr) continue;
		if (object.get()->IsRemoveGameObjectTrue())
		{
			m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
		}
	}
	for (auto& object : m_pendingAdditions) {
		m_objects.emplace_back(std::move(object));
	}
	m_pendingAdditions.clear();
}


void Scene::FixedUpdate(float fixedTimeStep)
{
	for (auto& object : m_objects)
	{
		if (object == nullptr) continue;
		object->FixedUpdate(fixedTimeStep);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}


void Scene::CollisionDetection()
{
	for (size_t i = 0; i < m_objects.size(); ++i)
	{
		auto* collisionComponent1 = m_objects[i]->GetComponent<CollisionComponent>();
		if (!collisionComponent1)
			continue;

		for (size_t j = i + 1; j < m_objects.size(); ++j)
		{
			auto* collisionComponent2 = m_objects[j]->GetComponent<CollisionComponent>();
			if (!collisionComponent2)
				continue;

			if (collisionComponent1->Intersects(*collisionComponent2))
			{
				collisionComponent2->Intersects(*collisionComponent1);
			}
		}
	}
}

std::vector<GameObject*> Scene::GetGameObjectsWithTag(std::string tag)
{
	std::vector<GameObject*> gameobjectsWithTag;

	for (const auto& object : m_objects)
	{
		if (object->GetTag() == tag) 
		{
			gameobjectsWithTag.emplace_back(object.get());
		}
	}

	for (const auto& object : m_pendingAdditions)
	{
		if (object->GetTag() == tag)
		{
			gameobjectsWithTag.emplace_back(object.get());
		}
	}

	return gameobjectsWithTag;
}

std::vector<GameObject*> Scene::GetGameObjectsWithLayer(std::string layer)
{
	std::vector<GameObject*> gameobjectsWithLayer;

	for (const auto& object : m_objects)
	{
		if (object->GetLayer() == layer)
		{
			gameobjectsWithLayer.emplace_back(object.get());
		}
	}

	for (const auto& object : m_pendingAdditions)
	{
		if (object->GetLayer() == layer)
		{
			gameobjectsWithLayer.emplace_back(object.get());
		}
	}

	return gameobjectsWithLayer;
}

GameObject* Scene::GetGameObjectWithTag(std::string tag)
{
	for (const auto& object : m_objects)
	{
		if (object->GetTag() == tag)
		{
			return object.get();
		}
	}

	for (const auto& object : m_pendingAdditions)
	{
		if (object->GetTag() == tag)
		{
			return object.get();
		}
	}

	return nullptr;
}

GameObject* Scene::GetGameObjectWithLayer(std::string layer)
{
	for (const auto& object : m_objects)
	{
		if (object->GetLayer() == layer)
		{
			return object.get();
		}
	}

	for (const auto& object : m_pendingAdditions)
	{
		if (object->GetLayer() == layer)
		{
			return object.get();
		}
	}

	return nullptr;
}
