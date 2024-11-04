#define GLFW_INCLUDE_GLCOREARB
#include <glfw.h>
#include <stdio.h>

#include <penger.h>

const char *vertex_shader_source = R"(
#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_coords;
layout (location = 2) in vec3 normals;

out vec2 TexCoords;
out vec3 Normal;

uniform float angle;

void main() {
    mat4 rotation_matrix = mat4(
        cos(angle),  0.0, sin(angle), 0.0,
        0.0,         1.0, 0.0,        0.0,
       -sin(angle),  0.0, cos(angle), 0.0,
        0.0,         0.0, 0.0,        1.0
    );

    vec3 rotated_position = (rotation_matrix * vec4(position, 1.0)).xyz;
    vec3 translated_position = rotated_position + vec3(0.0, -0.60, 0.0);
    TexCoords = texture_coords;
    Normal = normals;

    gl_Position = vec4(translated_position, 1.0);
}
)";

const char *fragment_shader_source = R"(
#version 410 core

in vec3 Normal;

out vec4 FragColor;

void main() {
    vec3 color = normalize(Normal) * 0.5 + 0.5;
    FragColor = vec4(color, 1.0);
}
)";

int main(void) {
    glfwInit();

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(800, 800, "Window", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO_vertices;
    glGenBuffers(1, &VBO_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void *)0);

    GLuint VBO_texture_coords;
    glGenBuffers(1, &VBO_texture_coords);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_texture_coords);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coords), texture_coords, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (const void *)0);

    GLuint VBO_normals;
    glGenBuffers(1, &VBO_normals);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void *)0);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glUseProgram(program);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glUniform1f(glGetUniformLocation(program, "angle"), 2 * glfwGetTime());
        glDrawElements(GL_TRIANGLES, sizeof(vertex_indices), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO_vertices);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(program);

    glfwTerminate();
    return 0;
}
