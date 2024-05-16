#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h> 

// Globals.
static int light0On = 1; // White light on?
static int light1On = 1; // Green light on?
static float d = 1.0; // Diffuse and specular white light intensity.
static float m = 0.2; // Global ambient white light intensity.
static int localViewer = 1; // Local viewpoint?
static float p = 1.0; // Positional light?
static float t = 0.0; // Quadratic attenuation factor.
static float zMove = 0.0; // z-direction component.
static float xAngle = 0.0, yAngle = 0.0; // Rotation angles of white light.
static void* font = GLUT_BITMAP_8_BY_13; // Font selection.
static char theStringBuffer[10]; // String buffer.

// Routine to draw a bitmap character string.
void writeBitmapString(void *font, const char *string)
{
    const char *c;
    for (c = string; *c != '\0'; c++) 
        glutBitmapCharacter(font, *c);
}

// Routine to convert floating point to char string.
void floatToString(char *destStr, int precision, float val)
{
    sprintf(destStr, "%.*f", precision, val);
}

// Write data.
void writeData(void)
{
    glDisable(GL_LIGHTING); // Disable lighting.
    glColor3f(1.0, 1.0, 1.0);

    floatToString(theStringBuffer, 4, d);
    glRasterPos3f(-1.0, 1.05, -2.0);
    writeBitmapString(font, "Diffuse and specular white light intensity: ");
    writeBitmapString(font, theStringBuffer);

    floatToString(theStringBuffer, 4, m);
    glRasterPos3f(-1.0, 1.0, -2.0);
    writeBitmapString(font, "Global ambient white light intensity: ");
    writeBitmapString(font, theStringBuffer);

    floatToString(theStringBuffer, 4, t);
    glRasterPos3f(-1.0, 0.95, -2.0);
    writeBitmapString(font, "Quadratic attenuation: ");
    writeBitmapString(font, theStringBuffer);

    glRasterPos3f(-1.0, 0.9, -2.0);
    if (localViewer)
        writeBitmapString(font, "Local viewpoint.");
    else
        writeBitmapString(font, "Infinite viewpoint.");

    glEnable(GL_LIGHTING); // Re-enable lighting.
}

// Initialization routine.
void setup(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST); // Enable depth testing.

    // Turn on OpenGL lighting.
    glEnable(GL_LIGHTING);

    // Material property vectors.
    float matAmbAndDif[] = { 0.0, 0.0, 1.0, 1.0 };
    float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
    float matShine[] = { 50.0 };

    // Material properties of ball.
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

    // Cull back faces.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

