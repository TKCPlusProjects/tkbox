#ifndef tkbox_render_line_hpp
#define tkbox_render_line_hpp

#include <tkbox/tkbox_render.hpp>

namespace tkht {
namespace tkbox {
struct RenderLine : tkbox::Renderer {
  RenderLine(shared_ptr<Camera> camera, GLfloat depth);

  void GLFlush() override;
};
} // namespace tkbox
} // namespace tkht

#endif /* tkbox_render_line_hpp */
