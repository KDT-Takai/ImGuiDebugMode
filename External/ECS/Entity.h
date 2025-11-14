#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <string>
#include "Component.h"

// Entityクラス
class Entity {
public:
	// エンティティID
	uint32_t _id;
	// 名前
	std::string _name;

	// コンストラクタ
	Entity(uint32_t id, const std::string& name) : _id(id), _name(name) {}

	// コンポーネントの追加
	template<typename T, typename... Args>
	T* addComponent(Args&&... args) {
		auto component = std::make_shared<T>(std::forward<Args>(args)...);
		component->_entity = this;
		_components[typeid(T)] = component;
		return component.get();
	}

	// コンポーネントの取得
	template<typename T>
	T* getComponent() {
		auto it = _components.find(typeid(T));
		if (it != _components.end()) {
			return static_cast<T*>(it->second.get());
		}
		return nullptr;
	}

	// コンポーネントの削除
	template<typename T>
	void removeComponent() {
		_components.erase(typeid(T));
	}

	// コンポーネントの存在確認
	template<typename T>
	bool hasComponent() {
		return _components.find(typeid(T)) != _components.end();
	}

	// 更新処理
	void Update(float dt) {
		for (auto& pair : _components) {
			auto* comp = static_cast<Component*>(pair.second.get());
			comp->Update(dt);
		}
	}

	// コンポーネントのImGui表示
	void ImGuiDisplay() {
		for (auto& pair : _components) {
			auto* comp = static_cast<Component*>(pair.second.get());
			comp->ImGuiDisplay();
		}
	}

private:
	// コンポーネントのマップ
	std::unordered_map<std::type_index, std::shared_ptr<Component>> _components;
};