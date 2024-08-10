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

	rapidjson::Document document;
	Json::Load("text.txt", document);

	std::string name;
	int age;
	float speed;
	bool isAwake;
	Vector2 position;
	Color color;

	READ_DATA(document, name);
	READ_DATA(document, age);
	READ_DATA(document, speed);
	READ_DATA(document, isAwake);
	READ_DATA(document, position);
	READ_DATA(document, color);
	std::cout << "Name: " << name << ", Age: " << age << ", Speed: " << speed << ", Awake: " << isAwake << ", Position: " << position << ", Color: " << color <<  std::endl;

	{
		// create texture, using shared_ptr so texture can be shared
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("Textures/yayitworks.png", engine->GetRenderer());
		res_t<Font> font = ResourceManager::Instance().Get<Font>("Fonts/Avignon.ttf", 12);
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), "yay it works", { 1, 1, 0 });

		auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
		actor->SetTransform(Transform({ 100, 100 }));

		auto textureComponent = Factory::Instance().Create<TextureComponent>(TextureComponent::GetTypeName());
		textureComponent->SetTexture(texture);
		actor->AddComponent(std::move(textureComponent));

		while (!engine->GameQuit())
		{
			engine->Update();

			actor->Update(engine->GetTime().GetDeltaTime());

			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			engine->GetParticleSystem().Draw(engine->GetRenderer());
			engine->GetRenderer().DrawTexture(texture.get(), 30, 30);
			actor->Draw(engine->GetRenderer());
			text->Draw(engine->GetRenderer(), 400, 400);

			engine->GetRenderer().EndFrame();
		}
	}

	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}