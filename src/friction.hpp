#ifndef __FORCE_FRICTION_HPP__
#define __FORCE_FRICTION_HPP__

#include "force.hpp"

namespace wezside
{
	class Attractor: public wezside::Force
	{
	private:

	public:
		Friction(float xpos, float ypos, float zpos)
		{
			x = xpos;
			y = ypos;
			z = zpos;
			gravity = 0.6;
			target = ofVec3f(0);
			acc3f = ofVec3f(0);
		}
		void update(ofVec3f loc, float mass)
		{
/*			float c = 0.01;
			float normal = 1;
			float frictionMag = c*normal;
			friction = vel;
			friction *= -1;
			friction.normalize();
			friction *= frictionMag;
			acc += friction;*/
		}
		void draw(){}
	};
}
#endif //__FORCE_FRICTION_HPP__