#include <tkbox/tkbox_render_line.hpp>

namespace tkht {
namespace tkbox {
RenderLine::RenderLine(shared_ptr<Camera> camera, GLfloat depth)
    : tkbox::Renderer(camera, depth, 2) {}

void RenderLine::GLFlush() { glDrawArrays(GL_LINES, 0, shader->count); }
} // namespace tkbox
} // namespace tkht
