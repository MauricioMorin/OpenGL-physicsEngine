#include"Model.h"

#include "Entity.h"
#include "Component.h"
#include "MovementSystem.h"
#include "PositionComponent.h"
#include "RenderSystem.h"
#include "MeshComponent.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "BallColliderComponent.h"
#include "BorderCollisionSystem.h"
#include "TransparentMeshComponent.h"
#include "BallCollisionSystem.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <stdio.h>
using namespace std;

const unsigned int width = 800;
const unsigned int height = 800;

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
	 
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

Vertex vertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       
	Vertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(0.5f, 0.0f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f), glm::vec2(1.0f, 0.0f)},

	Vertex{glm::vec3(-0.5f, 0.0f, 0.5f), glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.8f, 0.0f), glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f), glm::vec2(0.5f, 1.0f)},

	Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.8f, 0.0f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f), glm::vec2(0.5f, 1.0f)},

	Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.8f, 0.5f,  0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(0.8f, 0.5f,  0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.8f, 0.0f), glm::vec3(0.8f, 0.5f,  0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f), glm::vec2(0.5f, 1.0f)},

	Vertex{glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(0.0f, 0.5f,  0.8f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f, 0.0f, 0.5f), glm::vec3(0.0f, 0.5f,  0.8f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.8f, 0.0f), glm::vec3(0.0f, 0.5f,  0.8f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f), glm::vec2(0.5f, 1.0f)}
};


// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};


