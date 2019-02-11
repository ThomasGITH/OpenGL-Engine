#pragma once
#include <vector>
#include "GameObject.h"
#include <string>

class GameManager;

class Locator
{
public:
	Locator(){};

	static void setGameManagerReference(GameManager* reference);
	static void AddGameObject(GameObject* object);
	static void RemoveGameObject(int index);
	static void RemoveGameObject(std::string tag);
	static GameObject& FindObjectByTag(std::string tag);
	static std::vector<GameObject*>& GetGameObjectList();
	~Locator();

private:
};

