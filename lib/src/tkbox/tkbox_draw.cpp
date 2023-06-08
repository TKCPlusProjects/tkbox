#include <tkbox/tkbox_draw.hpp>

namespace tkht {
namespace tkbox {
Drawer::Drawer() {
  camera = make_shared<Camera>(25.0f);
  point = make_shared<RendererPoint>(camera, 0.0f);
  line = make_shared<RendererLine>(camera, 0.1f);
  triangle = make_shared<RendererTriangle>(camera, 0.2f);

  uint32 flags = 0;
  flags += b2Draw::e_shapeBit;
  flags += b2Draw::e_jointBit;
  flags += b2Draw::e_aabbBit;
  flags += b2Draw::e_centerOfMassBit;
  SetFlags(flags);
}

void Drawer::DrawPolygon(const b2Vec2 *vertix_lst, int32 count,
                         const b2Color &color) {
  b2Vec2 p1 = vertix_lst[count - 1];
  for (int32 i = 0; i < count; ++i) {
    b2Vec2 p2 = vertix_lst[i];
    line->Push((Point*)&p1, (Color*)&color);
    line->Push((Point*)&p2, (Color*)&color);
    p1 = p2;
  }
}
void Drawer::DrawSolidPolygon(const b2Vec2 *vertix_lst, int32 count,
                              const b2Color &color) {
  b2Color fillColor(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);

  for (int32 i = 1; i < count - 1; ++i) {
    triangle->Push((Point*)&vertix_lst[0], (Color*)&fillColor);
    triangle->Push((Point*)&vertix_lst[i], (Color*)&fillColor);
    triangle->Push((Point*)&vertix_lst[i + 1], (Color*)&fillColor);
  }

  DrawPolygon(vertix_lst, count, color);
}
void Drawer::DrawCircle(const b2Vec2 &center, float radius,
                        const b2Color &color) {
  b2Vec2 r1(1.0f, 0.0f);
  b2Vec2 v1 = center + radius * r1;
  for (int32 i = 0; i < kCircleSegments; ++i) {
    b2Vec2 r2;
    r2.x = kCosInc * r1.x - kSinInc * r1.y;
    r2.y = kSinInc * r1.x + kCosInc * r1.y;
    b2Vec2 v2 = center + radius * r2;
    line->Push((Point*)&v1, (Color*)&color);
    line->Push((Point*)&v2, (Color*)&color);
    r1 = r2;
    v1 = v2;
  }
}
void Drawer::DrawSolidCircle(const b2Vec2 &center, float radius,
                             const b2Vec2 &axis, const b2Color &color) {
  b2Vec2 v0 = center;
  b2Vec2 r1(kCosInc, kSinInc);
  b2Vec2 v1 = center + radius * r1;
  b2Color fillColor(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
  for (int32 i = 0; i < kCircleSegments; ++i) {
    b2Vec2 r2;
    r2.x = kCosInc * r1.x - kSinInc * r1.y;
    r2.y = kSinInc * r1.x + kCosInc * r1.y;
    b2Vec2 v2 = center + radius * r2;
    triangle->Push((Point*)&v0, (Color*)&fillColor);
    triangle->Push((Point*)&v1, (Color*)&fillColor);
    triangle->Push((Point*)&v2, (Color*)&fillColor);
    r1 = r2;
    v1 = v2;
  }

  b2Vec2 p = center + radius * axis;
  line->Push((Point*)&center, (Color*)&color);
  line->Push((Point*)&p, (Color*)&color);

  DrawCircle(center, radius, color);
}
void Drawer::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                         const b2Color &color) {
  line->Push((Point*)&p1, (Color*)&color);
  line->Push((Point*)&p2, (Color*)&color);
}
void Drawer::DrawTransform(const b2Transform &xf) {
  b2Color red(1.0f, 0.0f, 0.0f);
  b2Color green(0.0f, 1.0f, 0.0f);
  b2Vec2 p1 = xf.p, p2;

  line->Push((Point*)&p1, (Color*)&red);
  p2 = p1 + kAxisScale * xf.q.GetXAxis();
  line->Push((Point*)&p2, (Color*)&red);

  line->Push((Point*)&p1, (Color*)&green);
  p2 = p1 + kAxisScale * xf.q.GetYAxis();
  line->Push((Point*)&p2, (Color*)&green);
}
void Drawer::DrawPoint(const b2Vec2 &p, float size, const b2Color &color) {
  point->Push(size, (Point*)&p, (Color*)&color);
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
void Drawer::DrawString(const b2Vec2 &pos, const char *string, ...) {
  if (!Debug)
    return;

  float x, y;
  camera->ConvertWorldToScreen(&x, &y, pos.x, pos.y);

  va_list arg;
  va_start(arg, string);
  ImGui::Begin("Overlay", NULL,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs |
                   ImGuiWindowFlags_AlwaysAutoResize |
                   ImGuiWindowFlags_NoScrollbar);
  ImGui::SetCursorPos(ImVec2(x, y));
  ImGui::TextColoredV(ImColor(230, 153, 153, 255), string, arg);
  ImGui::End();
  va_end(arg);
}
void Drawer::DrawAABB(b2AABB *aabb, const b2Color &color) {
  b2Vec2 p1 = aabb->lowerBound;
  b2Vec2 p2 = b2Vec2(aabb->upperBound.x, aabb->lowerBound.y);
  b2Vec2 p3 = aabb->upperBound;
  b2Vec2 p4 = b2Vec2(aabb->lowerBound.x, aabb->upperBound.y);

  line->Push((Point*)&p1, (Color*)&color);
  line->Push((Point*)&p2, (Color*)&color);

  line->Push((Point*)&p2, (Color*)&color);
  line->Push((Point*)&p3, (Color*)&color);

  line->Push((Point*)&p3, (Color*)&color);
  line->Push((Point*)&p4, (Color*)&color);

  line->Push((Point*)&p4, (Color*)&color);
  line->Push((Point*)&p1, (Color*)&color);
}

void Drawer::Flush() {
  point->Flush();
  line->Flush();
  triangle->Flush();
}
} // namespace tkbox
} // namespace tkht
