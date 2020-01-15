#pragma once

#include <Qtgui>

class RasterWindow : public QWindow
{
	Q_OBJECT

public:
	RasterWindow(QWindow *parent = Q_NULLPTR);

	virtual void render(QPainter *painter);

public slots:

	void renderLater();
	virtual void renderNow();

protected:
	bool event(QEvent *event) override;

	void resizeEvent(QResizeEvent *event) override;
	void exposeEvent(QExposeEvent *event) override;

public:
	QBackingStore *m_backingStore;
};
