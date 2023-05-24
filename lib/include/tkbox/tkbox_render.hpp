#ifndef tkbox_render_hpp
#define tkbox_render_hpp

#include <tkbox/tkbox_base.hpp>

namespace tkht {
namespace tkbox {
static const float kAxisScale = 0.4f;
static const float kCircleSegments = 16.0f;
static const float kCircleIncrement = 2.0f * b2_pi / kCircleSegments;
static const float kSinInc = sinf(kCircleIncrement);
static const float kCosInc = cosf(kCircleIncrement);

struct Renderer : tkgl::Renderer {
  /// @brief 初始化
  /// @param camera 视野相机
  /// @param depth 渲染深度
  /// @param dat_seg_len 每一个图形的点的个数
  Renderer(shared_ptr<Camera> camera, GLfloat depth, GLint dat_seg_len);

  void Push(const b2Vec2 &vertex, const b2Color &color);
  void Push(const float size, const b2Vec2 &vertex, const b2Color &color);
  ;
};
} // namespace tkbox
} // namespace tkht

#endif /* tkbox_render_hpp */
