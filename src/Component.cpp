#include "Component.h"
#include "Debug.h"
#include "IDManager.h"

Component::Component()
{
    Id = NextComponentID++;
}

void Component::Render()
{
   // Debug::Log("nothing");
}
