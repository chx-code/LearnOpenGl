//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"


void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray &ray) const
{
    return this->bvh->Intersect(ray);
}

Vector3f Scene::shader(const Ray &ray, const Intersection &p) const
{
    // init L_dir and L_indir
    Vector3f hitPoint = p.coords;
    Vector3f N = p.normal; // normal
    Material *m = p.m;
    Vector3f L_dir(0.0), L_indir(0.0);

    // Uniformly sample the light at x (pdf_light = 1 / A)
    Intersection intersection_light;
    float pdf_light;
    sampleLight(intersection_light, pdf_light);

    // Shoot a ray from p to x
    Vector3f dir_p_x = (intersection_light.coords - hitPoint).normalized();
    Ray ray_p_x(hitPoint + EPSILON * N, dir_p_x);
    // std::cout<<hitPoint.x<<" "<<hitPoint.y<<" "<<hitPoint.z<<std::endl;
    // std::cout<<dir_p_x.x<<" "<<dir_p_x.y<<" "<<dir_p_x.z<<std::endl;
    Intersection intersection_p_x = Scene::intersect(ray_p_x);
    // If the ray is not blocked in the middle
    if(intersection_p_x.happened && intersection_p_x.m->hasEmission()) {
        // std::cout<<1<<std::endl;
        Vector3f NN = intersection_p_x.normal;
        L_dir = intersection_p_x.m->m_emission * m->eval(ray.direction, dir_p_x, N) * dotProduct(dir_p_x, N) * dotProduct(-dir_p_x, NN) / intersection_p_x.distance / pdf_light;
    }

    if(get_random_float() <= RussianRoulette) {
        // Trace a ray r(p, wi)
        // std::cout<<1<<std::endl;
        Vector3f dir_i = m->sample(ray.direction, N).normalized();
        Ray ray_p_diri(hitPoint, dir_i);
        Intersection intersection_p_diri = Scene::intersect(ray_p_diri);
        
        // If ray r hit a non-emitting object at q
        if(intersection_p_diri.happened && !intersection_p_diri.m->hasEmission()) {
            L_indir = shader(ray_p_diri, intersection_p_diri) * m->eval(ray.direction, dir_i, N) * dotProduct(dir_i, N) / m->pdf(ray.direction, dir_i, N) / RussianRoulette;
        }
    }

    return m->getEmission() + L_dir + L_indir;

    // Vector3f wo = -ray.direction;
    // Intersection inter_light;
    // float pdf_light = 0;
    // sampleLight(inter_light, pdf_light);
    
    // Ray ws = Ray(p.coords, (inter_light.coords - p.coords).normalized());
    
    // // check if the light is blocked, how to do it?
    // // cosine use to convert dw to dA
    // Vector3f L_dir = Vector3f(0, 0, 0);

    // float dist = this->intersect(ws).distance;
    // if ((inter_light.coords - p.coords).norm() - dist * dist < 0.0001) {
    //     float cosine = dotProduct(-ws.direction.normalized(), inter_light.normal) / (inter_light.coords - p.coords).norm();
    //     L_dir = inter_light.emit * p.m->eval(-ws.direction, wo, p.normal) * dotProduct(p.normal, -ws.direction.normalized()) * cosine / pdf_light;
    // }

    // Vector3f wi = p.m->sample(wo, p.normal).normalized();
    // Ray wi_ray = Ray(p.coords, wi);
    
    // Vector3f L_indir = Vector3f(0, 0, 0);

    // if (get_random_float() < RussianRoulette) {
    //     if (L_dir.x == 0) {
    //         std::cout << "p.m->eval(wi, wo.direction, p.normal)" << p.m->eval(wi, wo, p.normal) << std::endl;
    //     }
    //     // std::cout << "shader(wi_ray, p)" << shader(wi_ray, p) << std::endl;
    //     // std::cout << "p.m->eval(wi, wo.direction, p.normal)" << p.m->eval(wi, wo.direction, p.normal) << std::endl;
    //     // std::cout << "dotProduct(p.normal, wi.normalized())" << dotProduct(p.normal, wi.normalized()) << std::endl;
    //     // std::cout << "p.m->pdf(wi, wo.direction, p.normal)" << p.m->pdf(wi, wo.direction, p.normal) << std::endl;
    //     L_indir = shader(wi_ray, p) * p.m->eval(-wi, wo, p.normal) * dotProduct(p.normal, -wi.normalized()) / p.m->pdf(-wi, wo, p.normal) / RussianRoulette;
    // }

    // std::cout << "L_dir : " << L_dir << std::endl;
    // std::cout << "L_indir : " << L_indir << std::endl;
    // return L_dir + L_indir;
}

void Scene::sampleLight(Intersection &pos, float &pdf) const
{
    float emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
        }
    }
    float p = get_random_float() * emit_area_sum;
    emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
            if (p <= emit_area_sum){
                objects[k]->Sample(pos, pdf);
                break;
            }
        }
    }
}

bool Scene::trace(
        const Ray &ray,
        const std::vector<Object*> &objects,
        float &tNear, uint32_t &index, Object **hitObject)
{
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }


    return (*hitObject != nullptr);
}

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray &ray, int depth) const
{
    // TO DO Implement Path Tracing Algorithm here
    Intersection inter = this->intersect(ray);

    if (inter.happened)
        return shader(ray, inter);
    else
        return Vector3f(0, 0, 0);
}
