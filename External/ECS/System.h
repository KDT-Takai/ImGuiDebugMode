#pragma once
#include "Entity.h"
#include <vector>

class System {
public:
	virtual void Update(const std::vector<std::unique_ptr<Entity>>& entity, float dt) = 0;
	virtual ~System() {}
};