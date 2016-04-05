#include "sdl/rSDLApplication.hpp"
#include "BilkyModule.hpp"

class BilkyApplication : public rApplication {
public:
	rModule* CreateModule(rEngine* engine);
};

rModule* BilkyApplication::CreateModule(rEngine* engine) {
	return new BilkyModule(engine);
}

IMPLEMENT_MAIN(BilkyApplication)