#include<GL/glut.h>
#include<iostream>

using namespace std;

static float scalar = 1;
static float rot = 0;
static bool left_down = false;
static bool right_down = false;
static int times = 0;

static const float vertex_list[][3] =
{
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
};


static const GLint index_list[][2] =
{
    {0, 1},
    {2, 3},
    {4, 5},
    {6, 7},
    {0, 2},
    {1, 3},
    {4, 6},
    {5, 7},
    {0, 4},
    {1, 5},
    {7, 3},
    {2, 6}
};

void DrawCube(void)
{
  int i, j;

  glBegin(GL_LINES);
  for (i = 0; i < 12; ++i)

  {
    for (j = 0; j < 2; ++j)

    {
      glVertex3fv(vertex_list[index_list[i][j]]);
    }
  }
  glEnd();
}


void renderScene(void)
{
  times++;
  if (times % 10 == 0) {
    if (left_down) rot += 0.1f;
    if (right_down) rot -= 0.1f;
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glPushMatrix();
  glViewport(0, 0, 500, 500);
  glRotatef(10, 0, 1, 0);
  glRotatef(10, 1, 0, 0);
  glRotatef(rot, 0, 1, 0);
  glColor3f(0, 1, 0);
  glScalef(scalar, scalar, scalar);
  DrawCube();
  glPopMatrix();

  glPushMatrix();
  glViewport(500, 0, 500, 500);
  glColor3f(1, 0, 0);
  glScalef(scalar, scalar, scalar);
  glRotatef(rot, 0, 1, 0);
  glutWireTeapot(0.5);
  glPopMatrix();

  glPushMatrix();
  glViewport(1000, 0, 500, 500);
  glColor3f(0, 0, 1);
  glRotatef(10, 0, 1, 0);
  glRotatef(10, 1, 0, 0);
  glRotatef(rot, 0, 1, 0);
  glScalef(scalar, scalar, scalar);
  glutWireSphere(0.5, 50, 50);
  glPopMatrix();

  glutSwapBuffers();
}

float check_scalar(float s) {
  if (s <= 0) return 0.1;
  if (s > 1.5) return 1.5;
  return s;
}

void input(unsigned char key, int a, int b) {
  switch (key)
  {
  case 'w': {
    scalar += 0.1;
    cout << "input w" << endl;
    break;
  }
  case 's': {
    scalar -= 0.1;
    scalar = check_scalar(scalar);
    cout << "input s" << endl;
    break;
  }
  case 'r': {
    scalar = 0;
    rot = 0;
    cout << "input r" << endl;
    break;
  }
  }
}

void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      left_down = true;
    }
    else if (state == GLUT_UP) {
      left_down = false;
    }
  }
  else if (button == GLUT_RIGHT_BUTTON) {
    if (state == GLUT_DOWN) {
      right_down = true;
    }
    else if (state == GLUT_UP) {
      right_down = false;
    }
  }
}

void main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(1500, 500);
  glutCreateWindow("Project01");
  glutKeyboardFunc(input);
  glutMouseFunc(mouse);
  glutDisplayFunc(renderScene);
  glutIdleFunc(renderScene);
  glutMainLoop();
}