#include "lightwindow.h"
//#include <dlib/matrix.h>
#include "macrodef.h"
#include "Scene.h"
#include "SDF.h"

void LightWindow::render(QPainter * painter)
{
	painter->drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, QStringLiteral("QlightRender"));
}

//Result unionOp(Result a, Result b) {
//	return a.sd < b.sd ? a : b;
//}




//Result scene(float x, float y)
//{
//	Result r1 = { circleSDF(x, y, 0.3f, 0.3f, 0.10f), 2.0f };
//	Result r2 = { circleSDF(x, y, 0.3f, 0.7f, 0.05f), 0.8f };
//	Result r3 = { circleSDF(x, y, 0.7f, 0.5f, 0.10f), 0.0f };
//	Result r4 = { circleSDF(x, y, 0.4f, 0.4f, 0.10f), 4.0f };
//	return unionOp(unionOp(unionOp(r1, r2), r3),r4);
//}

float LightWindow::trace(float ox, float oy, float dx, float dy) {
	float t = 0.0f;
	for (int i = 0; i < MAX_STEP && t < MAX_DISTANCE; i++) {
		/*Scene my_scene;
		my_scene.addSDF(circle_2, BoolOp::UNION_OP).addSDF(circle_3, BoolOp::UNION_OP);*/

		const auto r = my_scene.process(ox + dx * t, oy + dy * t);
		if (r.sd < EPSILON)
			return r.emissive;
		t += r.sd;
	}
	return 0.0f;
}

float LightWindow::sample(float x, float y)
{
	float sum = 0.0f;
	for (int i = 0; i < SAMPLE_N; i++) {
		 //float a = TWO_PI * rand() / RAND_MAX;
		 //float a = TWO_PI * i / 64;
		float a = TWO_PI * (i + (float)rand() / RAND_MAX) / SAMPLE_N;
		sum += trace(x, y, cosf(a), sinf(a));
	}
	return sum / SAMPLE_N;
}

void LightWindow::buildScene()
{
	CircleSDF* circle_1 = new CircleSDF(2.0f, 0.3f, 0.3f, 0.10f);
	CircleSDF* circle_2 = new CircleSDF(0.8f, 0.3f, 0.7f, 0.05f);
	CircleSDF* circle_3 = new CircleSDF(0.0f, 0.7f, 0.5f, 0.10f);
	PlaneSDF* plane_1 = new PlaneSDF(0.8, 0.0, 0.5, 0.0, 1.0);
	//CircleSDF* circle_4 = new CircleSDF(0.9f, 0.7f, 0.7f, 0.16f);
	my_scene.addSDF(circle_1, BoolOp::UNION_OP).addSDF(circle_2, BoolOp::UNION_OP).addSDF(circle_3, BoolOp::UNION_OP).addSDF(plane_1, BoolOp::UNION_OP);
}

void LightWindow::renderNow()
{
	buildScene();
	if (!isExposed())
		return;

	QRect rect(0, 0, width(), height());
	m_backingStore->beginPaint(rect);

	QPaintDevice *device = m_backingStore->paintDevice();
	QPainter painter(device);
	QPen whitepen;
	//painter.fillRect(0, 0, width(), height(), QGradient::NightFade);	
	//dlib::matrix<float> colormap;
	//colormap.set_size(width(), height());
	//dlib::parallel_for(0, height(), [&](int y) {
	//	dlib::parallel_for(0, width(), [&](int x) {
	//		int color = (int)(fminf(sample((float)x / width(), (float)y / height()) * 255.0f, 255.0f));
	//		//¥Ê»Îmat
	//		colormap(x, y) = color;
	//	});
	//});

	for (int y = 0; y < height(); y++) {
		for (int x = 0; x < width(); x++) {
			
			/*float color = colormap(x, y);*/
			float color = (int)(fminf(sample((float)x / width(), (float)y / height()) * 255.0f, 255.0f));
			whitepen.setColor(QColor(color, color, color));
			painter.setPen(whitepen);
			painter.drawPoint(x, y);
		}
	}
	render(&painter);
	painter.end();

	m_backingStore->endPaint();
	m_backingStore->flush(rect);
}
