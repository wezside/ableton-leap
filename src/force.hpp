#ifndef __FORCE_HPP__
#define __FORCE_HPP__

namespace wezside
{
	class Force
	{
	protected:
		// Force vector components
		float x, y, z;

		// Any additional target to measure distance to
		ofVec3f target;

		// Acceleration vector
		ofVec3f acc3f;

	public:
		Force(){};
		Force(float xpos, float ypos, float zpos)
		{
			x = xpos;
			y = ypos;
			z = zpos;
			target = ofVec3f(0);
			acc3f = ofVec3f(0);
		}

		// Copy constructor
		Force(const Force& f) : x(f.x), y(f.y), z(f.z), acc3f(f.acc3f) {}

		// Copy assignment constructor
		Force& operator=(Force& f) 
		{
			x = f.x;
			y = f.y;
			z = f.z;
			acc3f = f.acc3f;
			return *this;
		};          		

		virtual ~Force(){}

		virtual void update(ofVec3f loc, float mass)
		{
			acc3f += ofVec3f(x, y, z);
		}
		virtual ofVec3f get() {return acc3f;}
		virtual void setTarget(ofVec2f t){target = t;}
		virtual void setTarget(ofVec3f t){target = t;}
		virtual void setPosition(float xpos, float ypos, float zpos)
		{
			x = xpos;
			y = ypos;
			z = zpos;
		}
		virtual void draw() 
		{
			ofSetColor(255.0f, 122.0f);
			ofCircle(x, y, z, 10);
		}
	};
}
#endif // __FORCE_HPP__