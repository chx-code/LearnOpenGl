/*
 * Created by cuihongxin on 2023/1/30.
 */

#pragma once
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Mesh.h"

using namespace std;
using namespace glm;

struct Transform {
    vec3 position;
    vec3 rotation;
    vec3 scale;
};

class Model {
private:
    vector<Mesh> meshes;
    Transform mTransform = {vec3(0.0f), vec3(0.0f), vec3(1.0f)};

    string directoryPath;
    static vector<Texture> textures_loaded;

    void loadModel(const string& path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         const string& typeName);

public:
    explicit Model(const char *path);
    explicit Model(const Mesh& mesh);
    explicit Model(const vector<Mesh>& meshes);
    void Draw(Shader shader);

    glm::mat4 getModelMatrix() const;

    const vec3 &getPosition() const;
    void setPosition(const vec3 &position);
    const vec3 &getRotation() const;
    void setRotation(const vec3 &rotation);
    const vec3 &getScale() const;
    void setScale(const vec3 &scale);
};
