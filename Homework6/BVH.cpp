#include <algorithm>
#include <cassert>
#include "BVH.hpp"

BVHAccel::BVHAccel(std::vector<Object*> p, int maxPrimsInNode,
                   SplitMethod splitMethod)
    : maxPrimsInNode(std::min(255, maxPrimsInNode)), splitMethod(splitMethod),
      primitives(std::move(p))
{
    time_t start, stop;
    time(&start);
    if (primitives.empty())
        return;

    root = recursiveBuild(primitives);

    time(&stop);
    double diff = difftime(stop, start);
    int hrs = (int)diff / 3600;
    int mins = ((int)diff / 60) - (hrs * 60);
    int secs = (int)diff - (hrs * 3600) - (mins * 60);

    printf(
        "\rBVH Generation complete: \nTime Taken: %i hrs, %i mins, %i secs\n\n",
        hrs, mins, secs);
}

BVHBuildNode* BVHAccel::recursiveBuild(std::vector<Object*> objects)
{
    BVHBuildNode* node = new BVHBuildNode();

    // Compute bounds of all primitives in BVH node
    Bounds3 bounds;
    for (int i = 0; i < objects.size(); ++i)
        bounds = Union(bounds, objects[i]->getBounds());
    if (objects.size() == 1) {
        // Create leaf _BVHBuildNode_
        node->bounds = objects[0]->getBounds();
        node->object = objects[0];
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }
    else if (objects.size() == 2) {
        node->left = recursiveBuild(std::vector{objects[0]});
        node->right = recursiveBuild(std::vector{objects[1]});

        node->bounds = Union(node->left->bounds, node->right->bounds);
        return node;
    }
    else {
        std::vector<Object*> leftshapes, rightshapes;
        switch (this->splitMethod) {
            case SplitMethod::NAIVE:
                NAIVEsplitFuction(objects, leftshapes, rightshapes);
                break;
            case SplitMethod::SAH:
                SAHsplitFuction(objects, leftshapes, rightshapes);
                break;
            default:
                throw std::runtime_error("BVHAccel::recursiveBuild not know splitMethod.");
                break;
        }

        node->left = recursiveBuild(leftshapes);
        node->right = recursiveBuild(rightshapes);

        node->bounds = Union(node->left->bounds, node->right->bounds);
    }

    return node;
}

void BVHAccel::NAIVEsplitFuction(std::vector<Object *> &objects, std::vector<Object *> &leftshapes, std::vector<Object *> &rightshapes)
{
    Bounds3 centroidBounds;
    for (int i = 0; i < objects.size(); ++i)
        centroidBounds =
            Union(centroidBounds, objects[i]->getBounds().Centroid());
    int dim = centroidBounds.maxExtent();
    switch (dim) {
    case 0:
        // sort objects by x position
        std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
            return f1->getBounds().Centroid().x <
                    f2->getBounds().Centroid().x;
        });
        break;
    case 1:
        // sort objects by y position
        std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
            return f1->getBounds().Centroid().y <
                    f2->getBounds().Centroid().y;
        });
        break;
    case 2:
        // sort objects by z position
        std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
            return f1->getBounds().Centroid().z <
                    f2->getBounds().Centroid().z;
        });
        break;
    }

    auto beginning = objects.begin();
    auto middling = objects.begin() + (objects.size() / 2);
    auto ending = objects.end();

    leftshapes = std::vector<Object*>(beginning, middling);
    rightshapes = std::vector<Object*>(middling, ending);

    assert(objects.size() == (leftshapes.size() + rightshapes.size()));
}

void BVHAccel::SAHsplitFuction(std::vector<Object *> &objects, std::vector<Object *> &leftshapes, std::vector<Object *> &rightshapes)
{
    Bounds3 centroidBounds;
    for (int i = 0; i < objects.size(); ++i)
        centroidBounds =
            Union(centroidBounds, objects[i]->getBounds().Centroid());
    int dim = centroidBounds.maxExtent();
    switch (dim) {
    case 0:
        // sort objects by x position
        std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
            return f1->getBounds().Centroid().x <
                    f2->getBounds().Centroid().x;
        });
        break;
    case 1:
        // sort objects by y position
        std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
            return f1->getBounds().Centroid().y <
                    f2->getBounds().Centroid().y;
        });
        break;
    case 2:
        // sort objects by z position
        std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
            return f1->getBounds().Centroid().z <
                    f2->getBounds().Centroid().z;
        });
        break;
    }

    Bounds3 frontSumBounds[objects.size()], backSumBounds[objects.size()];
    frontSumBounds[0] = objects[0]->getBounds().Centroid();
    for(int i = 1; i < objects.size(); i++) {
        frontSumBounds[i] = Union(frontSumBounds[i - 1], objects[i]->getBounds().Centroid());
    }
    backSumBounds[objects.size() - 1] = objects[objects.size() - 1]->getBounds().Centroid();
    for (int i = objects.size() - 2; i >= 0; i--) {
        backSumBounds[i] = Union(backSumBounds[i + 1], objects[i]->getBounds().Centroid());
    }
    std::vector<double> time_svh;
    for (int i = 0; i < objects.size(); i++) {
        double time = ( frontSumBounds[i].SurfaceArea() / centroidBounds.SurfaceArea() * (i + 1))
                    + ( backSumBounds[i].SurfaceArea() / centroidBounds.SurfaceArea() * (objects.size() - i));
        time_svh.push_back(time);
    }
    int i_vector_min_itr = std::min_element( time_svh.begin(), time_svh.end()) - time_svh.begin() ;

    auto beginning = objects.begin();
    auto middling = objects.begin()  + i_vector_min_itr + 1;
    auto ending = objects.end();

    leftshapes = std::vector<Object*>(beginning, middling);
    rightshapes = std::vector<Object*>(middling, ending);

    assert(objects.size() == (leftshapes.size() + rightshapes.size()));
}

Intersection BVHAccel::Intersect(const Ray& ray) const
{
    Intersection isect;
    if (!root)
        return isect;
    isect = BVHAccel::getIntersection(root, ray);
    return isect;
}

Intersection BVHAccel::getIntersection(BVHBuildNode* node, const Ray& ray) const
{
    // If the node's bounds don't intersect with the ray, return empty intersection
    if (!node->bounds.IntersectP(ray))
        return Intersection();
    // If we're at a leaf node, return the intersection with the contained object
    else if (node->left == nullptr && node->right == nullptr)
        return node->object->getIntersection(ray);
    // Otherwise, recurse on both children
    else {
        Intersection left = getIntersection(node->left, ray);
        Intersection right = getIntersection(node->right, ray);
        // Return the closest intersection
        if (left.distance < right.distance)
            return left;
        else
            return right;
    }
}