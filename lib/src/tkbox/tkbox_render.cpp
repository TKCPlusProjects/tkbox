#include <tkbox/tkbox_render.hpp>

namespace tkht {
namespace tkbox {
Renderer::Renderer(shared_ptr<Camera> camera, GLfloat depth,
                   GLint dat_seg_len)
    : tkgl::Renderer(camera, depth, dat_seg_len) {}

void Renderer::Push(const b2Vec2 &vertex, const b2Color &color) {
  Push(1.0f, vertex, color);
}
void Renderer::Push(const float size, const b2Vec2 &vertex,
                    const b2Color &color) {
  tkgl::Renderer::Push(size, vertex.x, vertex.y, color.r, color.g, color.b, color.a);
}
} // namespace tkbox
} // namespace tkht
