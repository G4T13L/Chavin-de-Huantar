/*
OPERACION CHAVIN DE HUANTAR
*/

#include "texturas.cpp"
#include <iostream>
#include "Camera.cpp"
#include "math.h"
#include "GL/glut.h"
using namespace std;

void Display();
void Reshape(int w,int h);
void Keyboard (unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void MouseMotion(int x, int y);
void Mouse(int button, int state, int x, int y);
void Timer(int value);
void Idle();
void Init();

Camera g_camera;
bool g_key[256];
bool g_shift_down = false;
int g_viewport_width = 0;
int g_viewport_height = 0;
bool g_mouse_left_down = false;
bool g_mouse_right_down = false;
float sigilo = 0.3;
bool v3raP = false;

// Movement settings
const float g_translation_speed = 0.08;
const float g_rotation_speed = M_PI/180*0.2;

int main (int argc, char **argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowPosition(0,0);
   glutInitWindowSize(600, 500);
   glutCreateWindow("OPERACION CHAVIN DE HUANTAR");

   Init();
   glEnable(GL_DEPTH_TEST);
   loadTextures();

   //esconde el mouse en el medio
   glutSetCursor(GLUT_CURSOR_NONE);

   glutIgnoreKeyRepeat(1);

   glutDisplayFunc(Display);
   glutReshapeFunc(Reshape);
   glutMouseFunc(Mouse);
   glutMotionFunc(MouseMotion);
   glutPassiveMotionFunc(MouseMotion);
   glutKeyboardFunc(Keyboard);
   glutKeyboardUpFunc(KeyboardUp);
   glutIdleFunc(Idle);

   glutTimerFunc(1, Timer, 0);
   glutMainLoop();

   return 0;
}

void Grid()
{
   glColor3f(1,1,1);

/*    glPushMatrix();

    for(int i=-50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(i, 0, -50);
        glVertex3f(i, 0, 50);
        glEnd();
    }

    for(int i=-50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(-50, 0, i);
        glVertex3f(50, 0, i);
        glEnd();
    }

    glPopMatrix();
    */
   float dim = 25;
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[0] );
   glBegin(GL_QUADS);
   glTexCoord2f(0,0);
   glVertex3f(-2*dim,0,2*dim);
   glTexCoord2f(num*dim,0);
   glVertex3f(2*dim,0,2*dim);
   glTexCoord2f(num*dim,num*dim);
   glVertex3f(2*dim,0,-2*dim);
   glTexCoord2f(0,num*dim);
   glVertex3f(-2*dim,0,-2*dim);
   glEnd();
}

void cursor(void){
  float vec[3];
  float pos[3];
  g_camera.GetDirectionVector(vec[0],vec[1],vec[2]);
  g_camera.GetPos(pos[0],pos[1],pos[2]);
  glLineWidth(2);

  glPushMatrix();

  glTranslatef(pos[0]+vec[0],pos[1]+vec[1],pos[2]+vec[2]);
  glRotatef(g_camera.GetYaw()*180/M_PI,0,-1,0);
  glRotatef(g_camera.GetPitch()*180/M_PI,0,0,1);

  glColor3f(1,0,0);

/*

  GLUquadric *quadratic;

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texID[1]);

  quadratic = gluNewQuadric();
  gluQuadricNormals(quadratic, GLU_SMOOTH);
  gluQuadricTexture(quadratic, GL_TRUE);
  gluSphere(quadratic,0.1,40,40);

*/
  glBegin(GL_LINES);
  glVertex3f(0,0,0.05);
  glVertex3f(0,0,0.02);

  glVertex3f(0,0,-0.05);
  glVertex3f(0,0,-0.02);

  glVertex3f(0,0.05,0);
  glVertex3f(0,0.02,0);

  glVertex3f(0,-0.05,0);
  glVertex3f(0,-0.02,0);

  glEnd();

  //glutWireTeapot(0.5);

  glPopMatrix();
  glLineWidth(1);
}
float estado=0;

