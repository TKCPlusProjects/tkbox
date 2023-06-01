#ifndef tkbox_graphic_hpp
#define tkbox_graphic_hpp

#include <tkbox/tkbox_base.hpp>

namespace tkht {
namespace tkbox {
class Graphic {
public:
  const char* path;
  vector<b2Vec2> vertexes;
  b2Color color;
  
  void Write();
  void Read();
};
} // namespace tkbox
} // namespace tkht

#endif /* tkbox_graphic_hpp */
