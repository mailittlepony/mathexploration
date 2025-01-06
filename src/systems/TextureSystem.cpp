/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : TextureSystem
 * @created     : Sunday Dec 29, 2024 16:57:51 GMT
 */
#include "Systems.hpp"
#include "render/Shader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define TEXTURE_TILE_HOR_COUNT 16

const std::string TextureSystem::path = "./src/render/textures/texture.png";
GLuint TextureSystem::texture_id = 0;
std::pair<glm::vec2, glm::vec2> TextureSystem::texture_uvs[80] = {  };

void TextureSystem::init(std::vector<Entity> entities, void *args)
{
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);  
    int width, height, ncha;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &ncha, 0);
    if (data)
    {
        std::cout << "Load texture : " << path << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    glUseProgram(Shader::program_id);
    glUniform1i(glGetUniformLocation(Shader::program_id, "texture1"), 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    for (int i = 0; i < 80; ++i)
    {
        int x = i % TEXTURE_TILE_HOR_COUNT;
        int y = i / TEXTURE_TILE_HOR_COUNT;

        float umin = (x / (float)TEXTURE_TILE_HOR_COUNT);
        float umax = ((x + 1) / (float)TEXTURE_TILE_HOR_COUNT);

        float vmin = TEXTURE_TILE_HOR_COUNT - ((y + 1) / (float)TEXTURE_TILE_HOR_COUNT);
        float vmax = TEXTURE_TILE_HOR_COUNT - (y / (float)TEXTURE_TILE_HOR_COUNT);

        texture_uvs[i].first = glm::vec2(umin, vmin); 
        texture_uvs[i].second = glm::vec2(umax, vmax); 
    }


    for (Entity const &entity : entities)
    {
        Texture *texture = ECS::get_component<Texture>(entity);

        texture->uvmin = texture_uvs[texture->id].first;
        texture->uvmax = texture_uvs[texture->id].second;
    }
}

TextureSystem::~TextureSystem()
{
}

GLuint TextureSystem::get_texture_id()
{
    return texture_id;
}

