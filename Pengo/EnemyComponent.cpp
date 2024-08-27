#include "EnemyComponent.h"
#include "GameConfig.h"
#include "CollisionComponent.h"
#include <Scene.h>
#include "EnemySpawnComponent.h"
#include "GameObject.h"
#include "SoundServiceLocator.h"

EnemyComponent::EnemyComponent(dae::GameObject* gameObject) : dae::Component(gameObject)
{

}

void EnemyComponent::Update(float)
{
	if (m_State != nullptr)
		m_State->Update();
}

void EnemyComponent::SetHitByWallPos(glm::vec3 direction)
{
	GetOwner()->SetGameObjectPosition(direction.x * Config::ELEMENT_SIZE, direction.y * Config::ELEMENT_SIZE);

	m_WasHitByWall = true;
}

void EnemyComponent::Dies()
{
	dae::GameObject* enemyWalls = GetEnemySpawnBlock();
	if (enemyWalls != nullptr)
	{
		if (enemyWalls->HasComponent<EnemySpawnComponent>())
			enemyWalls->GetComponent<EnemySpawnComponent>()->SpawnEnemy();
	}
	else
	{
		dae::Scene* currentScene = dae::SceneManager::GetInstance().GetSceneByName("LevelScene");
		size_t amountEnemies = currentScene->GetGameObjectsWithLayer("Enemy").size();

		if (amountEnemies <= 1)
		{
			dae::SceneManager::GetInstance().UnloadScene("GameLayout");
			dae::SceneManager::GetInstance().UnloadScene("LevelScene");
			dae::SceneManager::GetInstance().LoadScene("EndScene");
		}
	}

	dae::SoundServiceLocator::get_sound_system()->play("Snow-BeeSquashed.mp3", 10);

	GetOwner()->RemoveGameObject();
}

dae::GameObject* EnemyComponent::GetEnemySpawnBlock()
{
	dae::Scene* currentScene = dae::SceneManager::GetInstance().GetSceneByName("LevelScene");
	std::vector<dae::GameObject*> enemyWalls = currentScene->GetGameObjectsWithTag("EnemyWall");

	if (enemyWalls.size() >= 1)
		return enemyWalls.at(0);

	return nullptr;
}
