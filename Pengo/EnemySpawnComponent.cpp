#include "EnemySpawnComponent.h"
#include "EnemyComponent.h"
#include "Animation.h"
#include "CollisionComponent.h"
#include "EnemyCollisionObserver.h"
#include "Scene.h"
#include "EnemyState.h"
#include "EnemyMovementAIComponent.h"
#include "SoundServiceLocator.h"

EnemySpawnComponent::EnemySpawnComponent(dae::GameObject* gameObject) : dae::Component(gameObject)
{
}

void EnemySpawnComponent::SpawnEnemy()
{
	glm::vec3 pos = GetOwner()->GetGameObjectPosition();

	auto enemy = std::make_unique<dae::GameObject>();

	enemy.get()->AddComponent(new dae::RenderComponent(enemy.get()));
	enemy.get()->GetComponent<dae::RenderComponent>()->SetTexture("CharactersSheet.png");
	enemy.get()->GetComponent<dae::RenderComponent>()->SetSourceRect(0, 16 * 8, 16, 16);
	enemy.get()->SetGameObjectPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
	enemy.get()->AddComponent(new Animation(enemy.get()));
	enemy.get()->AddComponent(new EnemyComponent(enemy.get()));
	enemy.get()->GetComponent<EnemyComponent>()->SetState(std::make_unique<SpawningState>(enemy.get()));
	enemy.get()->AddComponent(new EnemyMovementAIComponent(enemy.get()));
	enemy.get()->AddComponent(new dae::CollisionComponent(enemy.get(), 16.f, 16.f));
	enemy.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new EnemyCollisionObserver(enemy.get()));
	enemy.get()->SetLayer("Enemy");

	dae::SceneManager::GetInstance().GetSceneByName("LevelScene")->Add(std::move(enemy));

	dae::SoundServiceLocator::get_sound_system()->play("Snow-BeeSpawning.mp3", 10);
}