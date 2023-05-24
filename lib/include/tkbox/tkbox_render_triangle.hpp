#ifndef tkbox_render_triangle_hpp
#define tkbox_render_triangle_hpp

#include <tkbox/tkbox_render.hpp>

namespace tkht {
namespace tkbox {
struct RenderTriangle : tkbox::Renderer {
  RenderTriangle(shared_ptr<Camera> camera, GLfloat depth);

  void GLFlush() override;
};
} // namespace tkbox
} // namespace tkht

#endif /* tkbox_render_triangle_hpp */
