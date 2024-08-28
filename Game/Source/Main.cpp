#include "Engine.h"
#include "SpaceGame.h"
#include <iostream>
#include <cassert>

int main(int argc, char* argv[])
{
	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::unique_ptr<Engine> engine = std::make_unique<Engine>(); // unique ptr so it deletes when out of scope
	engine->Initialize();

	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>(engine.get());
	game->Initialize();

	{
		while (!engine->GameQuit())
		{
			engine->Update();
			game->Update(engine->GetTime().GetDeltaTime());
			
			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			engine->GetParticleSystem().Draw(engine->GetRenderer());
			game->Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}

	game->Shutdown();
	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}