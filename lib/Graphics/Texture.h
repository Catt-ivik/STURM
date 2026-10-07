// +++ Texture class for the program STURM +++
//
// Functions for loading an image as an OpenGL texture
// using the open source library stb.
// Thanks to this library, this class provides also methods
// for getting texture's width and height.
//
// In future developement i count on creating a
// Texture::Load function (or something similar)
// for changing the texture at runtime for eventual
// needs.

#ifndef STURM_TEXTURE
#define STURM_TEXTURE

class Texture
{
public:

    Texture();
    Texture(const char* filePath);
    ~Texture();

    const int GetWidth();
    const int GetHeight();
    const unsigned int GetID();

    void Bind();

private:

    unsigned int ID;
    int width, height, nrChannels;

};

#endif // STURM_TEXTURE