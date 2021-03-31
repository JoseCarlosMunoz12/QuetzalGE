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
	
	glfwSetInputMode(this->window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
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
	//Regular Shaders to Draw
	this->shaders.push_back(new Shader(0,STATIC,this->GLVerMajor , this->GLVerMinor ,
		"vertex_core.glsl", "fragment_core.glsl"));
	this->shaders.push_back(new Shader(1, STATIC,this->GLVerMajor, this->GLVerMinor,
		"terrain_vertex.glsl", "terrain_fragment.glsl"));
	this->shaders.push_back(new Shader(2, STATIC,this->GLVerMajor, this->GLVerMinor,
		"MultiTexVertex.glsl", "MultiTexFragment.glsl"));
	//Shadow Shaders
	this->shaders.push_back(new Shader(3, STATIC, this->GLVerMajor, this->GLVerMinor,
		"ShadowMapVertex.glsl", "ShadowMapFrag.glsl"));
	//Shadow Debug information
	this->shaders.push_back(new Shader(4, STATIC, this->GLVerMajor, this->GLVerMinor,
		"DebugVertex.glsl", "DebugFrag.glsl"));
	this->shaders.push_back(new Shader(5,ANIM,this->GLVerMajor,GLVerMinor,
		"BasicAnimVertex.glsl","BasicAnimFrag.glsl"));
}

void Game::initShadows()
{
	this->Shadows.push_back(new ShadowTex("Shadow0"));
	this->Shadows.push_back(new ShadowTex("Shadow1"));
	this->Shadows.push_back(new ShadowTex("Shadow2"));
	for (auto& ii : this->Shadows)
	{
		ii->Init(this->Window_Width, this->Window_Height);
	}
}

void Game::initTextures()
{
	//Texture INIT----------
	this->textures.push_back(new Texture("Images/Linux Penguin (Texture).png", GL_TEXTURE_2D,GL_RGBA ));
	this->textures.push_back(new Texture("Images/pusheen_specular.png", GL_TEXTURE_2D, GL_RGBA ));
	//Second Texture
	this->textures.push_back(new Texture("Images/container.png", GL_TEXTURE_2D, GL_RGBA ));
	this->textures.push_back(new Texture("Images/container_specular.png", GL_TEXTURE_2D, GL_RGBA ));
	//Third Image
	this->textures.push_back(new Texture("Images/Test1.png", GL_TEXTURE_2D, GL_RGBA ));
	this->textures.push_back(new Texture("Images/Test1_specular.png", GL_TEXTURE_2D, GL_RGBA ));
	//Blend Map Images
	this->textures.push_back(new Texture("Images/grassy2.png", GL_TEXTURE_2D, GL_RGBA ));
	this->textures.push_back(new Texture("Images/mud.png", GL_TEXTURE_2D, GL_RGBA ));
	this->textures.push_back(new Texture("Images/grassFlowers.png", GL_TEXTURE_2D, GL_RGBA ));
	this->textures.push_back(new Texture("Images/path.png", GL_TEXTURE_2D, GL_RGBA ));
	this->textures.push_back(new Texture("Images/blendMap.png", GL_TEXTURE_2D, GL_RGBA ));
	//Stall Texture
	this->textures.push_back(new Texture("Images/stallTexture.png", GL_TEXTURE_2D, GL_RGBA ));
	//Tree Texture
	this->textures.push_back(new Texture("Images/tree.png", GL_TEXTURE_2D, GL_RGBA ));
	this->textures.push_back(new Texture("Images/diffuse.png", GL_TEXTURE_2D, GL_RGBA));
	//Shadow MapCreation
	for (auto& ii : this->Shadows)
	{
		this->textures.push_back(ii);
	}	
	//HeightMap Info
	this->MipMapsData.push_back(new MipMap("Images/Test.png", this->MapWidth,this->MapHeigth,10.f,100.f,100.f));
}

