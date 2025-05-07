//Laboratorio Computacion Grafica Grupo 06
//Proyecto Final
//Alumno: Rangel de la Rosa José Refugio
//num. de cuenta: 420054559


/*
	Seguimiento de Actividades
		25-04-2025 -> Creacion de repositorio y configuraciones iniciales.
		03-05-2025 -> Prueba de carga de modelos (PC, Escritorio, Mouse, Monitor, Aspiradora, Silla)
		04-05-2025 -> Correccion de modelos y distribucion inicial (PC, Escritorio, Mouse, Monitor, Aspiradora)
		05-05-2025 -> Animacion de aspiradora
		05-05-2025 -> Corrección modelo silla
		06-05-2025 -> Publicidad
		06-05-2025 -> Patrocinios
		06-05-2025 -> Animacion de puerta
*/

#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void Animation();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,2.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f,  0.0f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};



glm::vec3 Light1 = glm::vec3(0);
//Anim
//float rotBall = 0.0f;
//bool AnimBall = false;
//bool AnimDog = false;
//float rotDog = 0.0f;
//bool dogAnim = false;
//float FLegs = 0.0f;
//float RLegs = 0.0f;
//float head = 0.0f;
//float tail = 0.0f;
//glm::vec3 dogPos(0.0f, 0.0f, 0.0f);
//float dogRot = 0.0f;
//bool step = false;

//Variables aspiradora
bool Animaspiradora = false;
bool haciaDerecha = true;
float rotElice = 0.0f;
float movXaspiradora = 24.0f;
float movXInicial = 0.0f;
bool inicioAtrasX = true;
float movZaspiradora = 18.0f;
float rotaspiradora = 0.0f;

enum EstadoAspiradora {
	ATRAS_Z,
	ROTA_Y1,
	ROTA_Y11,
	ADELANTE_Z,
	ROTA_Y2,
	ROTA_Y22,
	ATRAS_X,
	REGRESA_ROTAR_Y, 
	REGRESA_X, 
	ROTA_FIN,
	IDLE
};

EstadoAspiradora estadoActual = ATRAS_Z;
EstadoAspiradora estadoAnterior;


//Variables monitor
bool Animocultar = false;
bool Animostrar = false;
float rotXtubo = 0.0f;
float movZtubo = 0.1f;
float movYtubo = 1.3f;
float rotYtubo = 0.0f;

enum EstadoMonitor {
	ROT_Y_TUBO,
	ROT_Y_TUBO2,
	MOV_Y_TUBO,
	MOV_Y_TUBO2,
	ROT_X_TUBO,
	ROT_X_TUBO2,
	OCULTAR,
	MOSTRAR,
};
EstadoMonitor estadoMonitor = MOSTRAR;

//Variables Luces
bool Animluces = false;
glm::vec3 ambientColor(0.0f, 0.0f, 0.0f);
glm::vec3 diffuseColor(0.0f, 0.0f, 0.0f);
glm::vec3 specularColor(0.0f, 0.0f, 0.0f);

glm::vec3 ambientColor2(0.0f, 0.0f, 0.0f);
glm::vec3 diffuseColor2(0.0f, 0.0f, 0.0f);
glm::vec3 specularColor2(0.0f, 0.0f, 0.0f);

