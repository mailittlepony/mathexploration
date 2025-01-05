/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : TextureSystem
 * @created     : Sunday Dec 29, 2024 16:57:51 GMT
 */
#include "Systems.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void TextureSystem::init(std::vector<Entity> entities, void *args)
{
    for (Entity const &entity : entities)
    {
        unsigned int &texture_id = ECS::get_component<Texture>(entity)->texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}

void TextureSystem::load(std::vector<Entity> entities, void *args)
{
    const std::string& texture_path = *static_cast<const std::string*>(args);

    for (Entity const &entity : entities)
    {
        Texture *texture = ECS::get_component<Texture>(entity);

        stbi_set_flip_vertically_on_load(true);  
        unsigned char *data = stbi_load(texture_path.c_str(), &texture->width, &texture->height, &texture->nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
}

    void TextureSystem::draw(std::vector<Entity> entities, void *args)
{    for (Entity const &entity : entities)
    {
        unsigned int &texture_id = ECS::get_component<Texture>(entity)->texture_id;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_id);
    }
}

TextureSystem::~TextureSystem()
{
}

