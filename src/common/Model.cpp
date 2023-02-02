/*
 * Created by cuihongxin on 2023/1/30.
 */

#include "Model.h"
vector<Texture> Model::textures_loaded;

Model::Model(const char *path) {
    loadModel(path);
}

void Model::Draw(Shader shader) {
    for(auto & mesh : meshes)
        mesh.Draw(shader);
}

void Model::loadModel(const string& path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path,
                                             aiProcess_Triangulate |
                                             aiProcess_FlipUVs |
                                             aiProcess_GenNormals |
                                             aiProcess_OptimizeMeshes);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }
    directoryPath = path.substr(0, path.find_last_of('/') + 1);

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    // 处理节点所有的网格（如果有的话）
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // 接下来对它的子节点重复这一过程
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // 处理顶点位置、法线和纹理坐标
        vertex.Position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.Normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        if(mesh->mTextureCoords[0]) // 网格是否有纹理坐标？
            vertex.TexCoords = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        else
            vertex.TexCoords = vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
    }
    // 处理索引
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // 处理材质
    if(mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture> diffuseMaps = loadMaterialTextures(material,
                                                           aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        vector<Texture> specularMaps = loadMaterialTextures(material,
                                                            aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const string& typeName) {
    vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        string texPath = directoryPath + str.C_Str();

        bool skip = false;
        for(const auto & tex : Model::textures_loaded)
        {
            if(tex.getPath() == texPath)
            {
                textures.push_back(tex);
                skip = true;
                break;
            }
        }
        if (!skip) {
            mat->GetTexture(type, i, &str);
            Texture texture = Texture(texPath);
            texture.setType(typeName);

            textures.push_back(texture);
            Model::textures_loaded.push_back(texture);
        }
    }
    return textures;
}

glm::mat4 Model::getModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(mTransform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(mTransform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(mTransform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(model, mTransform.scale);

    model = glm::translate(model, mTransform.position);

    return model;
}

const vec3 &Model::getPosition() const {
    return mTransform.position;
}

void Model::setPosition(const vec3 &position) {
    Model::mTransform.position = position;
}

const vec3 &Model::getRotation() const {
    return mTransform.rotation;
}

void Model::setRotation(const vec3 &rotation) {
    Model::mTransform.rotation = rotation;
}

const vec3 &Model::getScale() const {
    return mTransform.scale;
}

void Model::setScale(const vec3 &scale) {
    Model::mTransform.scale = scale;
}
