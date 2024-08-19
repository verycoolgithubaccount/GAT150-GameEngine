#include "Engine.h"
#include "Components/PlayerComponent.h"
#include <iostream>
#include <cassert>

void func1(int i) { std::cout << "func1: " << i << std::endl; }
void func2(int i) { std::cout << "func2: " << i << std::endl; }

int main(int argc, char* argv[])
{
	void(*fp)(int);

	fp = &func1;
	fp(5);
	fp = &func2;
	fp(8);

	std::unique_ptr<Engine> engine = std::make_unique<Engine>(); // unique ptr so it deletes when out of scope
	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::string buffer;
	File::ReadFile("Scenes/scene.json", buffer);
	std::cout << buffer << std::endl;

	rapidjson::Document document;
	Json::Load("Scenes/scene.json", document);

	std::unique_ptr<Scene> scene = std::make_unique<Scene>(engine.get());
	scene->Read(document);
	scene->Initialize();


	{
		while (!engine->GameQuit())
		{
			engine->Update();
			scene->Update(engine->GetTime().GetDeltaTime(), engine->GetRenderer(), engine->GetAudio());

			auto* actor = scene->GetActor<Actor>("text");
			if (actor)
			{
				actor->Rotate(90 * engine->GetTime().GetDeltaTime());
			}

			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			scene->Draw(engine->GetRenderer());

			engine->GetParticleSystem().Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}

	scene->RemoveAll();
	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}