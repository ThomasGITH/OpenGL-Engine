#pragma once
#include <vector>
#include "GameObject.h"

class GameManager;

class Locator
{
public:
	Locator();

	static void setGameManagerReference(GameManager* reference);
	static void AddGameObject(GameObject* object);
	static void RemoveGameObject(int index);
	static std::vector<GameObject*> GetObjectsOfType(GameObject* type);

	~Locator();

private:
};

