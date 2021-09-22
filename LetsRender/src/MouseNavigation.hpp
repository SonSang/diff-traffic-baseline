#ifndef MOUSE_NAVIGATION_HPP
#define MOUSE_NAVIGATION_HPP

#include <GL/glut.h>

static void
zprMouse(int button, int state, int x, int y)
{
   GLint viewport[4];

   /* Do picking */
   // if (state==GLUT_DOWN)
   //    zprPick(x,glutGet(GLUT_WINDOW_HEIGHT)-1-y,3,3);

    _mouseX = x;
    _mouseY = y;

    if (state==GLUT_UP)
        switch (button)
        {
            case GLUT_LEFT_BUTTON:   _mouseLeft   = false; break;
            case GLUT_MIDDLE_BUTTON: _mouseMiddle = false; break;
            case GLUT_RIGHT_BUTTON:  _mouseRight  = false; break;
        }
    else
        switch (button)
        {
            case GLUT_LEFT_BUTTON:   _mouseLeft   = true; break;
            case GLUT_MIDDLE_BUTTON: _mouseMiddle = true; break;
            case GLUT_RIGHT_BUTTON:  _mouseRight  = true; break;
        }

    glGetIntegerv(GL_VIEWPORT,viewport);
    pos(&_dragPosX,&_dragPosY,&_dragPosZ,x,y,viewport);
    glutPostRedisplay();
}

static void
zprMotion(int x, int y)
{
    bool changed = false;

    const int dx = x - _mouseX;
    const int dy = y - _mouseY;

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT,viewport);

    if (dx==0 && dy==0)
        return;

    if (_mouseMiddle || (_mouseLeft && _mouseRight))
    {
        double s = exp((double)dy*0.01);

        glTranslatef( zprReferencePoint[0], zprReferencePoint[1], zprReferencePoint[2]);
        glScalef(s,s,s);
        glTranslatef(-zprReferencePoint[0],-zprReferencePoint[1],-zprReferencePoint[2]);

        changed = true;
    }
    else
        if (_mouseLeft)
        {
            double ax,ay,az;
            double bx,by,bz;
            double angle;

            ax = dy;
            ay = dx;
            az = 0.0;
            angle = vlen(ax,ay,az)/(double)(viewport[2]+1)*180.0;

            /* Use inverse matrix to determine local axis of rotation */

            bx = _matrixInverse[0]*ax + _matrixInverse[4]*ay + _matrixInverse[8] *az;
            by = _matrixInverse[1]*ax + _matrixInverse[5]*ay + _matrixInverse[9] *az;
            bz = _matrixInverse[2]*ax + _matrixInverse[6]*ay + _matrixInverse[10]*az;

            glTranslatef( zprReferencePoint[0], zprReferencePoint[1], zprReferencePoint[2]);
            glRotatef(angle,bx,by,bz);
            glTranslatef(-zprReferencePoint[0],-zprReferencePoint[1],-zprReferencePoint[2]);

            changed = true;
        }
        else
            if (_mouseRight)
            {
                double px,py,pz;

                pos(&px,&py,&pz,x,y,viewport);

                glLoadIdentity();
                glTranslatef(px-_dragPosX,py-_dragPosY,pz-_dragPosZ);
                glMultMatrixd(_matrix);

                _dragPosX = px;
                _dragPosY = py;
                _dragPosZ = pz;

                changed = true;
            }

    _mouseX = x;
    _mouseY = y;

    if (changed)
    {
        getMatrix();
        glutPostRedisplay();
    }
}

#endif
