
import string

__version__ = string.split('$Revision: 1.1.1.1 $')[1]
__date__ = string.join(string.split('$Date: 2015/02/15 19:25:21 $')[1:3], ' ')
__author__ = 'Modificado por ___________'

#
#

from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import sys
from OpenGL.GL.ARB.multitexture import *
from PIL.Image import *
from math import *
ESCAPE = '\033'
def LoadTexture(name):
    # global texture
    image = open(name)

    ix = image.size[0]
    iy = image.size[1]
    image = image.tobytes("raw", "RGBX", 0, -1)

    # Create Texture
    id = glGenTextures(1)
    glBindTexture(GL_TEXTURE_2D, id)  # 2d texture (x and y size)

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1)
    glTexImage2D(GL_TEXTURE_2D, 0, 3, ix, iy, 0, GL_RGBA, GL_UNSIGNED_BYTE, image)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL)

    return id
# A general OpenGL initialization function.  Sets all of the initial parameters.


def InitGL(Width, Height):  # We call this right after our OpenGL window is created.
    global textures, glMultiTexCoord2f, glActiveTexture, GL_TEXTURE0

    print 'Checking for extension support'
    if not glMultiTexCoord2f:
        print 'No OpenGL v1.3 built-in multi-texture support, checking for extension'
        if not glMultiTexCoord2fARB:
            print 'No GL_ARB_multitexture support, sorry, cannot run this demo!'
            sys.exit(1)
        else:
            glMultiTexCoord2f = glMultiTexCoord2fARB
            glActiveTexture = glActiveTextureARB
            GL_TEXTURE0 = GL_TEXTURE0_ARB
    else:
        print 'Using OpenGL v1.3 built-in multi-texture support'
    try:
        if not glInitMultitextureARB():
            print "Help!  No GL_ARB_multitexture"
            sys.exit(1)
    except NameError, err:
        # don't need to init a built-in (or an extension any more, for that matter)
        pass

    glActiveTexture(GL_TEXTURE0)
    LoadTexture('grass.jpeg')#se cambio la textura a 
    glEnable(GL_TEXTURE_2D)

    #glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND)

    glClearColor(0.0, 0.0, 0.0, 0.0)  # This Will Clear The Background Color To Black
    glClearDepth(1.0)  # Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS)  # The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST)  # Enables Depth Testing
    glShadeModel(GL_SMOOTH)  # Enables Smooth Color Shading

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()  # Reset The Projection Matrix
    # Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0, float(Width) / float(Height), 0.1, 100.0)

    glMatrixMode(GL_MODELVIEW)


def ReSizeGLScene(Width, Height):
    if Height == 0:  # Prevent A Divide By Zero If The Window Is Too Small
        Height = 1

    glViewport(0, 0, Width, Height)  # Reset The Current Viewport And Perspective Transformation
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45.0, float(Width) / float(Height), 0.1, 100.0)
    gluLookAt(0,0,5,2,2,5,0,0,1)
    glMatrixMode(GL_MODELVIEW)

def dibujar_piso(x,y,z):
	glPushMatrix();
	glTranslatef(x, y, z)
	glBegin(GL_QUADS)  # Start Drawing The Cube
  	# Front Face (note that the texture's corners have to match the quad's corners)
  	glMultiTexCoord2f(GL_TEXTURE0_ARB, 0.0, 0.0) 
    	glVertex3f(-1.0, -1.0, 1.0)  # Bottom Left Of The Texture and Quad
    	glMultiTexCoord2f(GL_TEXTURE0_ARB, 1.0, 0.0) 
    	glVertex3f(1.0, -1.0, 1.0)  # Bottom Right Of The Texture and Quad
    	glMultiTexCoord2f(GL_TEXTURE0_ARB, 1.0, 1.0) 
    	glVertex3f(1.0, 1.0, 1.0)  # Top Right Of The Texture and Quad
    	glMultiTexCoord2f(GL_TEXTURE0_ARB, 0.0, 1.0) 
    	glVertex3f(-1.0, 1.0, 1.0)  # Top Left Of The Texture and Quad
    	glEnd()
	glPopMatrix();

def camara():
	global x,y,z,vx,vz
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 128.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity()
	gluLookAt(0+x,0+y,5+z, 2+vx, 2+vy, 5+vz, 0.0, 0.0, 1.0);
	glutPostRedisplay()
    

def DrawGLScene():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)  # Clear The Screen And The Depth Buffer
    camara();  # Reset The View
    global vx,vy,vz
    #glTranslatef(0.0, 0.0, -10.0)  # Move Into The Screen
    # Note there does not seem to be support for this call.
    # glBindTexture(GL_TEXTURE_2D,texture)	# Rotate The Pyramid On It's Y Axis
    glPushMatrix()
    glTranslatef(-50,-50,0)#para ubicarte en el centro
    for i in range(0,100,2):
    	for j in range(0,100,2):
    		dibujar_piso(i,j,0);
    glPopMatrix()
    
    glPushMatrix()
    glTranslatef(2+vx,2+vy,5+vz)#para ubicarte en el centro
    glColor3f(0.0, 0.0, 1.0);
    glutWireSphere(.5,28,28);
    glPopMatrix()
    
    #  since this is double buffered, swap the buffers to display what just got drawn.
    glutSwapBuffers()

# The function called whenever a key is pressed. Note the use of Python tuples to pass in: (key, x, y)

def keyPressed(*args):
	global x,y,z,vx,vy,vz
	if args[0] == 'q':
		sys.exit()
	if args[0] == 'a':
		x-=0.1
		vx-=0.1
	if args[0] == 'w':
		y+=0.1
		vy+=0.1
	if args[0] == 's':
		y-=0.1
		vy-=0.1
	if args[0] == 'd':
		x+=0.1
		vx+=0.1
	if args[0] == 'u':
		z+=0.5
		vz+=0.5
	if args[0] == 'i':
		z-=0.5
		vz-=0.5
	if args[0] == '4':
		vx-=0.1
	if args[0] == '8':
		vy+=0.1
	if args[0] == '5':
		vy-=0.1
	if args[0] == '6':
		vx+=0.1
	if args[0] == '7':
		vz+=0.1
	if args[0] == '1':
		vz-=0.1
	glutPostRedisplay()

vx=0
vy=0
vz=0
x=0
y=0
z=0

def main():
    global window
    glutInit(sys.argv)

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)

    # get a 640 x 480 window
    glutInitWindowSize(640, 480)

    # the window starts at the upper left corner of the screen
    glutInitWindowPosition(0, 0)

    # Okay, like the C version we retain the window id to use when closing, but for those of you new
    # to Python (like myself), remember this assignment would make the variable local and not global
    # if it weren't for the global declaration at the start of main.
    window = glutCreateWindow("Chavin de Huantar")

    # Register the drawing function with glut, BUT in Python land, at least using PyOpenGL, we need to
    # set the function pointer and invoke a function to actually register the callback, otherwise it
    # would be very much like the C version of the code.
    glutDisplayFunc(DrawGLScene)

    # Uncomment this line to get full screen.
    # glutFullScreen()

    # When we are doing nothing, redraw the scene.
    glutIdleFunc(DrawGLScene)

    # Register the function called when our window is resized.
    glutReshapeFunc(ReSizeGLScene)

    # Register the function called when the keyboard is pressed.
    glutKeyboardFunc(keyPressed)

    # Initialize our window.
    InitGL(640, 480)

    # Start Event Processing Engine
    glutMainLoop()
main()
