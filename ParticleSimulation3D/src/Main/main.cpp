#include "sapch.h"
#include "Novaura/Core/Application.h"
#include "App/ParticleSimulationApp.h"

int main()
{
	Novaura::Application* app = new ParticleSimulation::ParticleSimulationApp("Space Adventures", 1280.0f, 720.0f);
	
	while (app->IsRunning())
	{
		app->Update();
	}
	delete app;
	return 0;
}