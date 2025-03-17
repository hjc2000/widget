#pragma once
#include <QtOpenGL/qopenglfunctions_1_0.h>
#include <QtOpenGLWidgets/QOpenGLWidget>

namespace widget
{
	class GLWidget :
		public QOpenGLWidget,
		protected QOpenGLFunctions_1_0
	{
	private:
		void drawCircle(float cx, float cy, float r, int num_segments)
		{
			glColor3f(1.0f, 1.0f, 1.0f); // 设置绘制颜色为白色

			glBegin(GL_TRIANGLE_FAN);
			glVertex2f(cx, cy); // 圆心坐标

			// 生成圆周上的点
			for (int i = 0; i <= num_segments; i++)
			{
				float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
				float x = r * cosf(theta);
				float y = r * sinf(theta);
				glVertex2f(x + cx, y + cy);
			}

			glEnd();
		}

	protected:
		void initializeGL() override
		{
			initializeOpenGLFunctions();
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 设置背景为黑色
		}

		void resizeGL(int w, int h) override
		{
			glViewport(0, 0, w, h);
		}

		void paintGL() override
		{
			glClear(GL_COLOR_BUFFER_BIT);

			// 设置正交投影
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // 标准化坐标系

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			// 绘制圆形
			drawCircle(0.0f, 0.0f, 0.5f, 100);
		}
	};

	int test_gl_widget(int argc, char *argv[]);
} // namespace widget
