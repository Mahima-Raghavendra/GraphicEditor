#include<GL/glut.h>
#include<stdlib.h>
#include<cmath>

int screenWidth = 1000;
int screenHeight = 600;
const int MAX_ITEMS = 1000;
GLint brushsize = 10;
int tempx, tempy, flag = 0, secondx, secondy;
GLint x, y;
int count = 0;
int press, btn_state;
bool isSecond = false;

/*struct ItemData {
    double x1, y1;
    double x2, y2;
};

ItemData items[MAX_ITEMS];
int itemCt = 0;*/

void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
}

void draw_pixel(int x, int y)
{
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawLine(int x1, int y1, int x2, int y2)
{
    int dx, dy, i, e;
    int incx, incy, inc1, inc2;
    int x, y;
    dx = x2 - x1;
    dy = y2 - y1;
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    incx = 1;
    if (x2 < x1)
        incx = -1;
    incy = 1;
    if (y2 < y1) incy = -1;
    x = x1; y = y1;
    if (dx > dy) {
        draw_pixel(x, y);
        e = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        for (i = 0; i < dx; i++) {
            if (e >= 0) {
                y += incy;
                e += inc1;
            }
            else
                e += inc2;
            x += incx;
            draw_pixel(x, y);
        }
    }
    else {
        draw_pixel(x, y);
        e = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (i = 0; i < dy; i++) {
            if (e >= 0) {
                x += incx;
                e += inc1;
            }
            else
                e += inc2;
            y += incy;
            draw_pixel(x, y);
        }
    }
    glFlush();
}

void drawRectangle(int x1, int y1, int x2, int y2)
{
    drawLine(x1, y1, x2, y1);
    drawLine(x2, y1, x2, y2);
    drawLine(x2, y2, x1, y2);
    drawLine(x1, y2, x1, y1);
    glFlush();
}

void drawCircle(int x1, int y1, int x2, int y2)
{
    int r = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    double d;
    int x, y;

    x = 0;
    y = r;
    d = 1.25 - r;

    while (x <= y)
    {
        draw_pixel(x1 + x, y1 + y);
        draw_pixel(x1 - x, y1 + y);
        draw_pixel(x1 + x, y1 - y);
        draw_pixel(x1 - x, y1 - y);
        draw_pixel(x1 + y, y1 + x);
        draw_pixel(x1 - y, y1 + x);
        draw_pixel(x1 + y, y1 - x);
        draw_pixel(x1 - y, y1 - x);
        x++;
        if (d < 0)
        {
            d += 2 * x + 3;
        }
        else
        {
            y--;
            d += 2 * (x - y) + 5;
        }
    }
    glFlush();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //glFlush();
    /*if (flag == 1) {
        for (size_t i = 0;i <= itemCt;++i) {
            drawLine(items[i].x1, items[i].y1, items[i].x2, items[i].y2);
        }
    }
    if (flag == 2) {
        for (size_t i = 0;i <= itemCt;++i) {
            //glBegin(GL_LINE_LOOP);
            //glVertex2i(items[i].x1, items[i].y1);
            //glVertex2i(items[i].x1, items[i].y2);
            //glVertex2i(items[i].x2, items[i].y2);
            //glVertex2i(items[i].x2, items[i].y1);
            //glEnd();
            drawRectangle(items[i].x1, items[i].y1, items[i].x2, items[i].y2);
        }
        glFlush();
    }*/
}

void myMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!isSecond) {
            tempx = x;
            tempy = screenHeight - y;
            isSecond = true;
        }
        else {
            if (flag == 1) {
                drawLine(tempx, tempy, x, (screenHeight - y));
            }
            else if (flag == 2) {
                drawRectangle(tempx, tempy, x, (screenHeight - y));
            }
            else if (flag == 3) {
                drawCircle(tempx, tempy, x, (screenHeight - y));
            }
            isSecond = false;
        }
    }
    /*if (button == GLUT_LEFT_BUTTON) {
        if(state == GLUT_DOWN && button!=GLUT_RIGHT_BUTTON && itemCt<MAX_ITEMS-1){
            items[itemCt].x1 = x;
            items[itemCt].y1 = screenHeight - y;
            items[itemCt].x2 = x;
            items[itemCt].y2 = screenHeight - y;
            glutPostRedisplay();
        }
        else if (state == GLUT_UP && button != GLUT_RIGHT_BUTTON) {
            items[itemCt].x2 = x;
            items[itemCt].y2 = screenHeight - y;
            itemCt++;
            glutPostRedisplay();
        }
    }*/
    if (button == GLUT_RIGHT_BUTTON)
        glClear(GL_COLOR_BUFFER_BIT);
}

