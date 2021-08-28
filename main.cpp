#include <iostream>
#include <concepts>
#include <thread>
#include <syncstream>
#include <GL/freeglut.h>
#include <cmath>
consteval int test(int value)
{
    return value;
}

template <typename T>
requires std::is_trivial_v<T>
void fun(T v)
{
    std::cout << v << std::endl;
}




void drawPlane(){
    int num_segments = 20;
    float dx = 2.0f/num_segments;
    float dy = 2.0f/num_segments;
    glBegin(GL_QUADS);
    for(int i=0; i<num_segments;++i){
        for(int j=0; j<num_segments;++j){
            if((i+j)%2 ==0){
                glColor3f(1.0f, 0.0f, 0.0f);
            }
            else{
                glColor3f(0.0f, 1.0f, 0.0f);
            }
            glVertex2f(-1 + i * dx, -1 + j * dy);
            glVertex2f(-1 + (i + 1) * dx, -1 + j * dy);
            glVertex2f(-1 + (i + 1) * dx, -1 + (j + 1) * dy);
            glVertex2f(-1 + i * dx, -1 + (j + 1) * dy);
        }
    }
    glEnd();
}


void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int triangleAmount = 100; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * M_PI;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT); //очищаем буфер
    GLfloat alpha = 2;
    // glRotatef(alpha, 0, 0, 1);
    // glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    // drawFilledCircle(0,0,1);
    drawPlane();
    // glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void idle(void)
{
    glutPostRedisplay();
}

void visible(int vis)
{
    if (vis == GLUT_VISIBLE)
        glutIdleFunc(idle);
    else
        glutIdleFunc(NULL);
}

void onReshape(int windowWidth, int windowHeight)
{
    const float aspectRatio = ((float)windowWidth) / windowHeight;
    float xSpan = 2; // Feel free to change this to any xSpan you need.
    float ySpan = 2; // Feel free to change this to any ySpan you need.

    if (aspectRatio > 1){
        // Width > Height, so scale xSpan accordinly.
        xSpan *= aspectRatio;
    }
    else{
        // Height >= Width, so scale ySpan accordingly.
        ySpan = xSpan / aspectRatio;
    }
    glViewport(0, 0, windowWidth, windowHeight);
    //Without it not working!!!
    glLoadIdentity();
    glOrtho(-1*xSpan, xSpan, -1*ySpan, ySpan, -100, 100);


}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);            //начальная инициализация окна
    glutInitDisplayMode(GLUT_DOUBLE); //установка режима отображения
    glutInitWindowSize(800, 600);     //размер окна
    glutInitWindowPosition(200, 200); //начальная позиция на экране
    glutCreateWindow("Window"); //заголовок окна
    glClearColor(1, 1, 1, 0);   //цвет фона

    // настройка проекции, с этими двумя ф-ми познакомимся поближе чуть позже.
    glMatrixMode(GL_PROJECTION); //режим матрицы
    glLoadIdentity();           //отчищает матрицу

    glOrtho(-2, 2, -2, 2, -100, 100); //cоздаем пространство нашей сцены, в данном случае 3D пространство с высотой, шириной и глубиной в 200 едениц.
    glutDisplayFunc(display);
    glutVisibilityFunc(visible); //функция которой мы передаем имя функции для отрисовки окна.
    glutReshapeFunc(onReshape);
    glutMainLoop();              //запускаем всё проинициализированное, проще говоря та же ф-я main, только в данном случае glut'овская ф-я main.
    return 0;
}