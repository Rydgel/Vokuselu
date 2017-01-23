#ifndef VOXELS_TEXTUREMANAGER_HPP
#define VOXELS_TEXTUREMANAGER_HPP

#include <unordered_map>
#include <boost/optional.hpp>
#include "../../vendors/stb_image/stb_image.hpp"
#include "Texture.hpp"


using TextureMap = std::unordered_map<std::string, std::shared_ptr<Texture>>;

class TextureManager
{
private:
    TextureMap m_textures;
public:
    TextureManager();
    // todo add more options maybe?
    void addTexture(const std::string name, const std::string path);
    const boost::optional<std::shared_ptr<Texture>> getTexture(const std::string name);
    ~TextureManager();
};


#endif //VOXELS_TEXTUREMANAGER_HPP
