#ifndef tkbox_render_point_hpp
#define tkbox_render_point_hpp

#include <tkbox/tkbox_render.hpp>

namespace tkht {
namespace tkbox {
struct RenderPoint : tkbox::Renderer {
  RenderPoint(shared_ptr<Camera> camera, GLfloat depth);

  void GLFlush() override;
};
} // namespace tkbox
} // namespace tkht

#endif /* tkbox_render_point_hpp */
