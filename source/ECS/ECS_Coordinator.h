#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "EventManager.h"


#include "../COMPONENTS/ComponentsAllInclude.h"
#include "../SYSTEMS/SystemsAllInclude.h"

class System;
class Move;
class MoveLevel;
class Act;

class ECS
{
private:
	std::unique_ptr<ComponoentManager> componentManager;
	std::unique_ptr<SystemManager> systemManager;
	std::unique_ptr<EntityManager> entityManager;
	std::unique_ptr<EventManager> eventManager;

public:
	inline void init()
	{
		// create pointers to each manager;
		componentManager = std::make_unique<ComponoentManager>();
		entityManager = std::make_unique<EntityManager>();
		systemManager = std::make_unique<SystemManager>();
		eventManager = std::make_unique<EventManager>();

		System::set_componentManager(componentManager.get());
		System::set_eventManager(eventManager.get());
	}


	// Entity methods
	inline Entity create_entity()
	{
		return entityManager->create_entity();
	}

	inline void destroy_entity(Entity entity)
	{
		entityManager->destroy_entity(entity);
		componentManager->entity_destroyed(entity);
		systemManager->entity_destroyed(entity);
	}

	inline Signature get_signature(Entity entity)
	{
		return entityManager->get_signature(entity);
	}


	// Components methods
	template <typename T>
	void register_component()
	{
		componentManager->register_component<T>();
		LOG("COMPONENT: " << typeid(T).name() << " registered");
	}

	template <typename T>
	void add_component(Entity entity, T component)
	{
		componentManager->add_component<T>(entity, component);

		Signature signature = entityManager->get_signature(entity);

		signature[componentManager->get_ComponentType<T>()] = true;
		entityManager->set_signature(entity, signature);

		//systemManager->entity_signature_changed(entity, signature);
	}

	template <typename T>
	void remove_component(Entity entity)
	{
		componentManager->remove_component<T>(entity);

		Signature signature = entityManager->get_signature(entity);

		signature.set(componentManager->get_component<T>(), false);
		entityManager->set_signature(entity, signature);

		//systemManager->entity_signature_changed(entity, signature);
	}

	template <typename T>
	T& get_component(Entity entity)
	{
		return componentManager->get_component<T>(entity);
	}

	template <typename T>
	ComponentType get_ComponentType()
	{
		return componentManager->get_ComponentType<T>();
	}
	

	// System methods
	template <typename T>
	std::shared_ptr<T> register_system()
	{
		return systemManager->register_system<T>();
	}

	inline void signature_changed(Entity entity, Signature signature)
	{
		systemManager->entity_signature_changed(entity, signature);
	}

	inline void update_all_systems()
	{
		systemManager->update_all_systems();
	}


	
	// Event methos
	inline void send_event(Event event, Entity entity)
	{
		eventManager->send_event(event, entity);
	}

	inline void clear_events()
	{
		eventManager->clear_events();
	}


	   	  
	inline void register_components()
	{
		register_component<Player>();
		register_component<Position>();
		register_component<Render>();
		register_component<Obstacle>();
		register_component<Name>();
		register_component<Vision>();
		register_component<Actor>();
		register_component<Item>();
		register_component<Statistics>();





	}

	inline void register_systems()
	{
		register_system<Act>();
		register_system<Move>();
		register_system<MoveLevel>();
	}



};


