#include <iostream>
#include <vector>

#include "CGL/vector2D.h"

#include "mass.h"
#include "rope.h"
#include "spring.h"

namespace CGL {

    Rope::Rope(Vector2D start, Vector2D end, int num_nodes, float node_mass, float k, vector<int> pinned_nodes)
    {
        // TODO (Part 1): Create a rope starting at `start`, ending at `end`, and containing `num_nodes` nodes.
        for (int i = 0; i < num_nodes; i++) {
            Vector2D position = start + (end - start) * (i / (num_nodes - 1.0));
            Mass *mass = new Mass(position, node_mass, false);
            masses.push_back(mass);

            if (i > 0) {
                Spring *spring = new Spring(masses[i - 1], masses[i], k);
                springs.push_back(spring);
            }
        }

    //    Comment-in this part when you implement the constructor
       for (auto &i : pinned_nodes) {
           masses[i]->pinned = true;
       }
    }

    void Rope::simulateEuler(float delta_t, Vector2D gravity)
    {
        for (auto &s : springs)
        {
            // TODO (Part 2): Use Hooke's law to calculate the force on a node
            Vector2D force = -s->k * (s->m1->position - s->m2->position).unit() * ((s->m1->position - s->m2->position).norm() - s->rest_length);
            s->m1->forces += force;
            s->m2->forces += (-force);
        }

        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                // TODO (Part 2): Add the force due to gravity, then compute the new velocity and position
                // m->forces += m->mass * gravity;
                // // m->position = m->position + delta_t * m->velocity;
                // m->velocity = m->velocity + delta_t * m->forces / m->mass;
                // m->position = m->position + delta_t * m->velocity;

                // TODO (Part 2): Add global damping
                m->forces += m->mass * gravity;
                // m->position = m->position + delta_t * m->velocity;
                m->velocity = m->velocity + delta_t * m->forces / m->mass;
                m->velocity = (1 - damping) * m->velocity;
                m->position = m->position + delta_t * m->velocity;
            }

            // Reset all forces on each mass
            m->forces = Vector2D(0, 0);
        }
    }

    void Rope::simulateVerlet(float delta_t, Vector2D gravity)
    {
        for (auto &s : springs)
        {
            // TODO (Part 3): Simulate one timestep of the rope using explicit Verlet （solving constraints)
            Vector2D dis = s->m1->position - s->m2->position;
            float length = dis.norm();
            Vector2D force = -s->k * (length - s->rest_length) * dis.unit();
            s->m1->forces += force;
            s->m2->forces += (-force);
        }

        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                Vector2D temp_position = m->position;
                // TODO (Part 3.1): Set the new position of the rope mass
                m->forces += m->mass * gravity;
                m->position = m->position + (1 - damping) * (m->position - m->last_position) + m->forces / m->mass * delta_t * delta_t;
                m->last_position = temp_position;
                
                // TODO (Part 4): Add global Verlet damping
            }
            
            m->forces = Vector2D(0, 0);
        }
    }
}
