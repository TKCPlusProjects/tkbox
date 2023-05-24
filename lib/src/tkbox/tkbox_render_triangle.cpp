#include <tkbox/tkbox_render_triangle.hpp>

namespace tkht {
namespace tkbox {
RenderTriangle::RenderTriangle(shared_ptr<Camera> camera, GLfloat depth)
    : tkbox::Renderer(camera, depth, 3) {}

void RenderTriangle::GLFlush() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDrawArrays(GL_TRIANGLES, 0, shader->count);
  glDisable(GL_BLEND);
}
} // namespace tkbox
} // namespace tkht
