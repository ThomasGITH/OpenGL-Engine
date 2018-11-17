#include "Locator.h"
#include "GameManager.h"

static GameManager* GM;

Locator::Locator()
{
}

void Locator::setGameManagerReference(GameManager* reference)
{
	GM = reference;
}

void Locator::AddGameObject(GameObject* object)
{
	std::vector<GameObject*> objectList = GM->GetGameObjectList();

	objectList.push_back(object);
	GM->SetGameObjectList(objectList);
}

void Locator::RemoveGameObject(int index)
{
	std::vector<GameObject*> objectList = GM->GetGameObjectList();

	if (objectList.size() >= index + 1)
	{
		objectList.erase(objectList.begin() + index);
		GM->SetGameObjectList(objectList);
	}
}

std::vector<GameObject*> Locator::GetObjectsOfType(GameObject* type)
{
	std::vector<GameObject*> objectList;

	for (int i = 0; i < GM->GetGameObjectList().size(); i++)
	{
		
		if (GM->GetGameObjectList()[i] == type)
		{
			objectList.push_back(GM->GetGameObjectList()[i]);
		}
		
	}

	return objectList;
}

std::vector<GameObject*>Locator::GetGameObjectList()
{
	return GM->GetGameObjectList();
}




Locator::~Locator()
{
}
