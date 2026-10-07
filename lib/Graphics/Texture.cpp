#include "Texture.h"

#include <glad/glad.h>
#include "../stb_image.h"

#include <iostream>

Texture::Texture() :
    ID(0),
    width(0),
    height(0),
    nrChannels(0)
{

}

Texture::Texture(const char* filePath) : Texture()
{
    // Generate and bind the texture to this->ID
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    // Setting the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Loading and generating the texture
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "ERROR: failed to load texture from '" << filePath << "'." << std::endl;
    }

    stbi_image_free(data);

    // Now unbinding the texture for other texture (error produces usually black sprites I learned)
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{

}

const int Texture::GetWidth()
{
    return width;
}

const int Texture::GetHeight()
{
    return height;
}

const unsigned int Texture::GetID()
{
    return ID;
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

