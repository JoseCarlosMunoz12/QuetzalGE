#include "Game.h"
void Game::initGLFW()
{
	//INIT GLFW
	if (glfwInit() == GLFW_FALSE)
	{
			std::cout << "ERROR::GLFE_INIT_FAILED" << "\n";
			glfwTerminate();
	}
}

void Game::initWindow(const char* title, bool resizable)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GLVerMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GLVerMinor);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	this->window = glfwCreateWindow(Window_Width, Window_Height, title, NULL, NULL);
	if (this->window == nullptr)
	{
		std::cout << "ERROR::GLFW_WINODE_INIT_FAILED";
		glfwTerminate();
	}
	glfwGetFramebufferSize(this->window, &this->frameBufferWidth , &this->frameBufferHeight );
	glfwSetFramebufferSizeCallback(this->window, Game::framebuffer_resize_callback);
	//glViewport(0, 0,framebufferWidth,framebufferWidth );
	glfwMakeContextCurrent(this->window);//IMPORTANT

}

void Game::initGLEW()
{
	//INIT GLEW (NEEDS WINDOW AND OPENGL CONTEXT)	
	glewExperimental = GL_TRUE;
	//ERROR
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR:MAIN>CPP::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}

void Game::initOpenGLOptions()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glfwSetInputMode(this->window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
}

void Game::initMatrices()
{
	this->ViewMatrix = glm::mat4(1.f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);
	this->ProjectionMatrix = glm::mat4(1.f);

	this->ProjectionMatrix = glm::perspective(glm::radians(this->fov),
		static_cast<float>(this->frameBufferWidth) / static_cast<float>(this->frameBufferHeight),
		this->nearPlane,
		this->farPlane);
}

void Game::initShaders()
{
}

void Game::initShadows()
{
}

void Game::initTextures()
{
}

void Game::initMaterials()
{
}

void Game::initModels()
{
}

void Game::initLights()
{
}
 
void Game::initUniforms()
{
}

void Game::initImGui()
{
	this->ImManager = std::make_unique<ImGuiWindowManager>(this->window);
}

void Game::updateDT()
{
	this->cuTime = static_cast<float>(glfwGetTime());
	this->dt = this->cuTime - this->lastTime;
	this->lastTime = this->cuTime;
	//std::cout << 1 / dt <<"\n";
}

void Game::updateKeyboardInput()
{
	//End Game
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}

}

void Game::updateMouseInput()
{
}

void Game::updateInput()
{
	glfwPollEvents();
	this->updateOpenGLOptions();
	this->updateKeyboardInput();
	this->updateMouseInput();
	this->updateController();
}

void Game::updateController()
{
}
 
void Game::ImGuiOptions()
{
	this->ImManager->Update();
}

void Game::updateUniforms()
{
	//Update FrameBuffer size and projection matrix
	glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);
	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(glm::radians(this->fov),
		static_cast<float>(this->frameBufferWidth) / static_cast<float>(this-> frameBufferHeight),
		this->nearPlane,
		this->farPlane);
}

void Game::updateOpenGLOptions()
{
	if (glfwGetKey(this->window, GLFW_KEY_L) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);
		
	}
	if (glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		this->MakeMesh = false;
	}
	if (glfwGetKey(this->window, GLFW_KEY_E) == GLFW_PRESS)
	{
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		this->MakeMesh = true;
	}
	if (glfwGetKey(this->window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}
}

Game::Game(const char * title,
	const int width, const int height,
	const int GLmajorVer, const int GLminorVer, bool resizable,glm::vec3 SkyColor)
	: Window_Width(width), Window_Height(height),
	GLVerMajor(GLmajorVer), GLVerMinor(GLminorVer)
{
	
	this->SkyColor = SkyColor;
	this->window = NULL;
	this->frameBufferHeight = this->Window_Height;
	this->frameBufferWidth = this->Window_Width;
	this-> camPosition = glm::vec3(0.f, 1.f, 0.f);
	this-> worldUp = glm::vec3(0.f, 0.f, 1.f);
	this-> camFront = glm::vec3(0.f, 0.f,-1.f);

	this-> fov = 90.f;
	this-> nearPlane = .1f;
	this-> farPlane = 1000.f;
	
	this->dt = 0.f;
	this->cuTime = 0.f;
	this->lastTime = 0.f;
	
	this->initGLFW();
	this->initWindow(title,resizable);
	this->initGLEW();
	this->initOpenGLOptions();
	this->initMatrices();
	this->initShaders();
	this->initShadows();
	this->initTextures();
	this->initMaterials();
	this->initModels();
	this->initLights();
	this->initUniforms();
	this->initImGui();
	const char* glsl_version = "#version 130";
}

Game::~Game()
{
	glfwDestroyWindow(this->window );
	glfwTerminate();
}
//Acessor
int Game::getWindowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}
//Modifiers
void Game::setWindowShouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}
//Functions
void Game::update()
{
	//Update Input---
	this->updateDT();
	this->updateInput();
	this->ImGuiOptions();
}

void Game::render()
{
	//DRAW---
	//Updating Shadows Textures
	//render ImGui
	this->ImManager->Render();
	//Clear
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, this->Window_Width, this->Window_Height);
	glClearColor(this->SkyColor.r, this->SkyColor.g, this->SkyColor.b, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//Update uniforms
	this->updateUniforms();
	//render Models
	glfwSwapBuffers(window);
	glFlush();
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::framebuffer_resize_callback(GLFWwindow * window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
}