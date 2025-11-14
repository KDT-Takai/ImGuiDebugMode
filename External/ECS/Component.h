#pragma once

class Entity;

class Component {
public:
	Entity* _entity;

	virtual void Update(float dt) = 0;
	// ImGui•\Ž¦
	virtual void ImGuiDisplay() = 0;
	virtual ~Component() {}
};