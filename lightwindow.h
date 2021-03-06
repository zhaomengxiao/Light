#pragma once

#include <QtGui>
#include "rasterWindow\rasterwindow.h"
#include "Scene.h"

//typedef struct { float sd, emissive; } Result;
//Result unionOp(Result a, Result b);
//Result scene(float x, float y);
//float circleSDF(float x, float y, float cx, float cy, float r);

class LightWindow : public RasterWindow
{
	Q_OBJECT

public:
	void render(QPainter *painter) override;
	void renderNow() override;

	void buildScene();
private:
	Scene my_scene;
};
