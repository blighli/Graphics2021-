#include <GL\glut.h>
#include <iostream>
#include <vector>
int wHeihgt = 1080;
int wWidth = 1080;
float eye[] = { 0,0,8 };
float center[] = { 0,0,0 };
float move[] = { 0,0,0 };
float rotateV[] = { -90.,0.,0. };
float size = .1f;

void Draw_teapot() {
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidTeapot(4);
	glPopMatrix();
}
void updateViewMatrix(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//Reset projection mat

	float ratio = width * 1. / height;
	gluPerspective(60, ratio, .1f, 100.f);
	//glOrtho(-3, 3, -3, 3, -100, 100);
	glMatrixMode(GL_MODELVIEW);
}
void windowReshape(int width, int height) {
	height = (height == 0) ? 1 : height;
	wHeihgt = height;
	wWidth = width;
	updateViewMatrix(width, height);
}

void input(UCHAR key,int a,int b) {
	switch (key)
	{
		case 'a': {
			rotateV[2] += 1.f;
			break;
		}
		case 'd': {
			rotateV[2] -= 1.f;
			break;
		}
		case 'w': {
			rotateV[0] += 1.f;
			break;
		}
		case 's': {
			rotateV[0] -= 1.f;
			break;
		}
	}
}
void mouseinput(int button, int state, int x, int y) {
	if (state == GLUT_UP && button == GLUT_LEFT_BUTTON) {
		size += 0.001;
		size = std::min((double)size, 1.5);
		glutPostRedisplay();
	}
	else if (state == GLUT_UP && button == GLUT_RIGHT_BUTTON) {
		size -= 0.001;
		size = std::max((double)size, 0.1);
		glutPostRedisplay();
	}
}
void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0, 1, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat light0colora[] = { .4,.24,0.,1. };
	GLfloat light0colord[] = { .8,.48,.0,1. };
	GLfloat light0colors[] = { 1,.6,.0,1. };
	GLfloat light0pos[] = { 7.,7.,7.,1. };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0colora);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0colord);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0colors);
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	glEnable(GL_LIGHT0);

	glRotatef(rotateV[0], 1., 0., 0.);
	glRotatef(rotateV[1], 0., 1., 0.);
	glRotatef(rotateV[2], 0., 0., 1.);

	glScalef(size, size, size);
	Draw_teapot();

	glutSwapBuffers();//flush
}
void idle() {
	glutPostRedisplay();
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(wWidth, wHeihgt);
	int windowHandle = glutCreateWindow("homework1");
	glutDisplayFunc(draw);
	glutReshapeFunc(windowReshape);
	glutKeyboardFunc(input);
	glutMouseFunc(mouseinput);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}