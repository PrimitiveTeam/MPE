#include "Components.h"

#include "MPE/Editor/ECS/Base/ComponentArray.h"

namespace MPE
{
namespace ECS
{
template class MPE_API ComponentArray<TransformComponent>;
template class MPE_API ComponentArray<VelocityComponent>;
}
}