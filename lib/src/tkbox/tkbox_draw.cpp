#include <tkbox/tkbox_draw.hpp>

namespace tkht {
namespace tkbox {
Drawer::Drawer() {
  camera = make_shared<Camera>(25.0f);
  point = make_shared<RenderPoint>(camera, 0.0f);
  line = make_shared<RenderLine>(camera, 0.1f);
  triangle = make_shared<RenderTriangle>(camera, 0.2f);

  uint32 flags = 0;
  flags += b2Draw::e_shapeBit;
  flags += b2Draw::e_jointBit;
  flags += b2Draw::e_aabbBit;
  flags += b2Draw::e_centerOfMassBit;
  SetFlags(flags);
}

void Drawer::SetSize(int width, int height) { camera->SetSize(width, height); }

void Drawer::Flush() {
  triangle->Flush();
  line->Flush();
  point->Flush();
}

void Drawer::Draw(b2Body* body, bool has_transform) {
  Graphic* graphic = reinterpret_cast<Graphic*>(body->GetUserData().pointer);

  if (has_transform) {
    Draw(graphic, body->GetTransform());
  } else {
    Draw(graphic);
  }
}

void Drawer::Draw(Graphic* graphic, const b2Transform& transform) {
  vector<b2Vec2> vertexes;
  for (b2Vec2 vertex : graphic->vertexes) {
    vertexes.push_back(b2Mul(transform, vertex));
  }
  DrawPolygon(&vertexes[0], graphic->vertexes.size(), graphic->color);
}

void Drawer::Draw(Graphic* graphic) {
  DrawPolygon(&graphic->vertexes[0], graphic->vertexes.size(), graphic->color);
}

void Drawer::DrawPolygon(const b2Vec2 *vertix_lst, int32 count,
                         const b2Color &color) {
  b2Vec2 p1 = vertix_lst[count - 1];
  for (int32 i = 0; i < count; ++i) {
    b2Vec2 p2 = vertix_lst[i];
    line->Push(p1, color);
    line->Push(p2, color);
    p1 = p2;
  }
}
void Drawer::DrawSolidPolygon(const b2Vec2 *vertix_lst, int32 count,
                              const b2Color &color) {
  b2Color fillColor(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);

  for (int32 i = 1; i < count - 1; ++i) {
    triangle->Push(vertix_lst[0], fillColor);
    triangle->Push(vertix_lst[i], fillColor);
    triangle->Push(vertix_lst[i + 1], fillColor);
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
    line->Push(v1, color);
    line->Push(v2, color);
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
    triangle->Push(v0, fillColor);
    triangle->Push(v1, fillColor);
    triangle->Push(v2, fillColor);
    r1 = r2;
    v1 = v2;
  }

  b2Vec2 p = center + radius * axis;
  line->Push(center, color);
  line->Push(p, color);

  DrawCircle(center, radius, color);
}
void Drawer::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                         const b2Color &color) {
  line->Push(p1, color);
  line->Push(p2, color);
}
void Drawer::DrawTransform(const b2Transform &xf) {
  b2Color red(1.0f, 0.0f, 0.0f);
  b2Color green(0.0f, 1.0f, 0.0f);
  b2Vec2 p1 = xf.p, p2;

  line->Push(p1, red);
  p2 = p1 + kAxisScale * xf.q.GetXAxis();
  line->Push(p2, red);

  line->Push(p1, green);
  p2 = p1 + kAxisScale * xf.q.GetYAxis();
  line->Push(p2, green);
}
void Drawer::DrawPoint(const b2Vec2 &p, float size, const b2Color &color) {
  point->Push(size, p, color);
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

  line->Push(p1, color);
  line->Push(p2, color);

  line->Push(p2, color);
  line->Push(p3, color);

  line->Push(p3, color);
  line->Push(p4, color);

  line->Push(p4, color);
  line->Push(p1, color);
}
} // namespace tkbox
} // namespace tkht