// Drawing routine.
void drawScene()
{
    // Light property vectors.
    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpec0[] = { d, d, d, 1.0 };
    float lightPos0[] = { 0.0, 0.0, 3.0, p }; // Last value p defines whether it is directional or positional.
    float lightDifAndSpec1[] = { 0.0, 1.0, 0.0, 1.0 };
    float lightPos1[] = { 1.0, 2.0, 0.0, 1.0 };
    float globAmb[] = { m, m, m, 1.0 };

    // Light0 properties.
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);

    // Light1 properties.
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec1);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, localViewer); // Enable local viewpoint.

    // Turn lights off/on.
    if (light0On) glEnable(GL_LIGHT0); else glDisable(GL_LIGHT0);
    if (light1On) glEnable(GL_LIGHT1); else glDisable(GL_LIGHT1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // Light quadratic attenuation factor.
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, t);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, t);

    writeData();

    gluLookAt(0.0, 3.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Draw light source spheres (or arrow) after disabling lighting.
    glDisable(GL_LIGHTING);

    // Light0 positioned and sphere positioned in case of positional light.
    // Arrow in case of directional light.
    glPushMatrix();
    glRotatef(xAngle, 1.0, 0.0, 0.0); // Rotation about x-axis.
    glRotatef(yAngle, 0.0, 1.0, 0.0); // Rotation about y-axis.
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glTranslatef(lightPos0[0], lightPos0[1], lightPos0[2]);
    glColor3f(d, d, d);
    if (light0On)
    {
        if (p)
            glutWireSphere(0.05, 8, 8); // Sphere at positional light source.
        else // Arrow pointing along incoming directional light.
        {
            glLineWidth(3.0);
            glBegin(GL_LINES);
            glVertex3f(0.0, 0.0, 0.25);
            glVertex3f(0.0, 0.0, -0.25);
            glVertex3f(0.0, 0.0, -0.25);
            glVertex3f(0.05, 0.0, -0.2);
            glVertex3f(0.0, 0.0, -0.25);
            glVertex3f(-0.05, 0.0, -0.2);
            glEnd();
            glLineWidth(1.0);
        }
    }
    glPopMatrix();

    // Light1 and its sphere positioned.
    glPushMatrix();
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glTranslatef(lightPos1[0], lightPos1[1], lightPos1[2]);
    glColor3f(0.0, 1.0, 0.0);
    if (light1On)
        glutWireSphere(0.05, 8, 8);
    glPopMatrix();

    glEnable(GL_LIGHTING);

    // Ball.
    glTranslatef(0.0, 0.0, zMove); // Move the ball.
    glutSolidSphere(1.5, 200, 200);

    glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / (float)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'w':
        light0On = !light0On;
        glutPostRedisplay();
        break;
    case 'g':
        light1On = !light1On;
        glutPostRedisplay();
        break;
    case 'l':
    case 'L':
        localViewer = !localViewer;
        glutPostRedisplay();
        break;
    case 'p':
    case 'P':
        p = p ? 0.0 : 1.0;
        glutPostRedisplay();
        break;
    case 'd':
        if (d > 0.0) d -= 0.05;
        glutPostRedisplay();
        break;
    case 'D':
        if (d < 1.0) d += 0.05;
        glutPostRedisplay();
        break;
    case 'm':
        if (m > 0.0) m -= 0.05;
        glutPostRedisplay();
        break;
    case 'M':
        if (m < 1.0) m += 0.05;
        glutPostRedisplay();
        break;
    case 't':
        if (t > 0.0) t -= 0.01;
        glutPostRedisplay();
        break;
    case 'T':
        t += 0.01;
        glutPostRedisplay();
        break;
    case 'r':
        zMove = 0.0; xAngle = 0.0; yAngle = 0.0;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
    if (key == GLUT_KEY_DOWN)
    {
        xAngle++;
        if (xAngle > 360.0) xAngle -= 360.0;
    }
    if (key == GLUT_KEY_UP)
    {
        xAngle--;
        if (xAngle < 0.0) xAngle += 360.0;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        yAngle++;
        if (yAngle > 360.0) yAngle -= 360.0;
    }
    if (key == GLUT_KEY_LEFT)
    {
        yAngle--;
        if (yAngle < 0.0) yAngle += 360.0;
    }
    if (key == GLUT_KEY_PAGE_UP) zMove -= 0.1;
    if (key == GLUT_KEY_PAGE_DOWN) if (zMove < 3.0) zMove += 0.1;
    glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    std::cout << "Interaction:" << std::endl;
    std::cout << "Press 'w' to toggle the white light off/on." << std::endl
              << "Press 'g' to toggle the green light off/on." << std::endl
              << "Press 'd/D' to decrease/increase the white light's diffuse and specular intensity." << std::endl
              << "Press 'm/M' to decrease/increase global ambient white light intensity." << std::endl
              << "Press 't/T' to decrease/increase the quadratic attenuation parameter." << std::endl
              << "Press 'l' to toggle between infinite and local viewpoint." << std::endl
              << "Press 'p' to toggle between positional and directional white light." << std::endl
              << "Press the page up/down keys to move the ball." << std::endl
              << "Press arrow keys to rotate the white light about the original position of the ball." << std::endl
              << "Press 'r' to reset the ball and white light to their original positions." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
    printInteraction();
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("lightAndMaterial2.cpp");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}