void myMovedMouse(int mouseX, int mouseY)
{
    x = mouseX;
    y = screenHeight - mouseY;

    if(flag==0)
        glRecti(x, y, x + brushsize, y + brushsize);
    /*if (flag == 1) {
        items[itemCt].x2 = x;
        items[itemCt].y2 = y;
        glutPostRedisplay();
    }*/
    /*if (flag == 1) {
        drawLine(tempx, tempy, x, y);
    }
    if (flag == 2) {
        drawRectangle(tempx, tempy, x, y);
        //items[itemCt].x2 = x;
        //items[itemCt].y2 = y;
        //glutPostRedisplay();
    }*/
    glFlush();
    glEnd();
}

void reshape(int width, int height) {
    screenWidth = width;
    screenHeight = height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, width, height);
}

void mymenu(int value)
{
    isSecond = false;
    switch (value)
    {
    case 1:
        brushsize = 4;
        break;
    case 2:
        brushsize = 8;
        break;
    case 3:
        brushsize = 12;
        break;
    case 4:
        brushsize = 16;
        break;
    case 5:
        brushsize = 20;
        break;
    case 6:
        flag = 1;
        glutSetCursor(GLUT_CURSOR_CROSSHAIR);
        break;
    case 7:
        flag = 2;
        glutSetCursor(GLUT_CURSOR_CROSSHAIR);
        break;
    case 8:
        flag = 3;
        glutSetCursor(GLUT_CURSOR_CROSSHAIR);
        break;
    case 9:
        flag = 0;
        glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 1.0, 1.0);
        break;
    case 10:
        flag = 0;
        glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
        glColor3f(1.0, 1.0, 1.0);
        break;
    case 11:
        flag = 0;
        glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
        glColor3f(1.0, 0.0, 0.0);
        break;
    case 12:
        flag = 0;
        glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
        glColor3f(0.0, 0.0, 0.0);
        break;
    case 13:
        flag = 0;
        glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
        glColor3f(0.0, 1.0, 0.0);
        break;
    case 14:
        flag = 0;
        glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
        glColor3f(0.0, 0.0, 1.0);
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Graphic Editor");
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(reshape);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMovedMouse);
    int sub1 = glutCreateMenu(mymenu);
    glutAddMenuEntry("1.0", 1);
    glutAddMenuEntry("2.0", 2);
    glutAddMenuEntry("3.0", 3);
    glutAddMenuEntry("4.0", 4);
    glutAddMenuEntry("5.0", 5);
    glutCreateMenu(mymenu);
    glutAddSubMenu("Brush or eraser size", sub1);
    glutAddMenuEntry("Line", 6);
    glutAddMenuEntry("Rectangle", 7);
    glutAddMenuEntry("Circle", 8);
    glutAddMenuEntry("Clear Screen", 9);
    glutAddMenuEntry("Erase", 10);
    glutAddMenuEntry("Red Pen", 11);
    glutAddMenuEntry("Black Pen", 12);
    glutAddMenuEntry("Green Pen", 13);
    glutAddMenuEntry("Blue Pen", 14);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    myInit();
    glutMainLoop();
}