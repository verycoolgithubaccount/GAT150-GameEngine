#include "Engine.h"
#include <iostream>
#include <cassert>

int main(int argc, char* argv[])
{
	Factory::Instance().Register<Actor>(Actor::GetTypeName());
	Factory::Instance().Register<TextureComponent>(TextureComponent::GetTypeName());
	//auto a = Factory::Instance().Create<Actor>("Actor");

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
		//// create texture, using shared_ptr so texture can be shared
		//res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("Textures/yayitworks.png", engine->GetRenderer());
		//res_t<Font> font = ResourceManager::Instance().Get<Font>("Fonts/Avignon.ttf", 12);
		//std::unique_ptr<Text> text = std::make_unique<Text>(font);
		//text->Create(engine->GetRenderer(), "yay it works", { 1, 1, 0 });

		//auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
		//actor->SetTransform(Transform({ 100, 100 }));

		//auto textureComponent = Factory::Instance().Create<TextureComponent>(TextureComponent::GetTypeName());
		//textureComponent->SetTexture(texture);
		//actor->AddComponent(std::move(textureComponent));

		while (!engine->GameQuit())
		{
			engine->Update();
			scene->Update(engine->GetTime().GetDeltaTime(), engine->GetRenderer(), engine->GetAudio());

			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			scene->Draw(engine->GetRenderer());

			engine->GetParticleSystem().Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}

	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}