void Game::initMaterials()
{
	//Testbug the new mats	
	this->MatTest.push_back(new MipMapMat("TerrainMat", 0, 2,
		this->SkyColor, { 0,1,2,3,4 }, {5,6}, {}, {}, {7}));
	this->MatTest.push_back(new TxtMat("Model Terrain", 1, 0,
							this->SkyColor, glm::vec3(0.1f),
							glm::vec3(1.f), glm::vec3(1.f),
		0, 1, {2,3}, {}, {}, {4}));
	this->MatTest.push_back(new TxtMat("Model File", 2, 0,
							this->SkyColor, glm::vec3(0.1f),
							glm::vec3(1.f), glm::vec3(1.f),
		0, 1, {2,3}, {}, {}, {4}));
	this->MatTest.push_back(new SingleTextMat("Single", 3, 4,
								this->SkyColor, 0));
	this->MatTest.push_back(new MipMapMat("Terr", 4, 5,
		this->SkyColor, { 0,1,2,3,4 }, { 5,6 }, {}, {}, { 7 }));
}

void Game::initModels()
{
	std::vector<glm::vec3> Set = { glm::vec3(1.f,1.f,0.f),
		glm::vec3(0.f,0.f,0.f) ,
		glm::vec3(0.f,1.f,0.f) };
	//Meshes Made to be use
	meshes.push_back(
		new Mesh(
			std::make_unique<CustomTerrain_M>(100, 100, this->MipMapsData[HEIGHTMAP_1]),
			"Terrain"));
	//meshes.push_back(
	//	new Mesh(&Sphere_M(1, 32.f, 32.f),
	//		"Sphere"));
	//meshes.push_back(
	//	new Mesh(&Cylinder_M(1.f, 4, 40),
	//		"Cylinder"));
	//meshes.push_back(
	//	new Mesh(&Cone_M(10.f, 10.f, 40, 10),
	//		"Cone"));
	//meshes.push_back(
	//	new Mesh(&Prism_M(4.f,4.f,1.f),
	//		"Cube"));
	//meshes.push_back(
	//	new Mesh(&Capsule_M(1.f,1.f,16,16),
	//		"Capsule"));
	//meshes.push_back(
	//	new Mesh(&Triangle_M(Set),
	//		"Triangle" ));
	//animMeshes.push_back(new AnimMesh(&MulClanimlr({"model_Running.dae"}), "Test0"));
	//animMeshes.push_back(new AnimMesh(&MulClanimlr({ "Snek_Up.dae", "Snek_Side.dae" }), "Test1"));
	//animMeshes.push_back(new AnimMesh(&ClAnimLr("Snek_Up.dae",this->AnimRdrMk.ReadFile("AnimeTest.txt")), "Test2"));
	//
	//Meshes Componets are made
	//

	//--Static Models Components
	MeshsArtifacts Terrain(glm::vec3(0.f), glm::vec3(0.f), QuatParts(), glm::vec3(1.f),
		0, 0, { 0,1,2,3,4,5,6,7 });
	MeshsArtifacts Terrains(glm::vec3(0.f), glm::vec3(0.f), QuatParts(), glm::vec3(.25f),
		0, 0, { 0,1,2,3,4,5,6,7 });
	MeshsArtifacts Monk(glm::vec3(0.f), glm::vec3(0.f), QuatParts(), glm::vec3(1.f), 0, 0, { 0,1,2,3,4 });
	MeshsArtifacts Flat(glm::vec3(0.f), glm::vec3(0.f), QuatParts(), glm::vec3(1.f), 0, 0, { 0 });

	//--Animated Models Components
	//
	//Pushing Models
	//
	this->models.push_back(new Model("Terrain",
		glm::vec3(0.f, 0.f, 0.f),
		this->MatTest[0],
		{this->textures[6],this->textures[7], this->textures[8],this->textures[9],this->textures[10],
		this->textures[14],this->textures[15],this->textures[16]},
		meshes[0], {Terrain}));/*
	this->models.push_back(new Model("Cube0",
		glm::vec3(1.f,-1.f,5.f),
		this->MatTest[1],
		{ this->textures[2],this->textures[3],
		this->textures[14],this->textures[15],this->textures[16] },
		meshes[4], { Monk }));
	this->models.push_back(new Model("Cube1",
		glm::vec3(1.f, 9.f, 5.f),
		this->MatTest[1],
		{ this->textures[2],this->textures[3],
		this->textures[14],this->textures[15],this->textures[16] },
		meshes[4], { Monk }));
	this->models.push_back(new Model("Cube2",
		glm::vec3(10.f, 6.f, 5.f),
		this->MatTest[1],
		{ this->textures[2],this->textures[3],
		this->textures[14],this->textures[15],this->textures[16] },
		meshes[4], { Monk }));
	this->models.push_back(new Model("Triangle",
		this->MipMapsData[0]->ReturnVecVal(4.f, 3.f) + glm::vec3(0.f,0.f,1.f),
		this->MatTest[1],
		{ this->textures[2],this->textures[3],
		this->textures[14],this->textures[15],this->textures[16] },
		meshes[6], { Monk }));
	this->models.push_back(new Model("Sphere1",
		this->MipMapsData[0]->ReturnVecVal(-6.f, 3.f),
		this->MatTest[1],
		{ this->textures[10],this->textures[10],
		this->textures[14],this->textures[15],this->textures[16] },
		meshes[1], { Monk }));
	this->models.push_back(new Model("Sphere0",
		this->MipMapsData[0]->ReturnVecVal(0.f, 0.f),
		this->MatTest[1],
		{ this->textures[9],this->textures[9],
		this->textures[14],this->textures[15],this->textures[16] },
		meshes[1], { Monk }));
	this->models.push_back(new Model("Capsule0",
		this->MipMapsData[0]->ReturnVecVal(3.f, -5.f),
		this->MatTest[1],
		{ this->textures[6],this->textures[6],
		this->textures[14],this->textures[15],this->textures[16] },
		meshes[5], { Monk }));
	this->models.push_back(new Model("Capsule1",
		this->MipMapsData[0]->ReturnVecVal(3.f, 5.f),
		this->MatTest[1],
		{ this->textures[6],this->textures[6],
		this->textures[14],this->textures[15],this->textures[16] },
		meshes[5], { Monk }));*/
	//anim Models
	//this->animModel.push_back(new AnimModel("Tes1t",
	//	glm::vec3(0.f, this->MipMapsData[0]->ReturnValue(0.f, 0.f), 0.f),
	//	this->MatTest[4],
	//	{ this->textures[13],this->textures[6], this->textures[8], this->textures[9],this->textures[10],
	//	this->textures[14],this->textures[15],this->textures[16] },
	//	animMeshes[1], { Terrains })); 
	//this->animModel.push_back(new AnimModel("Test",
	//	this->MipMapsData[0]->ReturnVecVal(4.f, 3.f),
	//	this->MatTest[4],
	//	{ this->textures[13],this->textures[13], this->textures[8], this->textures[9],this->textures[10],
	//	this->textures[14],this->textures[15],this->textures[16] },
	//	animMeshes[0], { Terrains }));
}

