#pragma once
#include "System.h"
#include <memory>
#include <vector>

class SystemManager {
public:
	template<typename T, typename... Args>
	T* addSystem(Args&&... args) {
		auto system = std::make_unique<T>(std::forward<Args>(args)...);
		T* systemPtr = system.get();
		_systems.push_back(std::move(system));
		return systemPtr;
	}

	void Update(const std::vector<std::unique_ptr<Entity>>& entities, float dt) {
		for (auto& system : _systems) {
			system->Update(entities, dt);
		}
	}

private:
	std::vector<std::unique_ptr<System>> _systems;
};