void personaje(){
   float vec[3];
   float pos[3];
   g_camera.GetDirectionVector(vec[0],vec[1],vec[2]);
   g_camera.GetPos(pos[0],pos[1],pos[2]);
   glPushMatrix();

   glTranslatef(pos[0]-vec[0],pos[1]-vec[1],pos[2]-vec[2]);

   if(g_key['w']==1||g_key['a']==1||g_key['d']==1||g_key['s']==1){
      glRotatef(g_camera.GetYaw()*180/M_PI+180,0,-1,0);
      estado = g_camera.GetYaw()*180/M_PI+180;
   } else{
      glRotatef(estado, 0,-1,0);
   }

   //glRotatef(g_camera.GetPitch()*180/M_PI,0,0,1);
   glutWireTeapot(0.5);

   glPopMatrix();

}

void Init(){
   glClearColor (1,1,1,1.0);
   //glEnable(GL_DEPTH_TEST);

   //incio de posicion
   g_camera.SetPos(0,2,0);

}


void cubo(){

      float lado = 0.5;
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, texID[1] );
       glBegin(GL_QUADS);
   	glTexCoord2f(0,0);
   	glVertex3f(-2*lado,0,2*lado);
   	glTexCoord2f(0.5,0);
   	glVertex3f(-2*lado,0,-2*lado);
         glTexCoord2f(0.5,1);
         glVertex3f(-2*lado,4*lado,-2*lado);
         glTexCoord2f(0,1);
         glVertex3f(-2*lado,4*lado,2*lado);

         glTexCoord2f(0.5,0);
         glVertex3f(-2*lado,0,-2*lado);
         glTexCoord2f(1,0);
         glVertex3f(2*lado,0,-2*lado);
         glTexCoord2f(1,1);
         glVertex3f(2*lado,4*lado,-2*lado);
         glTexCoord2f(0.5,1);
         glVertex3f(-2*lado,4*lado,-2*lado);

         glTexCoord2f(1,0);
         glVertex3f(2*lado,0,-2*lado);
         glTexCoord2f(0.5,0);
         glVertex3f(2*lado,0,2*lado);
         glTexCoord2f(0.5,1);
         glVertex3f(2*lado,4*lado,2*lado);
         glTexCoord2f(1,1);
         glVertex3f(2*lado,4*lado,-2*lado);

         glTexCoord2f(0.5,0);
         glVertex3f(2*lado,0,2*lado);
         glTexCoord2f(0,0);
         glVertex3f(-2*lado,0,2*lado);
         glTexCoord2f(0,1);
         glVertex3f(-2*lado,4*lado,2*lado);
         glTexCoord2f(0.5,1);
         glVertex3f(2*lado,4*lado,2*lado);

         glEnd();
}

void Display (void) {
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glEnable(GL_TEXTURE_2D);

   if(v3raP)
      g_camera.Refresh3p();
   else
      g_camera.Refresh();
   glColor3f(0,1,0);

   Grid();
   glutWireTeapot(0.5);
   personaje();
   cursor();
   glPushMatrix();
   glTranslatef(0,2,3);
   cubo();
   glPopMatrix();

   glutSwapBuffers(); //swap the buffers
}

void Reshape (int w, int h) {
    g_viewport_width = w;
    g_viewport_height = h;

    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection

    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0 , 100.0); //set the perspective (angle of sight, width, height, ,depth)
    //glMatrixMode (GL_MODELVIEW); //set the matrix back to model
}

const float g=0.00000987;
float v=0;
float t=0;

void Keyboard(unsigned char key, int x, int y){
    if(key == 27) {
        exit(0);
    }
    if(key == '<') {
        g_camera.setHeight(g_camera.GetY()-1);
    }
    if(key == ' ') {
        v=0.00464*1.5;
        g_camera.setHeight(2.000001);
    }
    if(key == 'f') {
        v3raP = !v3raP;
    }

    glutWarpPointer(g_viewport_width/2, g_viewport_height/2);

    if(glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
        g_shift_down = true;
    }
    else {
        g_shift_down = false;
    }

    g_key[key] = true;
}

