#pragma once
#include "Entity.h"
#include <vector>
#include <memory>

class EntityManager {
public:
	// エンティティの作成
	Entity* createEntity(const std::string& name = "Entity") {
		auto entity = std::make_unique<Entity>(_nextId++, name);
		Entity* entityPtr = entity.get();
		_entities.push_back(std::move(entity));
		return entityPtr;
	}
	// エンティティの更新
	void Update(float dt) {
		for (auto& entity : _entities) {
			entity->Update(dt);
		}
	}
	// エンティティの削除
	void ImGuiDisplay() {
		for (auto& entity : _entities) {
			entity->ImGuiDisplay();
		}
	}
	// エンティティの取得
	std::vector<std::unique_ptr<Entity>>& GetAll() {
		return _entities;
	}

private:
	uint32_t _nextId = 0;
	std::vector<std::unique_ptr<Entity>> _entities;
};