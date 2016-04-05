#include "BilkyModule.hpp"

BilkyModule::BilkyModule(rEngine* engine) 
	:rModule("Bilky")
{
	m_engine = engine;
}

void BilkyModule::LoadScene(const rString& sceneName) {

}

void BilkyModule::DeleteActor(rActor3* actor) {
	delete actor;
}

void BilkyModule::Init() {
	rViewport* viewport = m_engine->component->CreateViewport("default");
	viewport->SetViewportType(rViewportType::rVIEWPORT_2D);
	viewport->SetSize(1024, 768);

	texture = m_engine->content->Textures()->LoadFromPath("C:/Users/matthew/Downloads/Sea-Turtle-HD-Wallpaper.rtex", "turtle");

	if (texture) {
		rLog::Info("texture loaded");
	}
}

void BilkyModule::AfterRenderScene(rViewInfo* viewInfo) {
	m_engine->renderer->SpriteBatch()->RenderTexture(texture, rVector2(10, 10));
}