void KeyboardUp(unsigned char key, int x, int y){
  if(key=='w' || key=='W') {
    g_key['w'] = false;
    g_key['W'] = false;
  }
  if(key=='s' || key=='S') {
    g_key['s'] = false;
    g_key['S'] = false;
  }
  if(key=='a' || key=='A') {
    g_key['a'] = false;
    g_key['A'] = false;
  }
  if(key=='d' || key=='D') {
    g_key['d'] = false;
    g_key['D'] = false;
  }
  if(key=='<'){
     g_key['<'] = false;
     if(g_camera.GetY()>2){
           g_camera.setHeight(g_camera.GetY() +1);
     }else{
        g_camera.setHeight(2);
     }
 }


}

float velocidad (){
   return v = v - g*t;
}


void gravedad(){
   if(g_camera.GetY()<0){
      //toca el suelo
      g_camera.setHeight(0);
      v=0;
      t=0;
   }
   else if(g_camera.GetY()>2){
         g_camera.setHeight(g_camera.GetY() +velocidad()*t-g*t*t/2);
   }else{
      v=0;
      t=0;
   }
}

void Timer(int value){
    if(g_key['w'] || g_key['W']) {
      if (g_shift_down == true) {
         if(v3raP)
            g_camera.Move3p(g_translation_speed*sigilo);
         else
            g_camera.Move(g_translation_speed*sigilo);
      }else
         if(v3raP)
            g_camera.Move3p(g_translation_speed);
         else
            g_camera.Move(g_translation_speed);
    }
    if(g_key['s'] || g_key['S']) {
      if (g_shift_down == true) {
         if(v3raP)
            g_camera.Move3p(-g_translation_speed*sigilo);
         else
            g_camera.Move(-g_translation_speed*sigilo);
      }else
         if(v3raP)
            g_camera.Move3p(-g_translation_speed);
         else
            g_camera.Move(-g_translation_speed);
    }
    if(g_key['a'] || g_key['A']) {
      if (g_shift_down == true) {
         if(v3raP)
            g_camera.Strafe3p(g_translation_speed*sigilo);
         else
            g_camera.Strafe(g_translation_speed*sigilo);
      }else
         if(v3raP)
            g_camera.Strafe3p(g_translation_speed);
         else
            g_camera.Strafe(g_translation_speed);
      }
    if(g_key['d'] || g_key['D']) {
      if (g_shift_down == true) {

        if(v3raP)
           g_camera.Strafe3p(-g_translation_speed*sigilo);
        else
           g_camera.Strafe(-g_translation_speed*sigilo);
      }else
         if(v3raP)
            g_camera.Strafe3p(-g_translation_speed);
         else
            g_camera.Strafe(-g_translation_speed);
    }
    if(g_mouse_left_down) {
        g_camera.Fly(-g_translation_speed);
    }
    if(g_mouse_right_down) {
        g_camera.Fly(g_translation_speed*10);
    }
    gravedad();
    t++;
    //cout << "velocidad: "<<v<<endl<< "altura:"<< g_camera.GetY()<<endl;
    glutTimerFunc(1, Timer, 0);
}

void Idle(){
    Display();
}


void Mouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN) {
        if(button == GLUT_LEFT_BUTTON) {
            g_mouse_left_down = true;
        }
        else if(button == GLUT_RIGHT_BUTTON) {
            g_mouse_right_down = true;
        }
    }
    else if(state == GLUT_UP) {
        if(button == GLUT_LEFT_BUTTON) {
            g_mouse_left_down = false;
        }
        else if(button == GLUT_RIGHT_BUTTON) {
            g_mouse_right_down = false;
        }
    }
}

void MouseMotion(int x, int y)
{
    // This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
    // This avoids it being called recursively and hanging up the event loop
    static bool just_warped = false;

    if(just_warped) {
      just_warped = false;
      return;
    }

    int dx = x - g_viewport_width/2;
    int dy =g_viewport_height/2 - y;
    if(dx) {
      g_camera.RotateYaw(g_rotation_speed*dx);
    }
    if(dy) {
      if(v3raP)
         g_camera.RotatePitch3p(g_rotation_speed*dy);
      else
         g_camera.RotatePitch(g_rotation_speed*dy);
    }

    glutWarpPointer(g_viewport_width/2, g_viewport_height/2);
    just_warped = true;
}
