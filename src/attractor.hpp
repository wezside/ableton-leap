#ifndef __FORCE_ATTRACTOR_HPP__
#define __FORCE_ATTRACTOR_HPP__

#include "force.hpp"

namespace wezside
{
	class Attractor: public wezside::Force
	{
	private:

	public:
		Attractor(float xpos, float ypos, float zpos)
		{
			x = xpos;
			y = ypos;
			z = zpos;
			gravity = 0.25;
			forcemass = 150;
			forcemass_limit = 200;
			target = ofVec3f(0);
			acc3f = ofVec3f(0);
		}
		void update(ofVec3f loc, float mass)
		{
			ofVec3f p = ofVec3f(x, y, z) - loc;
			float distance = p.length();
			distance = ofClamp(distance, 250.0f, 1010.0f);
			p.normalize();
			if (forcemass > forcemass_limit) forcemass = forcemass_limit;
			float strength = (gravity * forcemass * mass) / (distance * distance);
			p *= strength;
			acc3f = p;
		}
		void draw()
		{
			ofSetColor(0.0f, 255.0f, 255.0f);
			ofCircle(x, y, z, 5.0f);
			ofSetColor(255.0f);
		}
		float gravity;
		float forcemass;
		float forcemass_limit;
	};
}
#endif //__FORCE_ATTRACTOR_HPP__