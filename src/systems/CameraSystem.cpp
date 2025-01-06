/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : CameraSystem
 * @created     : Sunday Jan 05, 2025 18:39:22 CET
 */

#include "Systems.hpp"
#include "render/Shader.hpp"

#define WIDTH 800
#define HEIGHT 600

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

void CameraSystem::init(std::vector<Entity> entities, void* args) {
    if (entities.empty()) return;

    Camera* camera = ECS::get_component<Camera>(entities[0]);
    Transform* transform = ECS::get_component<Transform>(entities[0]);

    if (!camera || !transform) return;

    GLuint shader_program = Shader::program_id;
    glUseProgram(shader_program);

    glm::mat4 projection;
    create_projection_matrix(WIDTH, HEIGHT, projection);
    GLint projection_loc = glGetUniformLocation(shader_program, "projection");
    glUniformMatrix4fv(projection_loc, 1, GL_FALSE, &projection[0][0]);

    glm::mat4 view;
    create_view_matrix(10, view, transform);
    GLint view_loc = glGetUniformLocation(shader_program, "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view[0][0]);
}

void CameraSystem::update_camera(std::vector<Entity> entities, void* args) {
    if (entities.empty()) return;

    Transform* transform = ECS::get_component<Transform>(entities[0]);
    if (!transform) return;

    GLuint shader_program = Shader::program_id;
    glUseProgram(shader_program);

    glm::mat4 view;
    create_view_matrix(10, view, transform);
    GLint view_loc = glGetUniformLocation(shader_program, "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view[0][0]);
}

void CameraSystem::create_projection_matrix(float screen_width, float screen_height, glm::mat4& proj_matrix) {
    proj_matrix = glm::mat4(1.0f);

    float aspect_ratio = screen_width / screen_height;

    if (aspect_ratio > 1.0f) {
        proj_matrix[0][0] = 1.0f / aspect_ratio;
    } else {
        proj_matrix[1][1] = aspect_ratio;
    }
}

void CameraSystem::create_view_matrix(int tile_count_ver, glm::mat4& view_matrix, Transform* transform) {
    view_matrix = glm::mat4(1.0f);

    view_matrix[0][0] = 2.0f / tile_count_ver;
    view_matrix[1][1] = 2.0f / tile_count_ver;

    glm::vec3 pos(-transform->x, -transform->y, -transform->z);
    view_matrix = glm::translate(view_matrix, pos);
}


