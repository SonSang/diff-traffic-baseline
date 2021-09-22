#ifndef RENDER_HPP
#define RENDER_HPP

#include "drawables.hpp"

namespace city_sight {

void Render()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Call draw on every thing.
   for (uint i = 0; i < city_global::csDrawables.size(); i++)
	{
      city_global::csDrawables[i]->draw((float)city_global::_dt,
                                        (float)city_global::_t);
	}

   //   eglSwapBuffers();
}

}  // namespace city_sight

#endif
