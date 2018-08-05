#include "resource/texture.h"

#include "renderer/renderer.h"
#include "utils/logging/logger.h"



namespace quasi_game_engine {

   Texture::Texture(unsigned char* pixel_map, int width,
                    int height, Asset asset)
                  : Resource(asset), pixel_map_(pixel_map),
                    width_(width), height_(height) {}


   Texture::~Texture() {}

   void Texture::LoadToGraphics(Renderer* render_manager) {
      render_manager->LoadImage(pixel_map_, width_, height_, true, &texture_id_);
   }


} // namespace quasi_game_engine
