#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Camera/Camera.h"



struct Window
{
	GLFWwindow* Window;
	float Width = 1280;
	float Height = 720;
};

class OpenGLContext
{
public:
	OpenGLContext(Camera& camera);
	~OpenGLContext();
	
	void Init();
	void Run();
	void HandleInput(float dt);
	void SwapBuffers();	
	inline void SetWindowDimensions(float w, float h)
	{
		glViewport(0, 0, w, h);
		m_Window.Width = w;
		m_Window.Height = h;
	}
	bool IsRunning() const;
	
	void ProcessInput(float dt);

	Window& GetWindow() { return m_Window; }
	const Window& GetWindow() const { return m_Window; }

private:
	Window m_Window;
	Camera& m_Camera;

private:
	// ??????????
	float m_DeltaTime = 0.0f;
	float m_LastFrame = 0.0f;
	bool m_FirstMouse = true;
	float m_LastX, m_LastY;
	bool m_ShowMouse = false;;
	bool m_LeftCtrlPressed = false;

private:
	void SetCallBackFunctions();
	void MousePositionCallback(GLFWwindow* window, double positionX, double positionY);
	void WindowResizeCallBack(GLFWwindow* window, int width, int height);
	void MouseScrollCallBack(GLFWwindow* window, double xoffset, double yoffset);
	//void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);	

	

	// callback wrapper
private:
	class GLFWCallbackWrapper
	{
	public:
		GLFWCallbackWrapper() = delete;
		GLFWCallbackWrapper(const GLFWCallbackWrapper&) = delete;
		GLFWCallbackWrapper(GLFWCallbackWrapper&&) = delete;
		~GLFWCallbackWrapper() = delete;

		static void WindowResizeCallBack(GLFWwindow* window, int width, int height);
		static void MousePositionCallback(GLFWwindow* window, double positionX, double positionY);
		static void MouseScrollCallBack(GLFWwindow* window, double xOffset, double yOffset);
		static void SetApplication(OpenGLContext* application);
	private:
		static OpenGLContext* s_Application;
	};
};