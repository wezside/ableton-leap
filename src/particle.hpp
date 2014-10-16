#include "force.hpp"

namespace wezside
{
	class Particle
	{
	
	private:
		// RGB random boundaries
		float m_fRmin, m_fGmin, m_fBmin;
		float m_fRmax, m_fGmax, m_fBmax;

		// Location random boundaries
		float m_fspawn_xmin, m_fspawn_ymin, m_fspawn_zmin;
		float m_fspawn_xmax, m_fspawn_ymax, m_fspawn_zmax;

		// Velocity random boundaries
		float m_fVel_xmin, m_fVel_ymin, m_fVel_zmin;
		float m_fVel_xmax, m_fVel_ymax, m_fVel_zmax;

		// Max delay and life span
		int m_nMaxDelay, m_nMaxLife;

		// Alpha start + end value
		float m_fAmin, m_fAmax;

		// Maximum velocity 
		int m_nVel_max;

		// Collection of forces to apply to the particle
		std::vector<Force*> forces;

		// Target vector used for force calculation
		ofVec3f target;

	public:
		Particle(){}
		~Particle()
		{
		}
		void init()
		{
			// RGB random boundaries
			m_fRmin = m_fGmin = m_fBmin = 255.0;
			m_fRmax = m_fGmax = m_fBmax = 255.0;

			// Location random boundaries
			ofSeedRandom();
			m_fspawn_xmin = -200.0f;
			m_fspawn_ymin = -ofGetHeight() * 0.5f;
			m_fspawn_zmin = -500.0;
			m_fspawn_xmax = 200.0f;
			m_fspawn_ymax = -ofGetHeight() * 0.5f - ofGetHeight();
			m_fspawn_zmax = -500.0;

			// Velocity random boundaries
			m_fVel_xmin = -1.0f;
			m_fVel_xmax = 1.0f;
			m_fVel_ymin = m_fVel_zmin = 0.0f;
			m_fVel_ymax = m_fVel_zmax = 0.0f;

			// Max delay and life span
			m_nMaxDelay = 50.0; 
			m_nMaxLife = 100.0;

			// Alpha start + end value
			m_fAmin = 0.0;
			m_fAmax = 0.5;

			// Maximum velocity 
			m_nVel_max = ofRandom(2, 4);

			// Target vector used for force calculation
			target = ofVec3f(0);

			reset();
		}
		void reset()
		{
			float r = ofRandom(m_fRmin, m_fRmax) / 255.0;
			float g = ofRandom(m_fGmin, m_fGmax) / 255.0;
			float b = ofRandom(m_fBmin, m_fBmax) / 255.0;

			col[0] = r;
			col[1] = g;
			col[2] = b;
			col[3] = m_fAmax;

			lerp[0] = 0.0;
			lerp[1] = 0.0;

			size = ofRandom(2, 50);
			mass = ofRandom(40, 150.0);

			loc.x = ofRandom(m_fspawn_xmin, m_fspawn_xmax);
			loc.y = ofRandom(m_fspawn_ymin, m_fspawn_ymax);
			loc.z = ofRandom(m_fspawn_zmin, m_fspawn_zmax);
			
			pos = loc;

			delay[0] = 0.0;
			delay[1] = ofRandom(m_nMaxDelay);

			life[0] = 0.0;
			life[1] = m_nMaxLife;

			alpha[0] = m_fAmin;
			alpha[1] = col[3];

			vel[0] = ofRandom(m_fVel_xmin, m_fVel_xmax);
			vel[1] = ofRandom(m_fVel_ymin, m_fVel_ymax);
			vel[2] = ofRandom(m_fVel_zmin, m_fVel_zmax);

			acc = ofVec3f(0);
			nor = ofVec3f(0, 0, 1);
		}
		void addForce(Force* f)
		{
			forces.push_back(f);
		}
		void applyForce(Force* f)
		{
			f->setTarget(target);
			f->update(loc, mass);
			ofVec3f forceVec = f->get();
			forceVec /= mass;
			acc += forceVec;
		}
		void updateForce(int index, Force* f)
		{
			forces.at(index) = NULL;
			forces.at(index) = f;
		}
		void update()
		{
			// Wait for start delay
			if (delay[0] >= delay[1])
			{
				delay[0] = delay[1];
				if (life[0] > life[1]) reset();
				if (loc[0] < -ofGetWidth() * 0.5) reset();

				bool varforce = acc.x != 0 && acc.y != 0 && acc.z != 0;
				life[0] += 0.1;

				// Add constant forces
				for (std::vector<Force*>::iterator it = forces.begin(); it != forces.end(); ++it)
				{
					(*it)->setTarget(target);
					(*it)->update(ofVec3f(loc.x, loc.y, loc.z), mass);
					acc += (*it)->get();
				}

				acc /= mass;
				vel += acc;

				// Only limit if a variable force is not present
				vel.limit(m_nVel_max);

				loc += vel;
				acc *= 0.0;
			}
			else delay[0] += 0.1;
		}
		void setRedRange(float min, float max) {m_fRmin = min; m_fRmax = max;}
		void setGreenRange(float min, float max) {m_fGmin = min; m_fGmax = max;}
		void setBlueRange(float min, float max) {m_fBmin = min; m_fBmax = max;}
		void setAlphaRange(float min, float max) {m_fAmin = min; m_fAmax = max;}

		void setTarget(ofVec2f t){target = t;}
		void setTarget(ofVec3f t){target = t;}

		float mass;			// Particle mass
		float size;			// Particle size
		float lerp[2];		// Linear and Colour interpolation values
		float life[2];		// Life span start + end
		float delay[2];		// Delay start + end boundary to wait for
		float alpha[2];		// Alpha value at start + end
		float m_time;		// Generic timer from main app

		ofFloatColor col;
		ofVec3f loc, pos, nor, vel, acc, friction;
	};
}