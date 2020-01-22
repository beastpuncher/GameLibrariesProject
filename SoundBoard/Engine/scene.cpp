#include "scene.h"
#include "entity.h"
#include "collisionComponent.h"
#include "audioSystems.h"
#include "eventManager.h"
#include "renderComponent.h"
#include "id.h"
#include <assert.h>
#include <algorithm>

bool Scene::Initialize()
{
	return true;
}

void Scene::Update()
{
	for (Entity* entity : m_entities)
	{
		entity->Update();
	}

	// update collision
	std::vector<ICollisionComponent*> collisionComponents;

	for (Entity* entity : m_entities)
	{
		ICollisionComponent* collisionComponent = entity->GetComponent<ICollisionComponent>();
		if (collisionComponent)
		{
			collisionComponents.push_back(collisionComponent);
		}
	}

	for (size_t i = 0; i < collisionComponents.size(); i++)
	{
		for (size_t j = i +1; j < collisionComponents.size(); j++)
		{
			if (collisionComponents[i]->Intersects(collisionComponents[j]))
			{
				Event event;
				event.eventID = "collision";

				event.reciver = collisionComponents[i]->GetOwner();
				event.sender = collisionComponents[j]->GetOwner();
				EventManager::Instance()->SendMessage(event);

				event.reciver = collisionComponents[j]->GetOwner();
				event.sender = collisionComponents[i]->GetOwner();
				EventManager::Instance()->SendMessage(event);
			}
		}
	}


	std::list <Entity*>::iterator iter = m_entities.begin();
	while (iter != m_entities.end())
	{
		if ((*iter)->GetState() == Entity::DESTROY)
		{
			(*iter)->Destroy();
			iter = RemoveEntity(*iter);
		}
		else 
		{
			iter++;
		}
	}

}

void Scene::Shutdown()
{
	for (Entity* entity : m_entities)
	{
		delete entity;
	}
	m_entities.clear();
}

void Scene::Draw()
{
	std::vector<IRenderComponent*> renderComponents;

	for (Entity* entity : m_entities)
	{
		IRenderComponent* renderComponent = entity->GetComponent<IRenderComponent>();
		if (renderComponent)
		{
			renderComponents.push_back(renderComponent);
		}
	}
	std::sort(renderComponents.begin(),renderComponents.end(),IRenderComponent::CompareDepth);
	for (IRenderComponent* render : renderComponents)
	{
		if (render->GetVisible())
		{
			render->Draw();
		}
	}
}

void Scene::AddEntity(Entity * entity)
{
	assert(entity);
	assert(std::find(m_entities.begin(),m_entities.end(),entity) == m_entities.end());

	m_entities.push_back(entity);
}

std::list <Entity*>::iterator Scene::RemoveEntity(Entity * entity, bool Destroy)
{
	assert(entity);
	assert(std::find(m_entities.begin(), m_entities.end(), entity) != m_entities.end());

	auto iter = std::find(m_entities.begin(), m_entities.end(), entity);
	if (iter != m_entities.end())
	{
		if (Destroy)
		{
			(*iter)->Destroy();
			delete *iter;
		}
		iter = m_entities.erase(iter);
	}
	return iter;
}

Entity * Scene::GetEntityWithID(const ID& id)
{
	Entity* entity = nullptr;

		for (Entity* _entity : m_entities)
		{
			if (*_entity == id)
			{
			entity = _entity;
			break;
			}
		}
	return entity;
}

std::vector<Entity*> Scene::GetEntitiesWithTag(const ID & tag)
{
	std::vector<Entity*> entities;

	for (Entity* entity : m_entities)
	{
		if (entity->GetTag() == tag)
		{
			entities.push_back(entity);
		}
	}

	return entities;
}
