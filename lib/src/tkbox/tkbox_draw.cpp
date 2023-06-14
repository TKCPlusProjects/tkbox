#include <tkbox/tkbox_draw.hpp>

namespace tkht {
namespace tkbox {
Drawer::Drawer(shared_ptr<Camera> camera, float depth) : tkgl::Drawer(camera, depth) {
  uint32 flags = 0;
  flags += b2Draw::e_shapeBit;
  flags += b2Draw::e_jointBit;
  flags += b2Draw::e_aabbBit;
  flags += b2Draw::e_centerOfMassBit;
  SetFlags(flags);
}

void Drawer::DrawPoint(const b2Vec2 &p, float size, const b2Color &color) {
  tkgl::Drawer::DrawPoint(size, (Point*)&p, 1, (Color*)&color);
}
void Drawer::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {
  b2Vec2 p[2] = {p1, p2};
  tkgl::Drawer::DrawSegment((Point*)p, 2, (Color*)&color);
}
void Drawer::DrawTransform(const b2Transform &xf) {
  DrawSegment(xf.p, xf.p + kAxisScale * xf.q.GetXAxis(), b2Color(1.0f, 0.0f, 0.0f));
  DrawSegment(xf.p, xf.p + kAxisScale * xf.q.GetYAxis(), b2Color(0.0f, 1.0f, 0.0f));
}
void Drawer::DrawPolygon(const b2Vec2 *vertices, int32 count, const b2Color &color) {
  tkgl::Drawer::DrawPolygon((Point*)vertices, count, (Color*)&color);
}
void Drawer::DrawSolidPolygon(const b2Vec2 *vertices, int32 count, const b2Color &color) {
  tkgl::Drawer::DrawSolidPolygon((Point*)vertices, count, (Color*)&color);
}
void Drawer::DrawCircle(const b2Vec2 &center, float radius, const b2Color &color) {
  tkgl::Drawer::DrawCircle((Point*)&center, radius, (Color*)&color);
}
void Drawer::DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color) {
  b2Color fillColor(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
  tkgl::Drawer::DrawSolidCircle((Point*)&center, radius, (Point*)&axis, (Color*)&fillColor);

  DrawSegment(center, center + radius * axis, color);
}

void Drawer::DrawAABB(b2AABB *aabb, const b2Color &color) {
  b2Vec2 vertices[4] = {
    aabb->lowerBound,
    b2Vec2(aabb->upperBound.x, aabb->lowerBound.y),
    aabb->upperBound,
    b2Vec2(aabb->lowerBound.x, aabb->upperBound.y),
  };
  DrawPolygon(vertices, 4, color);
}
void Drawer::DrawString(int x, int y, const char *string, ...) {
  if (!Debug)
    return;

  va_list arg;
  va_start(arg, string);
  ImGui::Begin("Overlay", NULL,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs |
                   ImGuiWindowFlags_AlwaysAutoResize |
                   ImGuiWindowFlags_NoScrollbar);
  ImGui::SetCursorPos(ImVec2(float(x), float(y)));
  ImGui::TextColoredV(ImColor(230, 153, 153, 255), string, arg);
  ImGui::End();
  va_end(arg);
}

void Drawer::Flush() {
  point->Flush();
  line->Flush();
  triangle->Flush();
}
} // namespace tkbox
} // namespace tkht
