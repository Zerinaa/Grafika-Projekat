#include <GL/glut.h>
#include "flower.c"

#define TRUE 1
#define FALSE 0

short int Light_1 = TRUE;
short int Light_0 = FALSE;
short int Material_1 = TRUE;
short int Material_2 = FALSE;
short int CubeRotation = FALSE;
short int CubeScaling = FALSE;
short int CubeTranslating = FALSE;
short int ClockwiseDirection = TRUE;

GLfloat ScaleFactor = 1.0;
GLfloat translateX = 1.5;
GLfloat translateY = 0;
GLfloat translateZ = -6;
GLfloat Xposition = -1.0;
GLfloat Yposition = 2.0;

float angle = 0;
float speed = 20;
float ar = 640/500;

// Callback funkcija za preoblikovanje prozora
static void resize(int width, int height)
{
    ar = (float) width / (float) height;
    glViewport(0, 0, width, height);

}

static void display(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    gluLookAt(Xposition,Yposition,0,0,-1,-12,0,1,0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    static int texture = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0,0.25,0.0);

    const GLfloat mat_ambient[] = {1.5, 1.5, 1.5, 1.0};
    const GLfloat mat_diffuse[] = {0.8, 0.8, 0.8, 1.0};
    const GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    const GLfloat high_shininess[] = {9.0};

    const GLfloat mat_ambient2[] = {5, 5, 5, 1.0};
    const GLfloat mat_diffuse2[] = {-3.8, -0.8, 0.8, 1.0};
    const GLfloat mat_specular2[] = {4.0, 4.0, 4.0, 1.0};
    const GLfloat high_shininess2[] = {30.0};

    const GLfloat mat_ambient1[] = {0.0, 0.0, 0.0, 1.0};
    const GLfloat mat_diffuse1[] = {0.0, 0.0, 0.0, 1.0};
    const GLfloat mat_specular1[] = {0.0, 0.0, 0.0, 0.0};
    const GLfloat high_shininess1[] = {0.0};


    if(Material_1 == TRUE) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
    }

    else {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess1);

    }

    if(Material_2 == TRUE) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient2);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse2);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular2);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess2);
    }

    glPushMatrix();
    glTranslatef(1.5,1.5,-6);
    glRotatef(65, -1.0, 0.0, 0.0);
    glutSolidCone(0.5, 1, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-1.5,2.0,-7);
    //glRotatef(30,0,1,1);
    glEnable(GL_TEXTURE_2D);


    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gimp_image.width, gimp_image.height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, gimp_image.pixel_data);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glutSolidTeapot(0.8);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glColor3f(0.8,0.7,0.0);
    glTranslatef(translateX, translateY, translateZ);
    glScalef(ScaleFactor, ScaleFactor, ScaleFactor);
    glRotatef(angle,0,1,1);
    glutSolidCube(0.8);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.43,0.85,0.85);
    glTranslatef(-2.5,-1,-6);
    glRotatef(130,1,1,1);
    glutSolidTetrahedron();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.13,0.65,0.13);
    glTranslatef(0,-3,-13);
    glRotatef(-60,1,0,1);
    glutSolidDodecahedron();
    glPopMatrix();

    glutSwapBuffers();
}

void init() {
    glClearColor(0.32, 0.32, 0.32, 1);
    glShadeModel(GL_SMOOTH);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    //LIGHT_1 (trenutno)
    const GLfloat light_ambient1[] = {0.5, 0.5, 0.5, 0.5};
    const GLfloat light_diffuse1[] = {0.5,0.5,0.5,0.5};
    const GLfloat light_specular1[] = {0.5,0.5,0.5,0.5};
    const GLfloat light_position1[] = {-15.0, -1.0, 0, 1.3};

    //LIGHT_0  (pali se pritiskom na 1)
    const GLfloat light_ambient0[] = {0.1, 0.1, 0.1, 0.1};
    const GLfloat light_diffuse0[] = {1.5, 1.5, 1.5, 1.5};
    const GLfloat light_specular0[] = {1.5, 1.5, 1.5, 1.5};
    const GLfloat light_position0[] = {2.0, 1.0, 1.0, 0.0};

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

}

