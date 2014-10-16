#include "particle.hpp"

namespace wezside
{
	class ParticleSystem
	{
	private:
		ofVbo vbo;
		ofVec2f m_mouse;
		std::vector<ofVec3f> forces;
		std::vector<Particle*> particles;
		std::vector<ofVec3f> particles_loc;
		std::vector<ofFloatColor> particles_col;

		void updateParticles()
		{
			particles_loc.clear();
			particles_col.clear();
			for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
			{
				Particle* p = *it;
				p->update();
				particles_loc.push_back(p->loc);
				particles_col.push_back(p->col);
			}
		}
	public:
		void init()
		{
			reset();
		}
		void reset()
		{
			updateParticles();
			vbo.setVertexData(&particles_loc[0], particles_loc.size(), GL_STATIC_DRAW);
			vbo.setColorData(&particles_col[0], particles_col.size(), GL_STATIC_DRAW);
		}
		void addParticle(Particle* p)
		{
			particles.push_back(p);
		}
		void addForce(Force* f)
		{
			for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
			{
				Particle* p = *it;
				p->addForce(f);
			}
		}
		void applyForce(Force* f)
		{
			for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
			{
				Particle* p = *it;
				p->applyForce(f);
			}			
		}
		void updateForce(int particle_index, int force_index, Force* f)
		{
			Particle* p = particles.at(particle_index);
			p->updateForce(force_index, f);
		}
		void update()
		{
			updateParticles();
			vbo.updateVertexData(&particles_loc[0], particles_loc.size());
			vbo.updateColorData(&particles_col[0], particles_col.size());
		}
		void draw()
		{
			// glEnable(GL_POINT_SMOOTH);
			glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

			int total = (int)particles.size();
			vbo.drawInstanced(GL_POINTS, 0, total, 1);
			
			// glDisable(GL_POINT_SMOOTH);
			glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
		}
		void destroy()
		{
			for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
			{
				delete (*it);
			}
			particles.clear();			
			particles_loc.clear();
			particles_col.clear();
		}
		void setMouseXY(int x, int y) 
		{
			m_mouse = ofVec2f(x, y);
			for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
				(*it)->setTarget(m_mouse);
		}
	};
}