#ifndef MOUSE_NAVIGATION_HPP
#define MOUSE_NAVIGATION_HPP

#include <GL/glut.h>
#include <algorithm>

#include "camera.hpp"

static double _left   = 0.0;
static double _right  = 0.0;
static double _bottom = 0.0;
static double _top    = 0.0;
static double _zNear  = -10.0;
static double _zFar   = 10.0;

static int  _mouseX      = 0;
static int  _mouseY      = 0;
static bool _mouseLeft   = false;
static bool _mouseMiddle = false;
static bool _mouseRight  = false;

static double _dragPosX  = 0.0;
static double _dragPosY  = 0.0;
static double _dragPosZ  = 0.0;

static double _matrix[16];
static double _matrixInverse[16];


static void
invertMatrix(const GLdouble *m, GLdouble *out )
{

/* NB. OpenGL Matrices are COLUMN major. */
#define MAT(m,r,c) (m)[(c)*4+(r)]

/* Here's some shorthand converting standard (row,column) to index. */
#define m11 MAT(m,0,0)
#define m12 MAT(m,0,1)
#define m13 MAT(m,0,2)
#define m14 MAT(m,0,3)
#define m21 MAT(m,1,0)
#define m22 MAT(m,1,1)
#define m23 MAT(m,1,2)
#define m24 MAT(m,1,3)
#define m31 MAT(m,2,0)
#define m32 MAT(m,2,1)
#define m33 MAT(m,2,2)
#define m34 MAT(m,2,3)
#define m41 MAT(m,3,0)
#define m42 MAT(m,3,1)
#define m43 MAT(m,3,2)
#define m44 MAT(m,3,3)

   GLdouble det;
   GLdouble d12, d13, d23, d24, d34, d41;
   GLdouble tmp[16]; /* Allow out == in. */

   /* Inverse = adjoint / det. (See linear algebra texts.)*/

   /* pre-compute 2x2 dets for last two rows when computing */
   /* cofactors of first two rows. */
   d12 = (m31*m42-m41*m32);
   d13 = (m31*m43-m41*m33);
   d23 = (m32*m43-m42*m33);
   d24 = (m32*m44-m42*m34);
   d34 = (m33*m44-m43*m34);
   d41 = (m34*m41-m44*m31);

   tmp[0] =  (m22 * d34 - m23 * d24 + m24 * d23);
   tmp[1] = -(m21 * d34 + m23 * d41 + m24 * d13);
   tmp[2] =  (m21 * d24 + m22 * d41 + m24 * d12);
   tmp[3] = -(m21 * d23 - m22 * d13 + m23 * d12);

   /* Compute determinant as early as possible using these cofactors. */
   det = m11 * tmp[0] + m12 * tmp[1] + m13 * tmp[2] + m14 * tmp[3];

   /* Run singularity test. */
   if (det == 0.0) {
      /* printf("invert_matrix: Warning: Singular matrix.\n"); */
/*    memcpy(out,_identity,16*sizeof(double)); */
   }
   else {
      GLdouble invDet = 1.0 / det;
      /* Compute rest of inverse. */
      tmp[0] *= invDet;
      tmp[1] *= invDet;
      tmp[2] *= invDet;
      tmp[3] *= invDet;

      tmp[4] = -(m12 * d34 - m13 * d24 + m14 * d23) * invDet;
      tmp[5] =  (m11 * d34 + m13 * d41 + m14 * d13) * invDet;
      tmp[6] = -(m11 * d24 + m12 * d41 + m14 * d12) * invDet;
      tmp[7] =  (m11 * d23 - m12 * d13 + m13 * d12) * invDet;

      /* Pre-compute 2x2 dets for first two rows when computing */
      /* cofactors of last two rows. */
      d12 = m11*m22-m21*m12;
      d13 = m11*m23-m21*m13;
      d23 = m12*m23-m22*m13;
      d24 = m12*m24-m22*m14;
      d34 = m13*m24-m23*m14;
      d41 = m14*m21-m24*m11;

      tmp[8] =  (m42 * d34 - m43 * d24 + m44 * d23) * invDet;
      tmp[9] = -(m41 * d34 + m43 * d41 + m44 * d13) * invDet;
      tmp[10] =  (m41 * d24 + m42 * d41 + m44 * d12) * invDet;
      tmp[11] = -(m41 * d23 - m42 * d13 + m43 * d12) * invDet;
      tmp[12] = -(m32 * d34 - m33 * d24 + m34 * d23) * invDet;
      tmp[13] =  (m31 * d34 + m33 * d41 + m34 * d13) * invDet;
      tmp[14] = -(m31 * d24 + m32 * d41 + m34 * d12) * invDet;
      tmp[15] =  (m31 * d23 - m32 * d13 + m33 * d12) * invDet;

      memcpy(out, tmp, 16*sizeof(GLdouble));
   }

#undef m11
#undef m12
#undef m13
#undef m14
#undef m21
#undef m22
#undef m23
#undef m24
#undef m31
#undef m32
#undef m33
#undef m34
#undef m41
#undef m42
#undef m43
#undef m44
#undef MAT
}

static void
getMatrix()
{
    glGetDoublev(GL_MODELVIEW_MATRIX,_matrix);
    invertMatrix(_matrix,_matrixInverse);
}

static double
vlen(double x,double y,double z)
{
    return sqrt(x*x+y*y+z*z);
}

static void
pos(double *px,double *py,double *pz,const int x,const int y,const int *viewport)
{
    /*
      Use the ortho projection and viewport information
      to map from mouse co-ordinates back into world
      co-ordinates
    */

    *px = (double)(x-viewport[0])/(double)(viewport[2]);
    *py = (double)(y-viewport[1])/(double)(viewport[3]);

    *px = _left + (*px)*(_right-_left);
    *py = _top  + (*py)*(_bottom-_top);
    *pz = _zNear;
}

static void
zprMouse(int button, int state, int x, int y)
{
    _mouseX = x;
    _mouseY = y;

    if (state == GLUT_UP) {
       if (button == GLUT_LEFT_BUTTON)
          _mouseLeft   = false;
       if (button == GLUT_MIDDLE_BUTTON)
          _mouseMiddle   = false;
       if (button == GLUT_RIGHT_BUTTON)
          _mouseRight   = false;
    }
    else {
          if (button == GLUT_LEFT_BUTTON)
             _mouseLeft   = true;
          if (button == GLUT_MIDDLE_BUTTON)
             _mouseMiddle   = true;
          if (button == GLUT_RIGHT_BUTTON)
             _mouseRight   = true;
    }

    glutPostRedisplay();
}

static void
zprMotion(int x, int y)
{
    bool changed = false;

    const int dx = x - _mouseX;
    const int dy = y - _mouseY;

    if (dx == 0 && dy == 0)
        return;

    if (_mouseMiddle || (_mouseLeft && _mouseRight)) {
       changed = true;
    }
    else {
       if (_mouseLeft) {
          city_sight::csCamera::getInstance()->Translate(-dx, dy, 0);
          changed = true;
       }
       else if (_mouseRight) {
          double s = exp((double)abs(dy)*0.7);

          s = std::min(s, 100.0);

          if (dy < 0)
             s *= -1;

          city_sight::csCamera::getInstance()->Translate(0, 0, s);

          changed = true;
       }
    }

    _mouseX = x;
    _mouseY = y;

    if (changed)
       glutPostRedisplay();

}

#endif
