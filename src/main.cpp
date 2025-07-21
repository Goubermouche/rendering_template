#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

GLFWwindow* window = nullptr;

int init_glfw() {
	if(!glfwInit()) {
			std::cerr << "failed to initialize GLFW" << std::endl;
			return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	{
		window = glfwCreateWindow(800, 200, "app", nullptr, nullptr);
	}

	if(window == nullptr) {
		std::cerr << "failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	return 0;
}

int init_glew() {
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return 1;
	}

	return 0;
}

int init_imgui() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	return 0;
}

int main() {
	if(init_glfw()) { return 1; }
	if(init_glew()) { return 1; }
	if(init_imgui()) { return 1; }

	// Main loop
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// Start ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Example ImGui window
		ImGui::Begin("Hello, ImGui!");
		ImGui::Text("This is a test window.");
		if(ImGui::Button("Click me")) {
			std::cout << "Button clicked!" << std::endl;
		}
		ImGui::End();

		// Rendering
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui::Render();
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