//Movimiento puerta
bool AnimPuerta = false;
glm::vec3 posPuerta(-11.75f, 0.0f, 15.25);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Rangel de la Rosa Jose Refugio", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

	//models
	Model Mesa((char*)"Models/mesa/mesa.obj");
	Model Piso((char*)"Models/piso/piso.obj");
	Model PC((char*)"Models/pc/pc.obj");
	Model Mouse((char*)"Models/mouse/mouse.obj");
	Model BaseAspiradora((char*)"Models/aspiradora/base.obj");
	Model EliceAspiradora((char*)"Models/aspiradora/elice.obj");
	Model Lampara((char*)"Models/lampara/lampara.obj");
	Model Silla((char*)"Models/silla/silla.obj");
	Model Teclado((char*)"Models/teclado/teclado.obj");
	Model Animacion2D((char*)"Models/publicidad/animacion.obj");
	Model Blender((char*)"Models/publicidad/blender.obj");
	Model Unity((char*)"Models/publicidad/unity.obj");
	Model Diplomado((char*)"Models/publicidad/diplomado.obj");
	Model AMD((char*)"Models/patrocinios/AMD.obj");
	Model NVIDIA((char*)"Models/patrocinios/NVIDIA.obj");
	Model ASUS((char*)"Models/patrocinios/ASUS.obj");
	Model Logitech((char*)"Models/patrocinios/LOGITECH.obj");
	Model UNAM((char*)"Models/patrocinios/UNAM.obj");
	Model FI((char*)"Models/patrocinios/FI.obj");
	Model DIE((char*)"Models/patrocinios/DIE.obj");
	Model IC((char*)"Models/patrocinios/IC.obj");
	Model Pared((char*)"Models/patrocinios/blanco.obj");
	Model Muro ((char*)"Models/muro/muro.obj");
	Model BaseMonitor((char*)"Models/monitor/base.obj");
	Model Tubo1Monitor((char*)"Models/monitor/tubo1.obj");
	Model Tubo2Monitor((char*)"Models/monitor/tubo2.obj");
	Model CilindroMonitor((char*)"Models/monitor/cilindro.obj");
	Model ScreenMonitor((char*)"Models/monitor/screen.obj");
	Model Pizarron((char*)"Models/pizarron/pizarron1.obj");


	//Ubicaciones PC
	std::vector<glm::vec3> posicionesPC = {
		// Primera fila
		glm::vec3(-7.968f, 1.558f, -11.568f),
		glm::vec3(-4.353f, 1.558f, -11.568f),
		glm::vec3(-0.738f, 1.558f, -11.568f),
		glm::vec3(2.877f, 1.558f, -11.568f),
		// Segunda fila
		glm::vec3(-7.968f, 1.558f, -5.0f),
		glm::vec3(-4.353f, 1.558f, -5.0f),
		glm::vec3(-0.738f, 1.558f, -5.0f),
		glm::vec3(2.877f, 1.558f, -5.0f),
		// Segunda fila
		glm::vec3(-7.968f, 1.558f, 1.568f),
		glm::vec3(-4.353f, 1.558f, 1.568f),
		glm::vec3(-0.738f, 1.558f, 1.568f),
		glm::vec3(2.877f, 1.558f, 1.568f),
		// Segunda fila
		glm::vec3(-7.968f, 1.558f, 8.136f),
		glm::vec3(-4.353f, 1.558f, 8.136f),
		glm::vec3(-0.738f, 1.558f, 8.136f),
		glm::vec3(2.877f, 1.558f,  8.136f),
	};

	std::vector<glm::vec3> posicionesPC2 = {
		// Primera fila
		glm::vec3(11.877f, 1.558f, -11.568f),
		glm::vec3(15.492f, 1.558f, -11.568f),
		glm::vec3(19.107f, 1.558f, -11.568f),
		glm::vec3(22.722f, 1.558f, -11.568f),
		// Segunda fila
		glm::vec3(11.877f, 1.558f, -5.0f),
		glm::vec3(15.492f, 1.558f, -5.0f),
		glm::vec3(19.107f, 1.558f, -5.0f),
		glm::vec3(22.722f, 1.558f, -5.0f),
		// Segunda fila
		glm::vec3(11.877f, 1.558f, 1.568f),
		glm::vec3(15.492f, 1.558f, 1.568f),
		glm::vec3(19.107f, 1.558f, 1.568f),
		glm::vec3(22.722f, 1.558f, 1.568f),
		// Segunda fila
		glm::vec3(11.877f, 1.558f, 8.136f),
		glm::vec3(15.492f, 1.558f, 8.136f),
		glm::vec3(19.107f, 1.558f, 8.136f),
		glm::vec3(22.722f, 1.558f, 8.136f),
	};

	std::vector<glm::vec3> posicionesLamparas = {
		// Primera fila
		glm::vec3(18.5f, 15.0, -7.0f),
		glm::vec3(18.5f, 15.0, 6.0f),
		glm::vec3(-3.0f, 15.0, -7.0f),
		glm::vec3(-3.0f, 15.0, 6.0f),
	};

	std::vector<glm::vec3> posicionesLuces = {
		// Primera fila
		glm::vec3(18.5f, 9.5f, -7.0f),
		glm::vec3(18.5f, 9.5f, 6.0f),
		glm::vec3(-3.0f, 9.5f, -7.0f),
		glm::vec3(-3.0f, 9.5f, 6.0f),
	};

	std::vector<glm::vec3> posicionesPanel = {
		glm::vec3(18.5f, 0.0f, 0.0f),
		glm::vec3(18.5f, 0.0f, 0.0f),

	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		Animation();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);


		glm::mat4 modelTemp1 = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

		glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);  // Dirección del sol
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.3f, 0.25f, 0.2f);       // Luz ambiental cálida
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 1.0f, 0.85f, 0.55f);      // Luz difusa brillante
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 1.0f, 1.0f, 0.9f);

		if (Animluces) {
			ambientColor2 = glm::vec3(0.4f, 0.4f, 0.4f);   // Luz ambiental tenue
			diffuseColor2 = glm::vec3(1.0f, 1.0f, 1.0f);  // Luz principal cálida
			specularColor2 = glm::vec3(1.0f, 1.0f, 1.0f);  // Reflejo blanco brillante
		}
		else {
			ambientColor2 = glm::vec3(0.0f, 0.0f, 0.0f);   // Luz ambiental tenue
			diffuseColor2 = glm::vec3(0.0f, 0.0f, 0.0f);  // Luz principal cálida
			specularColor2 = glm::vec3(0.0f, 0.0f, 0.0f);  // Reflejo blanco brillante
		}

		for (size_t i = 0; i < posicionesLuces.size(); ++i) {
			std::string base = "pointLights[" + std::to_string(i) + "].";

			glUniform3f(glGetUniformLocation(lightingShader.Program, (base + "position").c_str()), posicionesLuces[i].x, posicionesLuces[i].y, posicionesLuces[i].z);
			glUniform3f(glGetUniformLocation(lightingShader.Program, (base + "ambient").c_str()), ambientColor2.r, ambientColor2.g, ambientColor2.b);
			glUniform3f(glGetUniformLocation(lightingShader.Program, (base + "diffuse").c_str()), diffuseColor2.r, diffuseColor2.g, diffuseColor2.b);
			glUniform3f(glGetUniformLocation(lightingShader.Program, (base + "specular").c_str()), specularColor2.r, specularColor2.g, specularColor2.b);
			glUniform1f(glGetUniformLocation(lightingShader.Program, (base + "constant").c_str()), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, (base + "linear").c_str()), 0.045f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, (base + "quadratic").c_str()), 0.075f);
		}

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));


		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);
		//Carga de modelo 
		view = camera.GetViewMatrix();

		//Mapa
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(4.5f, 1.0f, 4.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lightingShader);


		//PC PROFESOR
			modelTemp1 = glm::mat4(1);
			model = glm::mat4(1);
			model = glm::translate(model, glm::vec3(7.0f, 1.558f, -18.0f));
			modelTemp1 = model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Mesa.Draw(lightingShader);

			model = glm::translate(modelTemp1, glm::vec3(-1.2591f, 0.0f, -0.122f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			PC.Draw(lightingShader);

			model = glm::translate(modelTemp1, glm::vec3(1.2f, 0.0f, 0.4f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Mouse.Draw(lightingShader);

			model = glm::translate(modelTemp1, glm::vec3(0.0f, -1.558f, 1.5f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Silla.Draw(lightingShader);

			model = glm::translate(modelTemp1, glm::vec3(0.1f, 0.0f, 0.4f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Teclado.Draw(lightingShader);

			modelTemp2 = model = glm::translate(modelTemp1, glm::vec3(0.4f, 0.0f, -0.9f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			BaseMonitor.Draw(lightingShader);

		model = glm::translate(modelTemp2, glm::vec3(0.0f, -0.5f, -0.15f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Tubo1Monitor.Draw(lightingShader);

		model = glm::rotate(model, glm::radians(rotYtubo), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTemp2 = model = glm::translate(model, glm::vec3(0.0f, movYtubo, movZtubo));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Tubo2Monitor.Draw(lightingShader);

		model = glm::translate(modelTemp2, glm::vec3(0.0f, 0.0f, 0.45f));
		model = glm::rotate(model, glm::radians(rotXtubo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CilindroMonitor.Draw(lightingShader);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ScreenMonitor.Draw(lightingShader);


		for (const glm::vec3& posicion : posicionesPC) {
			
			modelTemp1 = glm::mat4(1);
			model = glm::mat4(1);
			modelTemp1 = model = glm::translate(model, posicion);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Mesa.Draw(lightingShader);

			model = glm::translate(modelTemp1, glm::vec3(-1.2591f, 0.0f, -0.122f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			PC.Draw(lightingShader);
			
			model = glm::translate(modelTemp1, glm::vec3(1.2f, 0.0f, 0.4f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Mouse.Draw(lightingShader);
			
			model = glm::translate(modelTemp1, glm::vec3(0.0f, -1.558f, 1.5f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Silla.Draw(lightingShader);
			
			model = glm::translate(modelTemp1, glm::vec3(0.1f, 0.0f, 0.4f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Teclado.Draw(lightingShader);
			
			modelTemp2 = model = glm::translate(modelTemp1, glm::vec3(0.4f, 0.0f, -0.9f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			BaseMonitor.Draw(lightingShader);
			
			model = glm::translate(modelTemp2, glm::vec3(0.0f, -0.5f, -0.15f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Tubo1Monitor.Draw(lightingShader);
		
			model = glm::rotate(model, glm::radians(rotYtubo), glm::vec3(0.0f, 1.0f, 0.0f));
			modelTemp2 = model = glm::translate(model, glm::vec3(0.0f, movYtubo, movZtubo));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Tubo2Monitor.Draw(lightingShader);
			
			model = glm::translate(modelTemp2, glm::vec3(0.0f, 0.0f, 0.45f));
			model = glm::rotate(model, glm::radians(rotXtubo), glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			CilindroMonitor.Draw(lightingShader);
			
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			ScreenMonitor.Draw(lightingShader);
		}



		for (const glm::vec3& posicion : posicionesPC2) {
			
			modelTemp1 = glm::mat4(1);
			model = glm::mat4(1);
			modelTemp1 = model = glm::translate(model, posicion);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Mesa.Draw(lightingShader);

			model = glm::translate(modelTemp1, glm::vec3(1.2591f, 0.0f, -0.122f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			PC.Draw(lightingShader);
			
			model = glm::translate(modelTemp1, glm::vec3(0.6f, 0.0f, 0.4f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Mouse.Draw(lightingShader);
			
			model = glm::translate(modelTemp1, glm::vec3(-0.4f, -1.558f, 1.5f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Silla.Draw(lightingShader);
			
			model = glm::translate(modelTemp1, glm::vec3(-0.6f, 0.0f, 0.4f));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Teclado.Draw(lightingShader);
			
			modelTemp2 = model = glm::translate(modelTemp1, glm::vec3(-0.4f, 0.0f, -0.9f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			BaseMonitor.Draw(lightingShader);
			
			model = glm::translate(modelTemp2, glm::vec3(0.0f, -0.5f, -0.15f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Tubo1Monitor.Draw(lightingShader);
		
			model = glm::rotate(model, glm::radians(rotYtubo), glm::vec3(0.0f, -1.0f, 0.0f));
			modelTemp2 = model = glm::translate(model, glm::vec3(0.0f, movYtubo, movZtubo));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Tubo2Monitor.Draw(lightingShader);
			
			model = glm::translate(modelTemp2, glm::vec3(0.0f, 0.0f, 0.45f));
			model = glm::rotate(model, glm::radians(rotXtubo), glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			CilindroMonitor.Draw(lightingShader);
			
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			ScreenMonitor.Draw(lightingShader);
		}


		// Aspiradora
		model = glm::mat4(1.0f);
		// 1. Posicionamiento inicial en el mundo
		model = glm::translate(model, glm::vec3(movXaspiradora, 0.0f, movZaspiradora));
		model = glm::scale(model, glm::vec3(0.5f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		// Aplicar traslación dinámica en X y Y
		// Aplicar rotación en Y (alrededor del eje Y)
		modelTemp1 = model = glm::rotate(model, glm::radians(rotaspiradora), glm::vec3(0.0f, 1.0f, 0.0f));
		// Guarda esta transformación base si es necesaria para otros elementos como hélices
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BaseAspiradora.Draw(lightingShader);

		
		model = glm::translate(modelTemp1, glm::vec3(0.984f, 0.081f, 0.984f));
		model = glm::rotate(model, glm::radians(rotElice), glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		EliceAspiradora.Draw(lightingShader);

		
		model = glm::translate(modelTemp1, glm::vec3(-0.984f, 0.081f, 0.984f));
		model = glm::rotate(model, glm::radians(rotElice), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		EliceAspiradora.Draw(lightingShader);

		//Pizarron1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(18.5f, 0.0f, -20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pizarron.Draw(lightingShader);

		//Pizarron2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, -20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pizarron.Draw(lightingShader);

		//Animacion2D
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-13.0f, 0.0f, -10.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Animacion2D.Draw(lightingShader);

		//Blender
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-13.0f, 0.0f, -5.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Blender.Draw(lightingShader);

		//Unity
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-13.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Unity.Draw(lightingShader);

		//Diplomado
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-13.0f, 0.0f, 6.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Diplomado.Draw(lightingShader);

		//AMD
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-12.0f, 0.0f, -3.25f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		AMD.Draw(lightingShader);

		//NVIDIA
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-12.0f, 0.0f, 6.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		NVIDIA.Draw(lightingShader);

		//Asus
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-12.0f, 0.0f, -12.5));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ASUS.Draw(lightingShader);

		//Logitech
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-12.0f, 0.0f, -21.75));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Logitech.Draw(lightingShader);

		//UNAM
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(25.25f, 0.0f, 6.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		UNAM.Draw(lightingShader);

		//FI
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(25.25f, 0.0f, -3.25));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		FI.Draw(lightingShader);

		//DIE
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(25.25f, 0.0f, -12.5));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DIE.Draw(lightingShader);

		//IC
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(25.25f, 0.0f, -21.75));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		IC.Draw(lightingShader);

		//PARED1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(25.25f, 0.0f, 15.25));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pared.Draw(lightingShader);

		//PARED1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(20.625, 0.0f, 19.875f));
		model = glm::scale(model, glm::vec3(0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pared.Draw(lightingShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(11.375, 0.0f, 19.875f));
		model = glm::scale(model, glm::vec3(0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pared.Draw(lightingShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.125f, 0.0f, 19.875f));
		model = glm::scale(model, glm::vec3(0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pared.Draw(lightingShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-7.125f, 0.0f, 19.875f));
		model = glm::scale(model, glm::vec3(0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pared.Draw(lightingShader);

		// Animación de la puerta
		if (AnimPuerta) {
			// Abrir puerta: mover de 15.25 a 6.0
			if (posPuerta.z > 6.0f) {
				posPuerta.z -= 0.01f;
				if (posPuerta.z < 6.0f)
					posPuerta.z = 6.0f; // evitar pasar el límite
			}
		}
		else {
			// Cerrar puerta: mover de 6.0 a 15.25
			if (posPuerta.z < 15.25f) {
				posPuerta.z += 0.01f;
				if (posPuerta.z > 15.25f)
					posPuerta.z = 15.25f;
			}
		}

		//Puerta deslizadora
		model = glm::mat4(1.0f);
		model = glm::translate(model, posPuerta);
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pared.Draw(lightingShader);

		//Muro Led
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-8.5f, 0.0f,-25.0f));
		model = glm::scale(model, glm::vec3(0.95f, 0.8f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Muro.Draw(lightingShader);

		//Lamparas
		for (const glm::vec3& posicion : posicionesLamparas) {
			model = glm::mat4(1);
			model = glm::translate(model, posicion);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Lampara.Draw(lightingShader);
		}

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		for (const glm::vec3& posicion : posicionesLuces) {
			model = glm::mat4(1);
			model = glm::translate(model, posicion);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			// Draw the light object (using light's vertex attributes)
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}

	if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += 0.01f;
	}
	if (keys[GLFW_KEY_G])
	{
		pointLightPositions[0].x -= 0.01f;
	}

	if (keys[GLFW_KEY_Y])
	{
		pointLightPositions[0].y += 0.01f;
	}

	if (keys[GLFW_KEY_H])
	{
		pointLightPositions[0].y -= 0.01f;
	}
	if (keys[GLFW_KEY_U])
	{
		pointLightPositions[0].z -= 0.1f;
	}
	if (keys[GLFW_KEY_J])
	{
		pointLightPositions[0].z += 0.01f;
	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (GLFW_KEY_P == key && GLFW_PRESS == action) {
		Animluces = !Animluces;
	}
	if (GLFW_KEY_L == key && GLFW_PRESS == action) {
		Animaspiradora = !Animaspiradora;
	}
	if (GLFW_KEY_O == key && GLFW_PRESS == action) {
		Animocultar = true;
	}
	if (GLFW_KEY_M == key && GLFW_PRESS == action) {
		Animostrar = true;
	}
	if (GLFW_KEY_I == key && GLFW_PRESS == action) {
		AnimPuerta = !AnimPuerta;
	}
}

void Animation() {
	if (!Animaspiradora) {
		return;
	}else{
		// Giran las hélices
		rotElice += 5.0f;
		switch (estadoActual) {
			case ATRAS_Z:
				movZaspiradora -= 0.1f;
				rotaspiradora = 0.0f;
				if (movZaspiradora <= -23.0f) {  
					estadoAnterior = estadoActual;
					estadoActual = ROTA_Y1;
				}
				break;

			case ADELANTE_Z:
				movZaspiradora += 0.1f;
				if (movZaspiradora >= 18.0f) {
					if (movXaspiradora < -9.0f) {
						estadoActual = REGRESA_ROTAR_Y;
					}
					else {
						estadoAnterior = estadoActual;
						estadoActual = ROTA_Y11;
					}
				}
				break;

			case ATRAS_X:
				if (inicioAtrasX) {
					movXInicial = movXaspiradora; 
					inicioAtrasX = false;
				}

				movXaspiradora -= 0.05f;
				if (movXaspiradora <= movXInicial - 2.0f) {
					if(estadoAnterior == ATRAS_Z)
						estadoActual = ROTA_Y2;
					if (estadoAnterior == ADELANTE_Z)
						estadoActual = ROTA_Y22;
					inicioAtrasX = true;
				}
				break;

			case ROTA_Y1:
				rotaspiradora += 1.0f;
				if (rotaspiradora >= 90.0f) {
					estadoActual = ATRAS_X;
				}
				break;

			case ROTA_Y2:
				rotaspiradora += 1.0f;
				if (rotaspiradora >= 180.0f) {
					estadoActual = ADELANTE_Z;
				}
				break;

			case ROTA_Y11:
				rotaspiradora -= 1.0f;
				if (rotaspiradora <= 90.0f) {
					estadoActual = ATRAS_X;
				}
				break;

			case ROTA_Y22:
				rotaspiradora -= 1.0f;
				if (rotaspiradora <= 0.0f) {
					estadoActual = ATRAS_Z;
				}
				break;

			case REGRESA_ROTAR_Y:
				rotaspiradora += 1.0f;
				if (rotaspiradora >= 270.0f) {
					estadoActual = REGRESA_X;
				}
				break;

			case REGRESA_X:
				movXaspiradora += 0.05f;
				if (movXaspiradora >= 24.0f) {
					estadoActual = ROTA_FIN;
				}
				break;
			case ROTA_FIN:
				rotaspiradora += 1.0f;
				if (rotaspiradora >= 360.0f) {
					estadoActual = IDLE;
				}
				break;

			case IDLE:
				rotElice = 0.0f;
				rotaspiradora = 0.0f;
				Animaspiradora = !Animaspiradora;
				estadoActual = ATRAS_Z;
				break;
		}
	}

	if (!Animocultar) {
		return;
	}
	else {
		switch (estadoMonitor) {
			case MOSTRAR:
				rotYtubo += 0.5f;
				if (rotYtubo >= 180.0f) {
					estadoMonitor = MOV_Y_TUBO;
				}
				break;

			case MOV_Y_TUBO:
				movYtubo -= 0.01f;
				if (movYtubo <= 0.03f) {
					estadoMonitor = ROT_X_TUBO;
				}
				break;

			case ROT_X_TUBO:
				rotXtubo += 0.5f;
				if (rotXtubo >= 90.0f) {
					estadoMonitor = ROT_Y_TUBO;
				}
				break;

			case ROT_Y_TUBO:
				rotYtubo += 0.5f;
				if (rotYtubo >= 360.0f) {
					estadoMonitor = OCULTAR;
					Animocultar = false;
					Animostrar = false;
				}
				break;
				
		}
	}

	if (!Animostrar) {
		return;
	}
	else {
		switch (estadoMonitor) {
		case OCULTAR:
			rotYtubo -= 0.5f;
			if (rotYtubo <= 180.0f) {
				estadoMonitor = ROT_X_TUBO2;
			}
			break;

		case ROT_X_TUBO2:
			rotXtubo -= 0.5f;
			if (rotXtubo <= 0.0f) {
				estadoMonitor = MOV_Y_TUBO2;
			}
			break;

		case MOV_Y_TUBO2:
			movYtubo += 0.01f;
			if (movYtubo >= 1.5f) {
				estadoMonitor = ROT_Y_TUBO2;
			}
			break;
		
		case ROT_Y_TUBO2:
			rotYtubo -= 0.5f;
			if (rotYtubo <= 0.0f) {
				estadoMonitor = MOSTRAR;
				Animostrar = false;
				Animocultar = false;
			}
			break;

		}
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}