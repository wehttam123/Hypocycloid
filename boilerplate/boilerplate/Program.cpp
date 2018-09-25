#define _USE_MATH_DEFINES
#include "Program.h"
#include <cmath>

Program::Program() {
	window = nullptr;
	renderEngine = nullptr;
}

// Error callback for glfw errors
void Program::error(int error, const char* description) {
	std::cerr << description << std::endl;
}

// Called to start the program
void Program::start() {
	setupWindow();
	GLenum err = glewInit();
	if (glewInit() != GLEW_OK) {
		std::cerr << glewGetErrorString(err) << std::endl;
	}

	renderEngine = new RenderEngine(window);
	InputHandler::setUp(renderEngine);
	mainLoop();
}

// Creates GLFW window for the program and sets callbacks for input
void Program::setupWindow() {
	glfwSetErrorCallback(Program::error);
	if (glfwInit() == 0) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_SAMPLES, 16);
	window = glfwCreateWindow(1280, 720, "CPSC 589 Assignment 1 Hypocycloid", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // V-sync on

	glfwSetKeyCallback(window, InputHandler::key);
	glfwSetMouseButtonCallback(window, InputHandler::mouse);
	glfwSetCursorPosCallback(window, InputHandler::motion);
	glfwSetScrollCallback(window, InputHandler::scroll);
	glfwSetWindowSizeCallback(window, InputHandler::reshape);
}

// Main loop
void Program::mainLoop() {

	float r = 11.0;      // Radius of small circle
	float R = 2.5;		// Radius of larger circle
	float n = 100.0;		// Number of cycles

	float angle = 0.0;	// Rotation Angle******
	float scale = 1.0;	// Scale of Hypocycloid
	double i = 0.0;		// Position along cycle
	double u = 0.0;		// Position along Hypocycloid

	float x;			// X position
	float y;			// Y position

						// Adjust scale
	r = r * scale;
	R = R * scale;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glLineWidth(3);

		// Animation Position
		if (i < n) {
			i += 0.1; // Animation speed
		}
		else {
			i = 0.0;
		}

		// Calculate Position
		u = 2.0 * M_PI * i;
		// Parametric Equations
		x = ((R - r) * cos(u)) + (r * cos(((R - r) / r) * u));
		y = ((R - r) * sin(u)) - (r * sin(((R - r) / r) * u));

		// Build Hypocycloid
		Hypocycloid = Geometry::makeHypocycloid(r, R, i);

		// Outer Circle
		OuterCircle = Geometry::makeCircle(R, 0.0, 0.0, 1.0, 0.5, 0.0, false);

		// Inner Circle
		InnerCircle = Geometry::makeCircle(r, (R - r)*cos(u), (R - r)*sin(u), 0.0, 0.0, 0.0, false);
		EdgeDot = Geometry::makeCircle(0.2, x, y, 1.0, 0.0, 0.0, true);
		MiddleDot = Geometry::makeCircle(0.2, (R - r)*cos(u), (R - r)*sin(u), 0.0, 0.0, 0.0, true);
		Radius = Geometry::makeLine(x, y, (R - r)*cos(u), (R - r)*sin(u));

		// Render Objects
		renderEngine->assignBuffers(OuterCircle);
		renderEngine->updateBuffers(OuterCircle);
		objects.push_back(&OuterCircle);
		renderEngine->assignBuffers(InnerCircle);
		renderEngine->updateBuffers(InnerCircle);
		objects.push_back(&InnerCircle);
		renderEngine->assignBuffers(Hypocycloid);
		renderEngine->updateBuffers(Hypocycloid);
		objects.push_back(&Hypocycloid);
		renderEngine->assignBuffers(EdgeDot);
		renderEngine->updateBuffers(EdgeDot);
		objects.push_back(&EdgeDot);
		renderEngine->assignBuffers(MiddleDot);
		renderEngine->updateBuffers(MiddleDot);
		objects.push_back(&MiddleDot);
		renderEngine->assignBuffers(Radius);
		renderEngine->updateBuffers(Radius);
		objects.push_back(&Radius);

		renderEngine->render(objects, glm::mat4(1.f));
		glfwSwapBuffers(window);
	}

	// Clean up, program needs to exit
	glfwDestroyWindow(window);
	delete renderEngine;
	glfwTerminate();
}
