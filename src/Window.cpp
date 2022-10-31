#include "../external/imgui/imgui.h"
#include "../external/imgui/imgui_impl_glfw.h"
#include "../external/imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include "Window.h"

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int Window::Init()
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // GL 3.2 + GLSL 150
    const char *glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac

    // Create window with graphics context
    window = glfwCreateWindow(2560, 1440, "Tofu3Dcpp", NULL, NULL);

    auto x = glGetString(GL_VERSION);
    if (window == NULL)
        return 1;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    sceneRenderTexture.Invalidate(Vector2(2560, 1440));

    SetStyle();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    io.Fonts->AddFontFromFileTTF("../fonts/inconsolata.ttf", 15.0f);

    return 0;
}

void Window::SetStyle()
{
    ImGuiStyle *style = &ImGui::GetStyle();
    ImVec4 *colors = style->Colors;

    style->WindowRounding = 0;
    style->WindowBorderSize = 0;

    ImVec4 cTransparent = ImVec4(0, 0, 0, 0);
    ImVec4 cBeige = ImVec4(1.0f, 0.96f, 0.90f, 1.00f);
    ImVec4 cBeigeMid = ImVec4(0.97f, 0.94f, 0.88f, 1.0f);
    ImVec4 cBeigeDarker = ImVec4(0.94f, 0.91f, 0.85f, 1.0f);
    ImVec4 cScrollbar = ImVec4(0.74f, 0.71f, 0.65f, 0.8f);
    ImVec4 cScrollbarDarker = ImVec4(0.64f, 0.61f, 0.55f, 1.0f);

    colors[(int) ImGuiCol_Text] = ImVec4(0.23f, 0.29f, 0.40f, 1.f);
    colors[(int) ImGuiCol_TextDisabled] = ImVec4(0.23f, 0.29f, 0.40f, 0.5f);
    colors[(int) ImGuiCol_WindowBg] = ImVec4(0.99f, 0.96f, 0.90f, 1.00f);
    colors[(int) ImGuiCol_ChildBg] = cBeige;
    colors[(int) ImGuiCol_PopupBg] = cBeige;
    colors[(int) ImGuiCol_Border] = ImVec4(0.81f, 0.79f, 0.74f, 1);
    colors[(int) ImGuiCol_BorderShadow] = cTransparent;
    colors[(int) ImGuiCol_FrameBg] = cBeige;
    colors[(int) ImGuiCol_FrameBgHovered] = cBeige;
    colors[(int) ImGuiCol_FrameBgActive] = cBeige;
    colors[(int) ImGuiCol_TitleBg] = cBeige;
    colors[(int) ImGuiCol_TitleBgActive] = cBeige;
    colors[(int) ImGuiCol_TitleBgCollapsed] = cBeige;
    colors[(int) ImGuiCol_MenuBarBg] = cBeige;
    colors[(int) ImGuiCol_ScrollbarBg] = cBeige;
    colors[(int) ImGuiCol_ScrollbarGrab] = cScrollbar;
    colors[(int) ImGuiCol_ScrollbarGrabHovered] = cScrollbarDarker;
    colors[(int) ImGuiCol_ScrollbarGrabActive] = cScrollbarDarker;
    colors[(int) ImGuiCol_CheckMark] = ImVec4(0.43f, 0.43f, 0.43f, 1.00f);
    colors[(int) ImGuiCol_SliderGrab] = ImVec4(0.63f, 0.63f, 0.63f, 0.78f);
    colors[(int) ImGuiCol_SliderGrabActive] = ImVec4(0.43f, 0.44f, 0.46f, 0.78f);
    colors[(int) ImGuiCol_Button] = cBeigeDarker;
    colors[(int) ImGuiCol_ButtonHovered] = cBeigeMid;
    colors[(int) ImGuiCol_ButtonActive] = cBeigeDarker;
    colors[(int) ImGuiCol_Header] = cBeigeDarker;
    colors[(int) ImGuiCol_HeaderHovered] = cBeigeMid;
    colors[(int) ImGuiCol_HeaderActive] = cBeigeDarker;
    colors[(int) ImGuiCol_Separator] = ImVec4(0.81f, 0.79f, 0.74f, 1);
    colors[(int) ImGuiCol_SeparatorHovered] = ImVec4(0.17f, 0.17f, 0.17f, 0.89f);
    colors[(int) ImGuiCol_SeparatorActive] = ImVec4(0.17f, 0.17f, 0.17f, 0.89f);
    colors[(int) ImGuiCol_ResizeGrip] = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
    colors[(int) ImGuiCol_ResizeGripHovered] = ImVec4(0.39f, 0.39f, 0.40f, 0.67f);
    colors[(int) ImGuiCol_ResizeGripActive] = ImVec4(0.39f, 0.39f, 0.40f, 0.67f);
    // colors[(int)ImGuiCol_CloseButton]            = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
    // colors[(int)ImGuiCol_ButtonHovered]     = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
    // colors[(int)ImGuiCol_ButtonActive]      = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
    colors[(int) ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[(int) ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[(int) ImGuiCol_PlotHistogram] = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
    colors[(int) ImGuiCol_PlotHistogramHovered] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
    colors[(int) ImGuiCol_TextSelectedBg] = ImVec4(0.71f, 0.72f, 0.73f, 0.57f);
    colors[(int) ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
    colors[(int) ImGuiCol_DragDropTarget] = ImVec4(0.16f, 0.16f, 0.17f, 0.95f);
}

void Window::Run()
{

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        Vector2 camSize = Vector2(400, 400);

        ImVec4 clear_color_renderTarget = ImVec4(0.8f, 0, 0.4f, 1.00f);
        glClearColor(clear_color_renderTarget.x * clear_color_renderTarget.w,
                     clear_color_renderTarget.y * clear_color_renderTarget.w,
                     clear_color_renderTarget.z * clear_color_renderTarget.w,
                     clear_color_renderTarget.w);
        glClear(GL_COLOR_BUFFER_BIT);

        sceneRenderTexture.Bind();

        glViewport(0, 0, camSize.x, camSize.y);

        // render scene



        glClearColor(clear_color_renderTarget.x * clear_color_renderTarget.w,
                     clear_color_renderTarget.y * clear_color_renderTarget.w,
                     clear_color_renderTarget.z * clear_color_renderTarget.w,
                     clear_color_renderTarget.w);
        glClear(GL_COLOR_BUFFER_BIT);


        sceneRenderTexture.Unbind(); // end rendering to sceneRenderTexture


        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        // render windows
        ImGui::SetNextWindowSize(ImVec2(camSize.x, camSize.y), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always, ImVec2(0, 0));
        bool open = true;
        ImGui::Begin("Scene View",
                     &open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                            ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);


        ImGui::SetCursorPosX(0);
        ImGui::Image((ImTextureID) sceneRenderTexture.ColorAttachment, ImVec2(camSize.x, camSize.y), ImVec2(0, 1),
                     ImVec2(1, 0));
        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                     clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}