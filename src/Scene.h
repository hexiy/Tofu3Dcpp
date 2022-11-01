#pragma once

#include "vector"
#include "GameObject.h"

class Scene
{
public:
    std::vector<GameObject> GameObjects;
public :
    void Start();

    void Update();

    void OnComponentAdded(GameObject *gameObject, Component *component);

    void RenderQueueChanged();

    void SortRenderQueue();

    void Render();

    void CreateDefaultScene();

    void AddGameObject(GameObject *go);
};