void Game::initLights()
{
	//Initializing Dir lights
	this->DirLights.push_back(new DrLights(0,glm::vec3(-1.f,-1.f,this->MipMapsData[0]->ReturnValue(-1.f, -1.f) + 10.f),
		glm::vec3(1.f, 1.f, 1.f), this->frameBufferWidth, this->frameBufferWidth));
	this->DirLights.push_back(new DrLights(1, glm::vec3(-1.f, -1.f, this->MipMapsData[0]->ReturnValue(-1.f, -1.f) + 10.f),
		glm::vec3(1.f, 0.f, 1.f), this->frameBufferWidth, this->frameBufferWidth));
	//Init Cone Lights
	//Init Arealights
	this->ArLights.push_back(new AreaLights(glm::vec3(1.f, 1.f, 1.f),
		glm::vec3(-1.f, 1.f, this->MipMapsData[0]->ReturnValue(-1.f, 1.f) + 10.f),
		24.f,12.f,2));

	for (auto& ii : this->DirLights)
	{
		this->LightsToUse.push_back(ii);
	}
	for (auto& ii : this->CnLights)
	{
		this->LightsToUse.push_back(ii);
	}
	for (auto& ii : this-> ArLights)
	{
		this->LightsToUse.push_back(ii);
	}

}
 