Vertex squareVerts[] = {
	Vertex{glm::vec3(-0.5f, -0.5f,  0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f,  0.5f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f,  0.5f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec4(1.0f, 1.0f, 1.0f,  0.5f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(0.5f, -0.5f,  0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f,  0.5f), glm::vec2(1.0f, 0.0f)},

	Vertex{glm::vec3(-0.5f, -0.5f,  0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 0.5f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f,  0.5f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),  glm::vec4(1.0f, 1.0f, 1.0f,  0.5f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(0.5f, -0.5f,  0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f,  0.5f), glm::vec2(1.0f, 0.0f)}
};

GLuint squareInts[] = {
	0, 1, 2,
	0, 2, 3,
	4, 5, 6,
	4, 6, 7
};


// Helper function to find the midpoint of two vertices
GLuint getMidpoint(GLuint v1, GLuint v2, std::unordered_map<uint64_t, GLuint>& midpointCache, std::vector<Vertex>& vertices, glm::vec4 color) {
	uint64_t smaller = v1 < v2 ? v1 : v2;
	uint64_t greater = v1 < v2 ? v2 : v1;
	uint64_t key = (smaller << 32) | greater;

	if (midpointCache.find(key) != midpointCache.end()) {
		return midpointCache[key];
	}

	glm::vec3 pos1 = vertices[v1].position;
	glm::vec3 pos2 = vertices[v2].position;
	glm::vec3 midpoint = glm::normalize((pos1 + pos2) * 0.5f);

	Vertex newVertex;
	newVertex.position = midpoint;
	newVertex.normal = midpoint;
	newVertex.color = color; // White color for simplicity
	newVertex.texUV = glm::vec2(0.5f + atan2(midpoint.z, midpoint.x) / (2 * glm::pi<float>()), 0.5f - asin(midpoint.y) / glm::pi<float>());

	vertices.push_back(newVertex);
	GLuint index = vertices.size() - 1;
	midpointCache[key] = index;

	return index;
}

void generateIcosphere(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, int subdivisions, glm::vec4 color= glm::vec4(0.75f, 0.6f, 0.95f, 1.0f)) {
	// Create an icosahedron
	const float t = (1.0f + glm::sqrt(5.0f)) / 2.0f;

	std::vector<glm::vec3> positions = {
		{-1,  t,  0}, { 1,  t,  0}, {-1, -t,  0}, { 1, -t,  0},
		{ 0, -1,  t}, { 0,  1,  t}, { 0, -1, -t}, { 0,  1, -t},
		{ t,  0, -1}, { t,  0,  1}, {-t,  0, -1}, {-t,  0,  1}
	};

	for (auto& pos : positions) {
		pos = glm::normalize(pos);
		vertices.push_back({ pos, pos, color, glm::vec2(0.5f + atan2(pos.z, pos.x) / (2 * glm::pi<float>()), 0.5f - asin(pos.y) / glm::pi<float>()) });
	}

	std::vector<GLuint> initialIndices = {
		0, 11, 5,  0, 5, 1,  0, 1, 7,  0, 7, 10,  0, 10, 11,
		1, 5, 9,  5, 11, 4,  11, 10, 2,  10, 7, 6,  7, 1, 8,
		3, 9, 4,  3, 4, 2,  3, 2, 6,  3, 6, 8,  3, 8, 9,
		4, 9, 5,  2, 4, 11,  6, 2, 10,  8, 6, 7,  9, 8, 1
	};

	indices = initialIndices;

	// Subdivide triangles
	std::unordered_map<uint64_t, GLuint> midpointCache;

	for (int i = 0; i < subdivisions; ++i) {
		std::vector<GLuint> newIndices;

		for (size_t j = 0; j < indices.size(); j += 3) {
			GLuint v1 = indices[j];
			GLuint v2 = indices[j + 1];
			GLuint v3 = indices[j + 2];

			GLuint a = getMidpoint(v1, v2, midpointCache, vertices, color);
			GLuint b = getMidpoint(v2, v3, midpointCache, vertices, color);
			GLuint c = getMidpoint(v3, v1, midpointCache, vertices, color);

			newIndices.push_back(v1); newIndices.push_back(a); newIndices.push_back(c);
			newIndices.push_back(v2); newIndices.push_back(b); newIndices.push_back(a);
			newIndices.push_back(v3); newIndices.push_back(c); newIndices.push_back(b);
			newIndices.push_back(a); newIndices.push_back(b); newIndices.push_back(c);
		}

		indices = newIndices;
	}
}

void generateCube(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, glm::vec4 color = glm::vec4(1.0f, 0.4f, 0.4f, 0.2f)) {
	// Define cube vertices
	glm::vec3 positions[] = {
		{-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f,  0.5f, -0.5f}, {-0.5f,  0.5f, -0.5f},
		{-0.5f, -0.5f,  0.5f}, {0.5f, -0.5f,  0.5f}, {0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f}
	};

	glm::vec3 normals[] = {
		{ 0.0f,  0.0f, -1.0f}, { 0.0f,  0.0f,  1.0f},
		{-1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f,  0.0f},
		{ 0.0f, -1.0f,  0.0f}, { 0.0f,  1.0f,  0.0f}
	};

	glm::vec2 texCoords[] = {
		{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}
	};

	// Vertices for each face
	int faceIndices[6][4] = {
		{3, 2, 6, 7},  // Top face
		{0, 4, 7, 3}, // Left face
		{4, 5, 6, 7}, // Front face
		{0, 1, 2, 3}, // Back face
		{1, 5, 6, 2}, // Right face
		{0, 1, 5, 4} // Bottom face
		
	};

	for (int i = 0; i < 6; ++i) {
		glm::vec3 normal = normals[i];

		for (int j = 0; j < 4; ++j) {
			int idx = faceIndices[i][j];
			vertices.push_back({ positions[idx], normal, color, texCoords[j] });
		}

		// Add two triangles per face
		int baseIndex = i * 4;
		indices.push_back(baseIndex + 0);
		indices.push_back(baseIndex + 1);
		indices.push_back(baseIndex + 2);
		indices.push_back(baseIndex + 0);
		indices.push_back(baseIndex + 2);
		indices.push_back(baseIndex + 3);
	}
}


int createBall(int id, ComponentManager& componentManager, Mesh sphere, float ballsize=0.5f) {
	Entity ball = id;

	// Assign a random or preset position
	glm::vec3 position = glm::vec3(static_cast<float>(rand() % 3 - 2), 1.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(ballsize); // Small sphere

	// Add transform component
	componentManager.AddComponent<TransformComponent>(ball, position, rotation, scale);

	// Add mesh component (assuming `sphere` is a predefined mesh)
	componentManager.AddComponent<MeshComponent>(ball, sphere);

	// Add physics component (gravity and bouncing behavior)
	glm::vec3 initialVelocity = glm::vec3(static_cast<float>(rand() % 6 - 0), static_cast<float>(rand() % 6 - 0), static_cast<float>(rand() % 6 - 0));
	glm::vec3 gravity = glm::vec3(0.0f, -9.81f, 0.0f);
	float restitution = 0.95f;
	//float mass = (4.0f / 3.0f) * 3.141592 * ballsize * ballsize * ballsize*300;
	//float mass = 100000.0f;
	float mass = (4.0f / 3.0f) * 3.141592 * ballsize * ballsize * ballsize;
	float friction = 0.10f;
	componentManager.AddComponent<PhysicsComponent>(ball, mass, initialVelocity, gravity, restitution, friction);

	// Add collider component (assuming a sphere collider with radius 0.1)
	componentManager.AddComponent<BallColliderComponent>(ball, ballsize);

	return ball;
}

int main() {
	
	//initializasition
	glfwInit();

	//version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "skibidi toillet lover", NULL, NULL);

	if (window == NULL) {
		cout << "No window ):" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Load Glad for OpenGL
	gladLoadGL();

	glViewport(0, 0, width, height);
		
	
	Texture textures[]
	{
		Texture("blue.png", "diffuse", 0),
		Texture("blue.png", "specular", 1)
	};

	Texture hexgridtex[]
	{
		Texture("check.png", "diffuse", 0),
		Texture("check.png", "specular", 1)
	};

	Texture hexgridtextures[]
	{
		Texture("blank.png", "diffuse", 0),
		Texture("blank.png", "specular", 1)
	};

	glm::vec3 Positions[]{
		glm::vec3(3.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 0.0f, 0.0f),
		glm::vec3(-2.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-3.0f, 0.0f, 0.0f)
	};
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	

	Shader shaderProgram("default.vert", "default.frag");
	//Store mesh data in vectors for the mesh
	
	/*std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	Mesh pyramid(verts, ind, tex);
	*/

	std::vector <Texture> hextex(hexgridtex, hexgridtex + sizeof(hexgridtex) / sizeof(Texture));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	std::vector<Vertex> verts;
	std::vector<GLuint> ind;
	generateIcosphere(verts, ind, 2);
	Mesh sphere(verts, ind, tex);

	std::vector<Vertex> cubverts;
	std::vector<GLuint> cubind;
	generateCube(cubverts, cubind);
	Mesh cube(cubverts, cubind, tex);


	std::vector <Vertex> faceverts(squareVerts, squareVerts + sizeof(squareVerts) / sizeof(Vertex));
	std::vector <GLuint> faceind(squareInts, squareInts + sizeof(squareInts) / sizeof(GLuint));


	Mesh square(faceverts, faceind, hextex);

	Shader lightShader("light.vert", "light.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	// Create light mesh
	Mesh light(lightVerts, lightInd, tex);


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(1.0f, 0.5f, 1.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	//get texture
	Model model("models/sword2/untitled.gltf");

	Mesh swordmesh = model.meshes[0];
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	float rotSpeed = 1.0f;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 10.0f));
	
	ComponentManager componentManager;

	float ballsize = 0.5f;
	int largestentityId = 0;
	#pragma region AddEntities
	// Create entities
	Entity entity1 = 1;
	Entity entity2 = 2;

	Entity left = 3;
	Entity right = 4;
	Entity down = 5;
	Entity top = 6;
	Entity back = 7;
	Entity front = 8;

	Entity entity9 = 9;

	Entity ball1 = 10;
	Entity ball2 = 11;
	Entity ball3 = 12;
	Entity ball4 = 13;
	Entity ball5 = 14;
	Entity ball6 = 15;
	// Add components
	//componentManager.AddComponent<TransformComponent>(entity1, glm::vec3(1.0f, 2.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(ballsize));
	//componentManager.AddComponent<TransformComponent>(ball1, glm::vec3(3.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(ballsize));
	//componentManager.AddComponent<TransformComponent>(ball2, glm::vec3(-3.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(ballsize));

	componentManager.AddComponent<TransformComponent>(entity2, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f));

	componentManager.AddComponent<TransformComponent>(left, glm::vec3(-0.5f, 0.0f, 0.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f), entity2);
	componentManager.AddComponent<TransformComponent>(right, glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(1.0f), entity2);
	componentManager.AddComponent<TransformComponent>(down, glm::vec3(0.0f, -0.5f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(1.0f), entity2);
	componentManager.AddComponent<TransformComponent>(top, glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(1.0f), entity2);
	componentManager.AddComponent<TransformComponent>(back, glm::vec3(0.0f, 0.0f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), entity2);
	componentManager.AddComponent<TransformComponent>(front, glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), entity2);


	componentManager.AddComponent<TransformComponent>(entity9, glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f));

	//componentManager.AddComponent<MeshComponent>(entity1, sphere);
	//componentManager.AddComponent<MeshComponent>(ball1, sphere);
	//componentManager.AddComponent<MeshComponent>(ball2, sphere);
	//componentManager.AddComponent<MeshComponent>(entity2, cube);

	componentManager.AddComponent<TransparentMeshComponent>(left, square);
	componentManager.AddComponent<TransparentMeshComponent>(right, square);
	componentManager.AddComponent<TransparentMeshComponent>(top, square);
	componentManager.AddComponent<TransparentMeshComponent>(down, square);
	componentManager.AddComponent<TransparentMeshComponent>(back, square);
	componentManager.AddComponent<TransparentMeshComponent>(front, square);

	componentManager.AddComponent<TransparentMeshComponent>(entity9, square);

	//componentManager.AddComponent<PhysicsComponent>(entity1, 1.0f, glm::vec3(5.0f, 0.0f, 3.0f), glm::vec3(0.0f, -9.81f, 0.0f), 0.95f, 0.10f);
	//componentManager.AddComponent<PhysicsComponent>(ball1, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -9.81f, 0.0f), 0.95f, 0.10f);
	//componentManager.AddComponent<PhysicsComponent>(ball2, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -9.81f, 0.0f), 0.95f, 0.10f);
	//componentManager.AddComponent<BallColliderComponent>(entity1, ballsize);
	//componentManager.AddComponent<BallColliderComponent>(ball1, ballsize);
	//componentManager.AddComponent<BallColliderComponent>(ball2, ballsize);
	// Create system
	RenderSystem RenderSystem(componentManager, shaderProgram, camera);
	//RenderSystem.AddEntity(entity1);
	//RenderSystem.AddEntity(ball1);
	//RenderSystem.AddEntity(ball2);

	RenderSystem.AddEntity(left);
	RenderSystem.AddEntity(right);
	RenderSystem.AddEntity(down);
	//RenderSystem.AddEntity(top);
	RenderSystem.AddEntity(back);
	RenderSystem.AddEntity(front);
	//RenderSystem.AddEntity(entity9);

	MovementSystem movementSystem(componentManager);
	movementSystem.AddEntity(entity1);
	movementSystem.AddEntity(entity2);

	PhysicsSystem physicsSystem(componentManager);
	//physicsSystem.AddEntity(entity1);
	//physicsSystem.AddEntity(ball1);
	//physicsSystem.AddEntity(ball2);
	BorderCollisionSystem collisionSystem(componentManager);
	//collisionSystem.AddEntity(entity1);
	//collisionSystem.AddEntity(ball1);
	//collisionSystem.AddEntity(ball2);
	PhysicsComponent* ball = componentManager.GetComponent<PhysicsComponent>(entity1);


	BallCollisionSystem ballCollisionSystem(componentManager);
	//ballCollisionSystem.AddEntity(entity1);
	//ballCollisionSystem.AddEntity(ball1);
	//ballCollisionSystem.AddEntity(ball2);

	#pragma endregion AddEntities

	bool isInteractingWithUI = false;
	bool interacting = false;
	bool isPaused = false;

	float updateRate = 0.016f;
	float simulationSpeed = 1.0f;
	largestentityId = 15;
	//Make window responsive
	while (!glfwWindowShouldClose(window)) {
		// Specify the color of the background
		
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		// Handles camera inputs
		if (!interacting && !isInteractingWithUI) {
			camera.Inputs(window);
		}
		
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		//std::cout << ball->velocity.y  << std::endl;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		RenderSystem.Update(updateRate);

		if (!isPaused) {
			collisionSystem.Update(updateRate * simulationSpeed);
			ballCollisionSystem.Update(updateRate * simulationSpeed);
			physicsSystem.Update(updateRate * simulationSpeed);
		}

		ImGui::Begin("Hello, world!");                // Create a window called "Hello, world!" and append into it.
		isInteractingWithUI = ImGui::IsAnyItemHovered() || ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
		if (ImGui::Button("Add Ball")) {
			largestentityId++;
			Entity newball = createBall(largestentityId, componentManager, sphere, ballsize);
			ballCollisionSystem.AddEntity(newball);
			RenderSystem.AddEntity(newball);
			collisionSystem.AddEntity(newball);
			physicsSystem.AddEntity(newball);
		}

		if (isInteractingWithUI)
		{
			interacting = true;
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			interacting = false;
		}
		ImGui::SliderFloat("Simulation Speed", &simulationSpeed, 0.0f, 5.0f);   // Edit simulation speed with slider

		ImGui::SliderFloat("ball size", &ballsize, 0.1f, 1.0f);
		if (ImGui::Button("||")) {
			isPaused = !isPaused;
		}
		ImGui::SameLine();

		if (ImGui::Button(">")) {
			isPaused = false;
			simulationSpeed = 1.0f;
		}
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		//model.Draw(shaderProgram, camera);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();

	}


	shaderProgram.Delete();
	lightShader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}