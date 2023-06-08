#ifndef tkbox_draw_hpp
#define tkbox_draw_hpp

#include <tkbox/tkbox_base.hpp>

namespace tkht {
namespace tkbox {
static const float kAxisScale = 0.4f;

class Drawer : public b2Draw {
public:
  shared_ptr<Camera> camera;
  shared_ptr<RendererPoint> point;
  shared_ptr<RendererLine> line;
  shared_ptr<RendererTriangle> triangle;

  Drawer();

  void DrawPolygon(const b2Vec2 *vertix_lst, int32 count,
                   const b2Color &color) override;
  void DrawSolidPolygon(const b2Vec2 *vertix_lst, int32 count,
                        const b2Color &color) override;
  void DrawCircle(const b2Vec2 &center, float radius,
                  const b2Color &color) override;
  void DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis,
                       const b2Color &color) override;
  void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                   const b2Color &color) override;
  void DrawTransform(const b2Transform &xf) override;
  void DrawPoint(const b2Vec2 &p, float size, const b2Color &color) override;
  void DrawString(int x, int y, const char *string, ...);
  void DrawString(const b2Vec2 &pos, const char *string, ...);
  void DrawAABB(b2AABB *aabb, const b2Color &color);

  void Flush();
};
} // namespace tkbox
} // namespace tkht

#endif /* tkbox_draw_hpp */
