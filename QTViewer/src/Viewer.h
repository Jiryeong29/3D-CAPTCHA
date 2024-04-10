#pragma once
#include "QGLViewer/manipulatedFrame.h"
#include "QGLViewer/qglviewerortho.h"
#include <qobjectdefs.h>
#include <qKeyEvent>
#include "DrawComponent.h"

class Viewer : public QGLViewerOrtho
{
	Q_OBJECT
public:
	Viewer(QWidget* parent);
	void initializeGL() override;
	void draw() override;
	void SetCamera(float ux, float uy, float uz, float dx, float dy, float dz);
	void SetCameraFront();
	void keyPressEvent(QKeyEvent* e) override;
	void mousePressEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* e) override;
	void mouseReleaseEvent(QMouseEvent*e) override;
	void animate() override;

	MN::DrawComponent dc3;


	int animateIdx = 0;
	int drawIdx = 0;

};
