#include "Locator.h"
#include "GameManager.h"

static GameManager* GM;

void Locator::setGameManagerReference(GameManager* reference)
{
	GM = reference;
}

void Locator::AddGameObject(GameObject* object)
{
	GM->GetGameObjectList().push_back(object);
}

void Locator::RemoveGameObject(int index)
{
	auto& objectList = GM->GetGameObjectList();

	if (objectList.size() >= index + 1)
	{
		objectList.erase(objectList.begin() + index);
	}
}

void Locator::RemoveGameObject(std::string tag)
{
	auto& objectList = GM->GetGameObjectList();

	for (int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i]->tag == tag)
		{
			objectList.erase(objectList.begin() + i);
			//return;
		}
		else if (i == objectList.size() - 1)
		{
			std::cout << "ERROR: Could not find object '" << tag << "' " << std::endl;
			//return;
		}
	}
}

GameObject& Locator::FindObjectByTag(std::string tag)
{
	auto objlist = GM->GetGameObjectList();

	for (int i = 0; i < objlist.size(); i++)
	{
		if (objlist[i]->tag == tag)
		{
			return *objlist[i];
		}
		else if (i == objlist.size() - 1)
		{
			std::cout << "ERROR: Could not find any object by that tag" << std::endl;
		}
	}
}

std::vector<GameObject*>& Locator::GetGameObjectList()
{
	return GM->GetGameObjectList();
}


Locator::~Locator()
{
	GM = nullptr;
}
