#include "GLWidget.h"

int widget::test_gl_widget(int argc, char *argv[])
{
	QApplication a(argc, argv);

	GLWidget w;
	w.resize(400, 400);
	w.setWindowTitle("Qt OpenGL Circle");
	w.show();

	return a.exec();
}