void RotationDirection(int x, int y) {
    if(x>320)
        ClockwiseDirection = TRUE;
    else
        ClockwiseDirection = FALSE;
}

void animateR(int value) {
    if (CubeRotation == TRUE) {
        if(ClockwiseDirection == TRUE)
            angle -= 0.5;
        else
            angle += 0.5;
        //if (angle >= 360)
            //angle = 0;
        glutPostRedisplay();
        glutTimerFunc(speed, animateR, 0);
    }
}

void animateS(int x, int y) {
    if (CubeScaling == TRUE) {
        if (y > 250)
            ScaleFactor -= 0.01;
        else
            ScaleFactor += 0.01;
        //glutPostRedisplay();
    }
}

void animateT(int x, int y) {
    if(CubeTranslating == TRUE) {
        if(y > 250) {
            translateY -= 0.1;
        }
        else {
            translateY += 0.1;
        }
        if(x > 320) {
            translateX += 0.1;
        }
        else {
            translateX -= 0.1;
        }
        glutPostRedisplay();
    }
}

void FollowMouse(int x, int y) {
    animateS(x,y);
    if(CubeRotation == TRUE)
        RotationDirection(x,y);
    glutPostRedisplay();
}

void OnMouseClick(int button, int state, int x, int y) {
    if(state == GLUT_DOWN) {
        switch(button) {
            case GLUT_LEFT_BUTTON:
                if(CubeRotation == TRUE)
                    CubeRotation = FALSE;
                else {
                    CubeRotation = TRUE;
                    RotationDirection(x,y);
                    glutTimerFunc(speed,animateR,0);
                }
                break;
            case GLUT_RIGHT_BUTTON:
                if(CubeScaling == TRUE) {

                    CubeScaling = FALSE;
                }
                else {
                    CubeScaling = TRUE;
                    //animateS(x,y);
                }
                break;
            case GLUT_MIDDLE_BUTTON:
                if(CubeTranslating == TRUE)
                    CubeTranslating = FALSE;
                else {
                    CubeTranslating = TRUE;
                    animateT(x, y);
                }
                break;

        }
    }
}

void kbd(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
            exit(0);
            break;
        case '1':
            if(Light_0 == FALSE) {
                glEnable(GL_LIGHT0);
                Light_0 = TRUE;
            }
            else {
                glDisable(GL_LIGHT0);
                Light_0 = FALSE;
            }
            break;
        case '0':
            if(Light_1 == FALSE) {
                glEnable(GL_LIGHT1);
                Light_1 = TRUE;
            }
            else {
                glDisable(GL_LIGHT1);
                Light_1 = FALSE;
            }
            break;
        case '2':
            if(Material_1 == TRUE)
                Material_1 = FALSE;
            else
                Material_1 = TRUE;
            break;
        case '3':
            if(Material_2 == TRUE)
                Material_2 = FALSE;
            else
                Material_2 = TRUE;
            break;
    }
    glutPostRedisplay();
}

void CameraControl(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            Yposition += 0.5;
            break;
        case GLUT_KEY_DOWN:
            Yposition -= 0.5;
            break;
        case GLUT_KEY_RIGHT:
            Xposition += 0.5;
            break;
        case GLUT_KEY_LEFT:
            Xposition -= 0.5;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 500);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("3D MODELI - ZAVRSNI PROJEKAT");
    glutKeyboardFunc(kbd);
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutSpecialFunc(CameraControl); //callback funkcija koja omoguca koristenje "strelica" tipki
    glutMouseFunc(OnMouseClick);
    glutPassiveMotionFunc(FollowMouse);

    glutMainLoop();
}