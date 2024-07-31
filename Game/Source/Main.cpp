#include "Engine.h"

#include <iostream>
#include <cassert>

int main(int argc, char* argv[])
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>(); // unique ptr so it deletes when out of scope
	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	while (!engine->GameQuit())
	{
		engine->Update();

		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();

		engine->GetParticleSystem().Draw(engine->GetRenderer());

		engine->GetRenderer().EndFrame();
	}

	engine->Shutdown();

	return 0;
}