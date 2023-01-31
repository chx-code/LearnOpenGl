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

class Model {
private:
    vector<Mesh> meshes;
    string directoryPath;
    static vector<Texture> textures_loaded;

    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         string typeName);
public:
    explicit Model(const char *path);
    void Draw(Shader shader);
};