void Game::initUniforms()
{
	for (auto& ii : this->shaders)
	{
		ii->setMat4fv(ViewMatrix, "ViewMatrix");
		ii->setMat4fv(ProjectionMatrix, "ProjectionMatrix");
		int Value = 0;
		for (auto& jj : this->DirLights)
		{
			std::string LightPos = "AllLightInf[" + std::to_string(Value) + "].LightPos";
			std::string LightClr = "AllLightInf[" + std::to_string(Value) + "].LightColor";
			ii->setVec3f(jj->GetPos(), LightPos.c_str());
			ii->setVec3f(jj->GetColor(), LightClr.c_str());
			Value++;
		}
	}
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
	if (glfwGetKey(this->window, GLFW_KEY_J) == GLFW_PRESS)
	{
		this->LightsToUse[0]->Move( glm::vec3(1.f, 0.f, 0.f));
	}
	if (glfwGetKey(this->window, GLFW_KEY_K) == GLFW_PRESS)
	{
		this->LightsToUse[0]->Move(glm::vec3(-1.f, 0.f, 0.f));
	}
	if (glfwGetKey(this->window, GLFW_KEY_I) == GLFW_PRESS)
	{
		this->LightsToUse[0]->Move(glm::vec3(0.f, 0.f, 1.f));
	}
	if (glfwGetKey(this->window, GLFW_KEY_U) == GLFW_PRESS)
	{
		this->LightsToUse[0]->Move(glm::vec3(0.f, 0.f, -1.f));
	}
	if (glfwGetKey(this->window, GLFW_KEY_O) == GLFW_PRESS)
	{
		this->LightsToUse[0]->Move(glm::vec3(0.f, -1.f, 0.f));
	}
	if (glfwGetKey(this->window, GLFW_KEY_P) == GLFW_PRESS)
	{
		this->LightsToUse[0]->Move(glm::vec3(0.f, 1.f, 0.f));
	}
	if (glfwGetKey(this->window, GLFW_KEY_Y) == GLFW_PRESS)
	{
		this->LightsToUse[0]->SetPosition(glm::vec3(0.f,this->MipMapsData[0]->ReturnValue(0.f,0.f), 0.f));
	}
	//End Game
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}

	//Camera	
	if (glfwGetKey(this->window , GLFW_KEY_W) == GLFW_PRESS)
	{
		this->camera.move(this->dt, FORWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->camera.move(this->dt, BACKWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->camera.move(this->dt, LEFT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->camera.move(this->dt, RIGHT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		this->camera.move(this->dt, UP);
	}

	//None Camera inputs
	if (glfwGetKey(this->window, GLFW_KEY_C) == GLFW_PRESS)
	{
		this->MouseToUse.SetMouseCenter(this->window,this->Window_Width, this->Window_Height);
	}

}

void Game::updateMouseInput()
{
	this->MouseToUse.UpdateMouseInput(this->window);
	if (this->MakeMesh)
	{
		if (!this->MouseToUse.UpdateMouse2dInput(this->window, {this->ScreenPos,this->WinSize}))
		{

			if (this->MouseToUse.MouseButtonClicked(this->window, GLFW_MOUSE_BUTTON_1))
			{
				this->SpaceLoc = this->MouseToUse.NewPosition(this->MipMapsData[0],
					{frameBufferWidth,frameBufferHeight },
					this->ProjectionMatrix,
					this->ViewMatrix,
					this->camera.getPosition());
			}
			if (this->MouseToUse.MouseButtonClicked(this->window, GLFW_MOUSE_BUTTON_2))
			{

			}
		}
	}
	else
	{
		this->camera.updateInput(dt, -1, this->MouseToUse.GetOffset());
	}

}

void Game::updateInput()
{
	glfwPollEvents();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	this->updateOpenGLOptions();
	this->updateKeyboardInput();
	this->updateMouseInput();
	this->updateController();
}

void Game::updateController()
{
	if (this->CheckCntrl.ControllerExist())
	{
		std::vector<float> Vals = this->CheckCntrl.GetRightAnalogVals();
		std::vector<float> Axis_acc = this->CheckCntrl.GetAxisRate();
		float Val0 =  Vals[0] * Axis_acc[0];
		float Val1 = Vals[1] * Axis_acc[1];
		this->camera.updateMouseInput(this->dt,Val0, Val1);
		this->camera.move(this->dt * this->CheckCntrl.GetLeftAnalogVals()[1], FORWARD);
		this->camera.move(this->dt * this->CheckCntrl.GetLeftAnalogVals()[0], RIGHT);
		if (this->CheckCntrl.AButtonPressed())
		{
			this->camera.move(this->dt, UP);
		}
		if (this->CheckCntrl.BButtonPressed())
		{
			this->camera.move(this->dt, DOWN);
		}
		if (this->CheckCntrl.MenuButtonPressed())
		{

			glfwSetWindowShouldClose(this->window, GLFW_TRUE);
		}
		if (this->CheckCntrl.LeftBumperPressed())
		{

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDisable(GL_CULL_FACE);
		}
		else if (this->CheckCntrl.RightBumperPressed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);
		}
	}
}
 
void Game::ImGuiOptions()
{
	if (this->OtherWindow) 
	{
		this->DrawFileInfo();
	}
}

void Game::updateUniforms()
{
	//Update uniforms
	this->ViewMatrix = this->camera.GetViewMatrix();

	int DirLightCount = this->DirLights.size();
	int CnLightCount = this->CnLights.size();
	int ArLightCount = this->ArLights.size();
	for (auto& ii :this->shaders)
	{ 
		ii->set1i(DirLightCount, "DirLightCount");
		ii->set1i(CnLightCount, "CnLightCount");
		ii->set1i(ArLightCount,"ArLightCount");
		int Value = 0;
		for (auto& jj: this->DirLights)
		{
			//Standard information
			std::string LightPos = "AllDirInfo[" + std::to_string(Value) + "].LightPos";
			std::string LightClr = "AllDirInfo[" + std::to_string(Value) + "].LightColor";
			ii->setVec3f(jj->GetPos(),  LightPos.c_str());
			ii->setVec3f(jj->GetColor(), LightClr.c_str());
			//Light Prop Info
			std::string LightAmbient = "AllDirInfo[" + std::to_string(Value) + "].Ambient";
			std::string LightDiffuse = "AllDirInfo[" + std::to_string(Value) + "].Diffuse";
			std::string LightSpecular = "AllDirInfo[" + std::to_string(Value) + "].Specular";
			ii->setVec3f(jj->GetAmbient(), LightAmbient.c_str());
			ii->setVec3f(jj->GetDiffuse(), LightDiffuse.c_str());
			ii->setVec3f(jj->GetSpecular(), LightSpecular.c_str());
			Value++;
		}
		Value = 0;
		for (auto& jj : this->CnLights)
		{
			std::string LightPos = "AllCnInfo[" + std::to_string(Value) + "].LightPos";
			std::string LightClr = "AllCnInfo[" + std::to_string(Value) + "].LightColor";
			std::string LightDir = "AllCnInfo[" + std::to_string(Value) + "].LightDirection";
			ii->setVec3f(jj->GetPos(), LightPos.c_str());
			ii->setVec3f(jj->GetColor(), LightClr.c_str());
			ii->setVec3f(jj->GetFront(), LightDir.c_str());
			//Light Prop Info
			std::string LightAmbient = "AllCnInfo[" + std::to_string(Value) + "].Ambient";
			std::string LightDiffuse = "AllCnInfo[" + std::to_string(Value) + "].Diffuse";
			std::string LightSpecular = "AllCnInfo[" + std::to_string(Value) + "].Specular";
			ii->setVec3f(jj->GetAmbient(), LightAmbient.c_str());
			ii->setVec3f(jj->GetDiffuse(), LightDiffuse.c_str());
			ii->setVec3f(jj->GetSpecular(), LightSpecular.c_str());
			//Cone Information
			std::string LightCnAngle = "AllCnInfo[" + std::to_string(Value) + "].ConeAngle";
			ii->setVec1f(glm::cos(glm::radians(jj->GetCone())), LightCnAngle.c_str());
			Value++;
		}
		Value = 0;
		for (auto& jj : this->ArLights)
		{
			//General Light info
			std::string LightPos = "AllArInfo[" + std::to_string(Value) + "].LightPos";
			std::string LightClr = "AllArInfo[" + std::to_string(Value) + "].LightColor";
			std::string LightDir = "AllArInfo[" + std::to_string(Value) + "].LightDirection";

			ii->setVec3f(jj->GetPos(), LightPos.c_str());
			ii->setVec3f(jj->GetColor(), LightClr.c_str());
			ii->setVec3f(jj->GetFront(), LightDir.c_str());
			//Light Prop Info
			std::string LightAmbient = "AllArInfo[" + std::to_string(Value) + "].Ambient";
			std::string LightDiffuse = "AllArInfo[" + std::to_string(Value) + "].Diffuse";
			std::string LightSpecular = "AllArInfo[" + std::to_string(Value) + "].Specular";
			ii->setVec3f(jj->GetAmbient(), LightAmbient.c_str());
			ii->setVec3f(jj->GetDiffuse(), LightDiffuse.c_str());
			ii->setVec3f(jj->GetSpecular(), LightSpecular.c_str());
			//Cone Info
			std::string LightCnAngle = "AllArInfo[" + std::to_string(Value) + "].ConeAngle";
			std::string LightUmAngle = "AllArInfo[" + std::to_string(Value) + "].UmbraAngle";
			ii->setVec1f(glm::cos(glm::radians(jj->GetCone())), LightCnAngle.c_str());
			ii->setVec1f(glm::cos(glm::radians(jj->GetUmbra())),LightUmAngle.c_str());
			//Light Constants
			std::string LightLin = "AllArInfo["+ std::to_string(Value) + "].Linear";
			std::string LightConst = "AllArInfo[" + std::to_string(Value) + "].Constant";
			std::string LightQuad = "AllArInfo[" + std::to_string(Value) + "].Quadratic";
			ii->setVec1f(jj->GetConstant(), LightConst.c_str());
			ii->setVec1f(jj->GetLinear(), LightLin.c_str());
			ii->setVec1f(jj->GetQuad(), LightQuad.c_str());
		}
		ii->setMat4fv(this->ViewMatrix, "ViewMatrix");
		ii->setVec3f(this->camera.getPosition(), "cameraPos");
	}
	//Update FrameBuffer size and projection matrix
	glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);
	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(glm::radians(this->fov),
		static_cast<float>(this->frameBufferWidth) / static_cast<float>(this-> frameBufferHeight),
		this->nearPlane,
		this->farPlane);
	for (auto& ii : this->shaders)
	{
		ii->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");
	}
}

std::vector<glm::mat4> Game::updateShadows()
{
	std::vector<glm::mat4> ReturnMatrix;
		int Count = 0;
	for (auto& ii : this->Shadows)
		{
			glm::mat4 TempVal = this->LightsToUse[Count]->GetLightMatrix(this->worldUp);
			ii->WriteToBuffer(this->Window_Width, this->Window_Height,
				this->shaders[3],TempVal);
			for (auto& jj : this->models)
			{
				jj->RenderShadow(this->shaders[3]);
			}
			ReturnMatrix.push_back(TempVal);
			Count++;
		}
	return ReturnMatrix;
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
	GLVerMajor(GLmajorVer), GLVerMinor(GLminorVer),
	camera(glm::vec3(0.f,1.f,0.f),glm::vec3(0.f,0.f,1.f),glm::vec3(0.f,0.f,1.f)),
	RdMkFiles("SaveFiles/Models/"),AnimRdrMk("SaveFiles/Animations/"),
	CheckCntrl(GLFW_JOYSTICK_1)
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
	this->camera.SetPos(glm::vec3(0.f,0.f ,this->MipMapsData[HEIGHTMAP_1]->ReturnValue(0.f, 0.f) + 1.f));
	const char* glsl_version = "#version 130";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	//ImGui::StyleColorsClassic();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

Game::~Game()
{
	ImGui::DestroyContext();
	glfwDestroyWindow(this->window );
	glfwTerminate();
	for (auto& ii : this->MatTest)
		delete ii;
	for (auto& i : meshes)
		delete i;
	for (auto& ii : animMeshes)
		delete ii;
	for (size_t i = 0; i < this->shaders.size(); i++)
			delete this->shaders[i];
	for (size_t i = 0; i < this->textures.size(); i++)
		delete this->textures[i];
	for (auto& ii : this->LightsToUse)
		delete ii;
	for (auto*& i : this->models)
		delete i;
	for (auto*& i : this->animModel)
		delete i;
	for (auto& ii : this->MipMapsData)
		delete ii;	
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
	this->CheckCntrl.UpdateVals(this->dt);
	this->updateDT();
	this->updateInput();
	this->ImGuiOptions();
	if (!this->SliderAnim)
	{
		this->TimePass = this->dt;
	}

	for (auto& ii : this->animModel)
	{
		ii->UpdateCollisions();
	}
}

void Game::render()
{
	//DRAW---
	//Updating Shadows Textures
	std::vector<glm::mat4> TempVal = this->updateShadows();
	//Clear
	ImGui::Render();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, this->Window_Width, this->Window_Height);
	glClearColor(this->SkyColor.r, this->SkyColor.g, this->SkyColor.b, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//Update uniforms
	this->updateUniforms();
	//render Models
	for (auto& ii : this->models)
	{
		ii->TestRender(this->shaders,TempVal);
	}
	for (auto& ii : this->animModel)
	{	
		ii->Render(this->TimePass, this->shaders, TempVal,this->StarAnim,this->SliderAnim,this->TransAnims,this->BlendAnims);
	}
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

bool Game::CheckNum(int Num)
{
	if (Num == this->NewTexId0)
	{
		return true;
	}
	else if (Num == this->NewTexId1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::LoadNewModels(std::vector<MdlToMake> FromFile)
{
	for (auto& ii : FromFile)
	{
		std::vector<MeshsArtifacts> TempArt;
		std::vector<Mesh*> MeshesToUse;
		std::vector<GeneralTextInfo*> TexToUse;
		for (auto& jj : ii.MeshesName)
		{
			for (auto& kk : this->meshes)
			{
				std::string MeshName = kk->GiveName();
				std::string FileMeshName = jj;
				if (MeshName == FileMeshName)
				{
					MeshesToUse.push_back(kk);
					break;
				}
			}
		}
		for (auto& jj : ii.TexNames)
		{
			for (auto& kk : this->textures)
			{
				std::string TexName = kk->GiveChar();
				std::string FileTexName = jj;
				if (TexName == FileTexName)
				{
					TexToUse.push_back(kk);
					break;
				}
			}
		}
		for (auto& jj : ii.NodesInf)
		{
			TempArt.push_back(MeshsArtifacts(jj.Pos, jj.Origin, jj.Rot, jj.Scale, jj.MeshId, jj.ParentId, jj.TexId));
		}
		this->models.push_back(new Model(ii.NewName.c_str(), ii.NewPos,
			this->MatTest[ii.MatId], TexToUse, MeshesToUse, TempArt, ii.NewRot));
	}
}

void Game::ReleaseModels()
{
	this->models.clear();
}
//IMGui Drawing Screens
void Game::DrawFileInfo()
{

	ImGui::Begin("test", &this->OtherWindow);
	static int clicked = 0;
	if (ImGui::Button("Read Button"))
	{
		RdMkFiles.GetFilesFolder();
	}
	std::vector<std::string> Files = RdMkFiles.GetAllFiles();
	int Count = 0;
	if (Files.size() != 0)
	{
		for (auto& jj : Files)
		{
			if (ImGui::Selectable(jj.c_str(), this->FileID == Count))
			{
				this->FileID = Count;
			}
			Count++;
		}
		ImGui::Text(std::to_string(this->FileID).c_str());
	}
	else
	{
		ImGui::Text("No Files to Choose from");
	}
	std::string TempName = "asdf";
	static char Name[100] = "";
	ImGui::InputText(TempName.c_str(), Name, IM_ARRAYSIZE(Name));
	if (ImGui::Button("Make File"))
	{
		FileSave = RdMkFiles.VerifyName(this->models, Name);
	}
	ImGui::Text(FileSave.c_str());
	if (ImGui::Button("Load File") && this->FileID != -1)
	{
		this->ReleaseModels();
		this->LoadNewModels(RdMkFiles.DecipherFile(this->FileID));
		this->FileID = -1;
	}

	ImGui::End();
}

void Game::DrawAnimInfo()
{
	ImGui::Begin("Add Animation", &this->AddAnim);
	std::string TempName = "Name of File";
	static char Name[100] = "";
	ImGui::InputText(TempName.c_str(), Name, IM_ARRAYSIZE(Name));
	static float NewLength = 0.001f;
	ImGui::InputFloat("Input Length (s)", &NewLength, 0.001f, .01f, "%.3f");
	if (ImGui::Button("Add Animation"))
	{
		this->animModel[this->AnimModelToMake]->AddAnimation(Name, NewLength);
		this->AddAnim = false;
	}
	ImGui::End();
}

void Game::DrawColAdd()
{
	std::string Title = "add shape to Body " + std::to_string(this->BodId);
	Title += " for parent " + std::to_string(this->ShapeID);
	ImGui::Begin(Title.c_str());
	if (ImGui::Button("Close Shape"))
	{
		this->AddShape = false;
	}
	ImGui::End();
}