#include "rasterWindow\rasterwindow.h"
//#include "lightwindow.h"
#include <QtWidgets/QApplication>
//#include "macrodef.h"
#include "svpng.inc"
#include "SDF.h"
#include "Scene.h"


int main(int argc, char *argv)
{
	//QApplication a(argc, argv);
	//LightWindow w;
	//w.show();
	//return a.exec();

	CircleSDF circle_1 = CircleSDF(2.0f, 0.3f, 0.3f, 0.10f);
	CircleSDF circle_2 = CircleSDF(0.8f, 0.7f, 0.7f, 0.05f);
	CircleSDF circle_3 = CircleSDF(0.0f, 0.7f, 0.65f, 0.05f);
	CircleSDF circle_4 = CircleSDF(0.0f, 0.35f, 0.3f, 0.10f);
	PlaneSDF plane_1 = PlaneSDF(0.5, 0.0, 0.7, 0.0, -1.0);
	Scene my_scene{ WIDTH,HEIGHT,SAMPLE_N};
	
	my_scene.addSDF(circle_1, BoolOp::UNION_OP)
		.addSDF(circle_4, BoolOp::UNION_OP)
		.addSDF(circle_2, BoolOp::UNION_OP)
		.addSDF(circle_3, BoolOp::UNION_OP)	
		.addSDF(plane_1, BoolOp::SUBTRACT_OP)
	;
	
	unsigned char rgb[WIDTH * HEIGHT * 3], *p = rgb;
	//unsigned x, y;
	FILE *fp;
	fopen_s(&fp,"rgb.png", "wb");

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x <WIDTH; x++ , p+=3) {
			p[0] = p[1] = p[2] = int(fminf(
				my_scene.sample(float(x) / WIDTH, float(y) / HEIGHT) * 255.0f, 255.0f));
			//p[0] = color;    /* R */
			//p[1] = color;    /* G */
			//p[2] = color;    /* B */
		}
	}
	svpng(fp, WIDTH, HEIGHT, rgb, 0);
	fclose(fp);
	return 0;
}
