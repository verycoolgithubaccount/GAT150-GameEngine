#include <box2d/box2d.h>
#include <memory>

class Physics
{
private:
	b2WorldId m_worldId;

public:
	Physics() = default;

	bool Initialize();
	void Shutdown();

	void Update(float dt);
};