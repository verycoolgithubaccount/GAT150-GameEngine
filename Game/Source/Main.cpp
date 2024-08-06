#include "Engine.h"
#include <iostream>
#include <cassert>

int main(int argc, char* argv[])
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>(); // unique ptr so it deletes when out of scope
	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	{
		// create texture, using shared_ptr so texture can be shared
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("Textures/yayitworks.png", engine->GetRenderer());

		Transform transform{ { 100, 100 } };
		std::unique_ptr<Actor> actor = std::make_unique<Actor>(transform);
		std::unique_ptr<TextureComponent> textureComponent = std::make_unique<TextureComponent>();
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

			engine->GetRenderer().EndFrame();
		}
	}

	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}