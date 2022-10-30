#include "../external/imgui/imgui.h"
#include "../external/imgui/imgui_impl_glfw.h"
#include "../external/imgui/imgui_impl_opengl3.h"
#include <stdio.h>

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <GLFW/glfw3.h> // Will drag system OpenGL headers

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char **)
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
    GLFWwindow *window = glfwCreateWindow(2560, 1440, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);

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

    // Setup Dear ImGui style

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
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    io.Fonts->AddFontFromFileTTF("fonts/inconsolata.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin(
                    "Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text(
                    "This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float *) &clear_color); // Edit 3 floats representing a color

            if (ImGui::Button(
                    "Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window",
                         &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
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

    return 0;
}