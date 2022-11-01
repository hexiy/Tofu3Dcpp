#include "Scene.h"
#include "Debug.h"
#include "Renderer.h"
#include "IDManager.h"

void Scene::Start()
{

}

void Scene::AddGameObject(GameObject *go)
{
    GameObjects.push_back(*go);
}

void Scene::CreateDefaultScene()
{
    for (int i = 0; i < 1; ++i)
    {
        GameObject *gameObject = new GameObject();
        gameObject->Id = NextGameObjectID++;
        gameObject->Init();

        Renderer *renderer = new Renderer();
        renderer->Id = NextComponentID++;
        gameObject->Components.push_back(renderer);

        Component *comp = new Component();
        comp->Id = NextComponentID++;
        gameObject->Components.push_back(comp);

        AddGameObject(gameObject);
    }
}

void Scene::Render()
{
    for (int i = 0; i < (int)GameObjects.size(); i++)
    {
        GameObjects[i].Render();
        //std::cout << "Id:" << ((*scene).GameObjects[i]).Id << std::endl;
    }
}

void Scene::SortRenderQueue()
{

}

void Scene::RenderQueueChanged()
{

}

void Scene::OnComponentAdded(GameObject *gameObject, Component *component)
{

}
