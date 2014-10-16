#ifndef __FORCE_REPELLER_HPP__
#define __FORCE_REPELLER_HPP__

#include "force.hpp"

namespace wezside
{
	class Repeller: public wezside::Force
	{
	private:
		float strength;
		float cx;
		float cy;

	public:
		Repeller(float xpos, float ypos, float zpos)
		{
			x = xpos;
			y = ypos;
			z = zpos;
			gravity = 3.35;
			forcemass = 15.0f;
			forcemass_limit = 200.0f;
			target = ofVec3f(0);
			acc3f = ofVec3f(0);
			cx = ofGetWindowWidth() * 0.5;
			cy = ofGetWindowHeight() * 0.5;
		}
		void update(ofVec3f loc, float mass)
		{
			// ofVec3f dir = ofVec3f(x, y, z) - loc;
			ofVec3f dir = ofVec3f(target.x - cx, target.y - cy, z) - loc;
			float d = dir.length();
			d = ofClamp(d, 1.0f, 5000.0f);
			dir.normalize();
			if (forcemass > forcemass_limit) forcemass = forcemass_limit;
			float force = -1.0f * ((gravity * forcemass * mass) / (d * d));
			dir *= force;
			acc3f = dir;
		}	

		float gravity;
		float forcemass;
		float forcemass_limit;
	};
}
#endif //__FORCE_REPELLER_HPP__