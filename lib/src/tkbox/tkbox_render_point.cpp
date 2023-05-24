#include <tkbox/tkbox_render_point.hpp>

namespace tkht {
namespace tkbox {
RenderPoint::RenderPoint(shared_ptr<Camera> camera, GLfloat depth)
    : tkbox::Renderer(camera, depth, 1) {}

void RenderPoint::GLFlush() {
  glEnable(GL_PROGRAM_POINT_SIZE);
  glDrawArrays(GL_POINTS, 0, shader->count);
  glDisable(GL_PROGRAM_POINT_SIZE);
}
} // namespace tkbox
} // namespace tkht
