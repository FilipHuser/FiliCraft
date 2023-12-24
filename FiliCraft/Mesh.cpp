//
//  Mesh.cpp
//  FiliCraft
//
//  Created by Filip Huser on 09.12.2023.
//

#include "Mesh.hpp"

struct Vertex
{
    float Position[3];
    float Normal[3];
    float Texture[2];
    float Tangent[3];
};

Mesh::Mesh(std::string path) : vds_type(NaN)
{
    this->indicesCount = 0;
    
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate
        | aiProcess_OptimizeMeshes              // sloučení malých plošek
        | aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodně duplikuje
        | aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
        | aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy

        //aiProcess_GenNormals/ai_Process_GenSmoothNormals - vypocet normal s jemnych prechodem v pripade, ze objekt neobsahuje normaly

    const aiScene* scene = importer.ReadFile(path, importOptions);

    if (scene) { //pokud bylo nacteni uspesne
        printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
        printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);

        for (unsigned int i = 0; i < scene->mNumMaterials; i++)                       //Materials
        {
            const aiMaterial* mat = scene->mMaterials[i];

            aiString name;
            mat->Get(AI_MATKEY_NAME, name);
            printf("Material [%d] name %s\n", i, name.C_Str());

            aiColor4D d;

            glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
            if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
                diffuse = glm::vec4(d.r, d.g, d.b, d.a);

        }

        for (unsigned int i = 0; i < scene->mNumMeshes; i++)                      //Objects
        {
            aiMesh* mesh = scene->mMeshes[i];

            Vertex* pVertices = new Vertex[mesh->mNumVertices];
            std::memset(pVertices, 0, sizeof(Vertex) * mesh->mNumVertices);

            for (unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                if (mesh->HasPositions()){
                    pVertices[i].Position[0] = mesh->mVertices[i].x;
                    pVertices[i].Position[1] = mesh->mVertices[i].y;
                    pVertices[i].Position[2] = mesh->mVertices[i].z;
                }
                if (mesh->HasNormals()){
                    pVertices[i].Normal[0] = mesh->mNormals[i].x;
                    pVertices[i].Normal[1] = mesh->mNormals[i].y;
                    pVertices[i].Normal[2] = mesh->mNormals[i].z;
                }
                if (mesh->HasTextureCoords(0)){
                    pVertices[i].Texture[0] = mesh->mTextureCoords[0][i].x;
                    pVertices[i].Texture[1] = mesh->mTextureCoords[0][i].y;
                }
                if (mesh->HasTangentsAndBitangents()){
                    pVertices[i].Tangent[0] = mesh->mTangents[i].x;
                    pVertices[i].Tangent[1] = mesh->mTangents[i].y;
                    pVertices[i].Tangent[2] = mesh->mTangents[i].z;
                }
            }
            unsigned int* pIndices = nullptr;
            if (mesh->HasFaces()) {

                pIndices = new unsigned int[mesh->mNumFaces * 3];
                for (unsigned int i = 0; i < mesh->mNumFaces; i++){
                    pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
                    pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
                    pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
                }
            }
            
            this->primitiveType = mesh->mPrimitiveTypes;
            
            for(int i{0}; i < mesh->mNumVertices; i++)
            {
                this->vertexData.push_back(0);
            }

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->mNumVertices, pVertices, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
           //tangenta pro normalovou mapu
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(VAO);

            GLuint err = glGetError();
            if (err != GL_NO_ERROR){
                std::cout << "GL ERROR: " << err << std::endl; return;
            } this->indicesCount = mesh->mNumFaces * 3;

            delete[] pVertices;
            delete[] pIndices;
        }
    }
    else {
        printf("Error during parsing mesh from %s : %s \n", path.c_str(), importer.GetErrorString());
    }
    glBindVertexArray(0);
}

Mesh::Mesh(std::vector<float> vertexData , VDS vds_type , GLenum primitiveType) : vertexData(vertexData) , vds_type(vds_type) , primitiveType(primitiveType)
{
    init();
}

void Mesh::init()
{
    create_VBO();
    create_VAO();
    create_EBO();
}

void Mesh::create_VBO()
{
    glGenBuffers(1 , &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER , this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertexData.size() * sizeof(float) , this->vertexData.data() , GL_STATIC_DRAW);
}

void Mesh::create_VAO()
{
    switch (this->vds_type) 
    {
        case xyz:
            
            glGenVertexArrays(1, &this->VAO); // Generate the VAO
            glBindVertexArray(this->VAO); // Bind the VAO

            // Bind the VBO to GL_ARRAY_BUFFER target
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

            // Specify the layout of the vertex data
            // First, the position data (three components)
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

            // Unbind the VBO (not necessary, but good practice)
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            // Unbind the VAO
            glBindVertexArray(0);
            break;
            
        case xyz_nnn:
            glGenVertexArrays(1, &this->VAO); // Generate the VAO
            glBindVertexArray(this->VAO); // Bind the VAO

            // Bind the VBO to GL_ARRAY_BUFFER target
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

            // Specify the layout of the vertex data
            // First, the position data (three components)
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, nullptr);

            // Next, the normal data (three components)
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(float) * 3));

            // Unbind the VBO (not necessary, but good practice)
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            // Unbind the VAO
            glBindVertexArray(0);
            break;
            
        case xyz_nnn_uv:
            glGenVertexArrays(1, &this->VAO); // Generate the VAO
            glBindVertexArray(this->VAO); // Bind the VAO

            // Bind the VBO to GL_ARRAY_BUFFER target
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

            // Specify the layout of the vertex data
            // First, the position data (three components)
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, nullptr);

            // Next, the normal data (three components)
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 3));
            
            // Next, the uv data (two components)
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 6));

            // Unbind the VBO (not necessary, but good practice)
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            // Unbind the VAO
            glBindVertexArray(0);
            break;
    }
}

void Mesh::create_EBO()
{
    
}

void Mesh::render()
{
    if (this->vds_type == NaN) //Assimp
    {
        glBindVertexArray(this->VAO);
        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
        glDrawArrays(this->primitiveType, 0, this->vertexData.size());
        // Unbind the VAO
        glBindVertexArray(0);
        
    } else {
     
        glBindVertexArray(this->VAO);
        glDrawArrays(this->primitiveType, 0, this->vertexData.size());
        // Unbind the VAO
        glBindVertexArray(0);
        
    }
}
