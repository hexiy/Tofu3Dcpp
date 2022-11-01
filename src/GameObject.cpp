#include "GameObject.h"
#include "Renderer.h"
#include "Debug.h"
#include "iostream"
#include "IDManager.h"

GameObject::GameObject()
{
    Id = NextGameObjectID++;
}

void GameObject::Init()
{
}

void GameObject::Render()
{
    for (int i = 0; i < (int) Components.size(); i++)
    {
        // Component *renderer = dynamic_cast<Component *>(Components[i]);
        // renderer->Render();

        (Components[i])->Render();

//        if (renderer != nullptr)
//        {
//            renderer->Render();
//            // std::cout << renderer->type << "  ";
//        } else
//        {
//            Components[i]->Render();
//
//            //std::cout << Components[i]->type << "  ";
//        }
    }

}

