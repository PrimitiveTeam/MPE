#include "ComponentTypeIDGenerator.h"

namespace MPE
{
namespace ECS
{
uint32_t MPE_API ComponentTypeIDGenerator::m_nextTypeID = 0;

ComponentTypeIDGenerator::ComponentTypeIDGenerator() {}
ComponentTypeIDGenerator::~ComponentTypeIDGenerator() {}
}
}
