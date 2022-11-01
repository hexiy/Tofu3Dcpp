#include "Window.h"
#include "Scene.h"
#include "iostream"

int main()
{
    Scene scene;
    scene.Start();
    scene.CreateDefaultScene();


    Window window;

    window.Init();
    window.Run(&scene);
}
