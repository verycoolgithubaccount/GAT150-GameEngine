#include "Engine.h"

int main(int argc, char* argv[])
{
	g_engine.Initialize();

	while (!g_engine.GameQuit())
	{
		g_engine.Update();

		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		g_engine.GetParticleSystem().Draw(g_engine.GetRenderer());

		g_engine.GetRenderer().EndFrame();
	}

	g_engine.Shutdown();

	return 0;
}