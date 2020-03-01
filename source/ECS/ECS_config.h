#pragma once

#include <unordered_map>
#include <bitset>
#include <queue>
#include <array>
#include <set>
#include <cstdint>
#include <cassert>
#include <memory>


#include "../COMPONENTS/ComponentsAllInclude.h" // for MAX_COMPONENTS


using Entity = std::uint32_t; 

using ComponentType = std::uint8_t;


const Entity MAX_ENTITIES = 100000; // also used to mark placeholders, or absence of entity



using Signature = std::bitset<MAX_COMPONENTS>;

// add event types here
enum class EventType { placeHolder = 0, move = 1, moveLevel, };