#pragma once

#include "rModule.hpp"

class BilkyModule : public rModule {
public:
	BilkyModule(rEngine* engine);

public:
	virtual void Init() override;

	virtual void LoadScene(const rString& sceneName) override;
	virtual void DeleteActor(rActor3* actor) override;

	virtual void AfterRenderScene(rViewInfo* viewInfo);

private:
	rEngine* m_engine;
	rTexture* texture;
};