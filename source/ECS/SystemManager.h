#pragma once

#include "ECS_config.h"
#include "System.h"
#include "../SYSTEMS/SystemsAllInclude.h"

class System;

// SYSTEM MANAGER - manages all systems
class SystemManager
{
	friend class ECS;

private:
	// map from system type string ptr to a signature
	std::unordered_map<const char*, Signature> signatures{};

	// map from system type string ptr to a system pointer
	std::unordered_map<const char*, std::shared_ptr<System>> systems;



public:


	template <typename T>
	void make_system_signature(std::shared_ptr<System> system)
	{
		Signature signature;
		for (ComponentType i = 0; i < MAX_COMPONENTS; i++)
		{
			if (std::find(system->components.begin(), system->components.end(), i) != system->components.end())
				signature.set(i, 1);
			else
				signature.set(i, 0);
		}
		set_signature<T>(signature);

		LOG("SYSTEM: " << typeid(T).name() << " singature make to: " << signature);
	}


	template <typename T>
	std::shared_ptr<T> register_system()
	{
		const char* typeName = typeid(T).name();

		assert(systems.find(typeName) == systems.end() && "ECS ERROR [SystemManager]: Registering system more than once.");

		// create a pointer to the system and return it so it can be used externally
		std::shared_ptr<T> system = std::make_shared<T>();
		std::shared_ptr<System> sys = system;
		sys->init();
		systems.insert({ typeName, system });
		make_system_signature<T>(system);
		LOG("SYSTEM: " << typeid(T).name() << " registered");
		return system;
	}


	template <typename T>
	void set_signature(Signature signature)
	{
		const char* typeName = typeid(T).name();

		assert(systems.find(typeName) != systems.end() && "ECS ERROR [SystemManager]: System used before registred.");

		// set the singature for this system
		signatures.insert({ typeName, signature });
	}


	inline void entity_destroyed(Entity entity)
	{
		// erase entity from all systems sets of entities
		// entities is a set, so no check needed
		for (auto& pair : systems)
		{
			auto& system = pair.second;
			system->entities.erase(entity);
		}
	}


	inline void entity_signature_changed(Entity entity, Signature entitySignature)
	{
		// Notify each system that an entity's signature changed
		for (auto const& pair : systems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = signatures[type];
	
			// Entity signature matches system signature - insert into set
			if ((entitySignature & systemSignature) == systemSignature)
			{
				system->entities.insert(entity);
			}
			// Entity signature does not match system signature - erase from set
			else
			{
				system->entities.erase(entity);
			}
		}
	}


	inline void update_all_systems()
	{ // ORDER IS IMPORTANT - it is order in which systems are updated

		systems[typeid(Act).name()]->update_all();
		systems[typeid(Move).name()]->update_all();
		systems[typeid(MoveLevel).name()]->update_all();

	}




};
