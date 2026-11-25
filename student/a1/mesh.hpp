#pragma once
#include "course.hpp"
using namespace course;
using namespace std;

struct Mesh 
{
    GLuint vao=0,vbo=0,ebo=0;
    GLsizei indexCount=0;
    Mesh()=default;
    Mesh(const Mesh&)=delete; 
    Mesh& operator=(const Mesh&)=delete;
    ~Mesh()
    {
        glDeleteVertexArrays(1,&vao);
        glDeleteBuffers(1,&vbo);
        glDeleteBuffers(1,&ebo);
    }
};

inline std::vector<Vertex> houseVertices()
{
    // TODO A1.1: build wall, roof, door, and window vertices (x,y,r,g,b).
    // Hint: Build CPU positions and colors in std::vector<Vertex>; no OpenGL calls are needed here.
    // In A1, (0, 0) maps to the screen center; x/y are normalized coordinates, not pixels.
    // Build the whole house around local (0, 0), using the center of its outer bounds
    // as the origin: (minX + maxX) / 2 = (minY + maxY) / 2 = 0.
    // A2 rotates/scales about this local origin, then places it at Object::position in TRS mode.
    // Center the whole house, not each roof/wall/door/window separately.
    // The starter roof below is only a drawing check; it is not a centered complete house.

    // TODO A1.1: 벽,지붕,문,창문의 정점을 만들어라 (x,y) 좌표 + (r,g,b) 색값 -> (x,y,r,g,b)
    // C:\Users\AdminStar\Desktop\GraphicsAssignments\docs reference-preview.png참조
    #pragma region Vertex 
    /*struct Vertex
    {
        float x = 0.0f, y = 0.0f;
        float r = 0.0f, g = 0.0f, b = 0.0f;
        float u = 0.0f, v = 0.0f;
    };*/
#pragma endregion

    //0: 좌하단,1 : 우하단,2 : 우상단,3 : 좌상단
    vector<Vertex> walls // 정점 4개
    {
        {-0.4f, -0.4f, 0.9f, 0.7f, 0.4f},
        {0.4f, -0.4f, 0.9f, 0.7f, 0.4f},
        {0.4f, 0.2f, 0.9f, 0.7f, 0.4},
        {-0.4f, 0.2f, 0.9f, 0.7f, 0.4f},
    };

    vector<Vertex> roof // 정점 3개
    {
        {-0.43f, 0.3f, 1.0f, 0.0f, 0.0f},
        {0.43f, 0.3f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.4f, 1.0f, 0.0f, 0.0f},
    };

    vector<Vertex> doors // 정점 4개
    {
        {-0.05f, -0.3f, 0.9f, 0.7f, 0.4f},
        {0.05f, -0.3f, 0.9f, 0.7f, 0.4f},
        {0.05f, 0.05f, 0.9f, 0.7f, 0.4f},
        {-0.05f, 0.05f, 0.9f, 0.7f, 0.4f},
    };

    vector<Vertex> windows // 정점 4개
    {
        //x : 0.25 ~ 0.35 y 0.1 ~ 0.2
        {0.25f, 0.1f , 0.0f, 0.5f, 1.0f},
        {0.35f, 0.1f , 0.0f, 0.5f, 1.0f},
        {0.35f, 0.2f , 0.0f, 0.5f, 1.0f},
        {0.25f, 0.2f , 0.0f, 0.5f, 1.0f},
    };
    
    vector<Vertex> vertices;
    
    vertices.insert(vertices.end(), walls.begin(), walls.end());
    vertices.insert(vertices.end(), roof.begin(), roof.end());
    vertices.insert(vertices.end(), doors.begin(), doors.end());
    vertices.insert(vertices.end(), windows.begin(), windows.end());

    return vertices;
}
inline std::vector<unsigned> houseIndices()
{
    // TODO A1.2: add triangle indices for all four house parts.
    // Hint: Add vertex indices to std::vector<unsigned>, with three indices per triangle.

    //ebo 를 사용하기 위한 정점데이터를 인덱스 순서 지정
    // 0: 좌하단,1 : 우하단,2 : 우상단,3 : 좌상단
    vector<unsigned int> indices{
        0,1,2, 0,2,3, 4,5,6, 7,8,9, 7,9,10, 11,12,13, 11,13,14  
    };
    return indices;
}
inline void createMesh(Mesh& mesh,const std::vector<Vertex>& vertices,const std::vector<unsigned>& indices)
{
    require(mesh.vao==0,"Create each immutable mesh only once");
    if(vertices.empty()||indices.empty())
        return;
    // TODO A1.3: glCreateBuffers + glNamedBufferStorage for VBO/EBO; byte sizes, flags=0.
    // Hint: Use glCreateBuffers(count, names) and glNamedBufferStorage(buffer, byteSize, data, flags). Use size() * sizeof(element type) and data().
    // Create names in mesh.vbo / mesh.ebo and upload the supplied arrays.
    
    //버퍼 사이즈를 직접 계산해야한다. 정점의 각 크기 * 정점들을 담고 있는 벡터의 크기 -> 총 버퍼의 크기, data가 데이터 시작 주소 vertices.data() -> 시작주소 반환
    //flag는 무슨 역할인가 일단 모르니깐 0으로 하고
    glCreateBuffers(1, &mesh.vbo);
    glNamedBufferStorage(mesh.vbo, vertices.size() * sizeof(Vertex), vertices.data(), 0);

    //ebo의 데이터 저장은 unsigned int 값  총 버퍼의 크기는 indices 벡터 사이즈 * unsigned int의 크기
    glCreateBuffers(1, &mesh.ebo);
    glNamedBufferStorage(mesh.ebo, indices.size() * sizeof(unsigned int), indices.data(), 0);

    // TODO A1.4: create VAO, attach VBO to binding 0, attach EBO.
    // Hint: Use glCreateVertexArrays, glVertexArrayVertexBuffer(vao, binding, buffer, offset, stride), and glVertexArrayElementBuffer.
    // Binding index 0; offset 0; stride sizeof(Vertex).
    #pragma region glVertexArrayVertexBuffer 함수
    /*
    * glVertexArrayVertexBuffer( 
        vao,            연결할 VAO
        bindingindex,   VAO 내부의 버퍼 바인딩 인덱스
        buffer,         연결할 VBO
        offset,         버퍼 데이터의 시작 위치
        stride          정점 하나의 크기(바이트)
    );
    */
    #pragma endregion
    
    glCreateVertexArrays(1, &mesh.vao);
    glVertexArrayVertexBuffer(mesh.vao, 0, mesh.vbo, 0, sizeof(Vertex));
    glVertexArrayElementBuffer(mesh.vao, mesh.ebo);
   
    // TODO A1.5: configure position (location 0, 2 floats) and color (location 1, 3 floats).
    // Hint: Use glVertexArrayAttribFormat, glVertexArrayAttribBinding, and glEnableVertexArrayAttrib. Use offsetof(Vertex, x) / offsetof(Vertex, r) for byte offsets.
    // Both attributes use VBO binding index 0. u/v are not enabled yet.
    mesh.indexCount=GLsizei(indices.size());
}
inline void drawMesh(const Mesh& mesh)
{
    if(!mesh.vao)
        return; // Keeps an unfinished starter runnable.
    // TODO A1.6: bind VAO and issue the indexed draw call.
    // Hint: Use glBindVertexArray followed by glDrawElements(mode, count, type, indices), with GL_TRIANGLES, GL_UNSIGNED_INT, and nullptr for the EBO start offset.
    // Count means number of indices, not number of triangles.
}


