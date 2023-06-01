#include <tkbox/tkbox_graphic.hpp>

namespace tkht {
namespace tkbox {
void Graphic::Write() {
  ofstream file(path, ios::binary);
  if (!file.is_open()) {
    Err("读取资源文件失败"); return;
  }

  int count = vertexes.size();
  file.write((char*)&count, sizeof(int));
  for (size_t i = 0; i < count; i++) {
    b2Vec2 vertex = vertexes[i];
    file.write((char*)&vertex.x, sizeof(float));
    file.write((char*)&vertex.y, sizeof(float));
  }
  file.write((char*)&color.r, sizeof(float));
  file.write((char*)&color.g, sizeof(float));
  file.write((char*)&color.b, sizeof(float));
  file.write((char*)&color.a, sizeof(float));
  file.close();
}

void Graphic::Read() {
  ifstream file(path, ios::binary);
  if (!file.is_open()) {
    Err("读取资源文件失败"); return;
  }

  int count;
  file.read((char*)&count, sizeof(int));
  vertexes.clear();
  for (size_t i = 0; i < count; i++) {
      b2Vec2 vertex;
      file.read((char*)&vertex.x, sizeof(float));
      file.read((char*)&vertex.y, sizeof(float));
      vertexes.push_back(vertex);
  }
  file.read((char*)&color.r, sizeof(float));
  file.read((char*)&color.g, sizeof(float));
  file.read((char*)&color.b, sizeof(float));
  file.read((char*)&color.a, sizeof(float));
  file.close();
}
} // namespace tkbox
} // namespace tkht
