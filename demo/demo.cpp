#include <tkbox/tkbox.hpp>

int main() 
{
  if (!glfwInit()) {
    Assert(false, "GLFW Init Failed");
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  float width = 1080.0f;
  float height = 720.0f;
  
  GLFWwindow* window = glfwCreateWindow(width, height, "Demo", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    Assert(false, "GLFW Create window Failed");
    return -1;
  }

  glfwMakeContextCurrent(window);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glewExperimental = GL_TRUE;
  glewInit();

  shared_ptr<tkgl::Camera> camera_graphic = make_shared<tkgl::Camera>(25.0f);
  camera_graphic->SetSize(width, height);
  shared_ptr<tkbox::Drawer> drawer_graphic = make_shared<tkbox::Drawer>(camera_graphic, 0.0f);

  Graphic graphic;
  graphic.path = strdup("a1.tkgp");
  if (filesystem::exists(graphic.path)) {
    graphic.Read();
  } else {
    graphic.color = Color(0.0f, 1.0f, 0.0f, 1.0f);
    graphic.shapes.push_back(make_shared<ShapeSegment>(vector<Point>{
      Point( 0.0f, -2.0f),
      Point( 0.0f,  2.0f),
      Point(-2.0f,  0.0f),
      Point( 2.0f,  0.0f),
    }));
    graphic.shapes.push_back(make_shared<ShapeSegment>(vector<Point>{
      Point(-2.0f,  0.0f),
      Point( 0.0f,  2.0f),
      Point( 2.0f,  0.0f),
    }, true));
    graphic.shapes.push_back(make_shared<ShapePolygon>(vector<Point>{
      Point( 0,  3.0f),
      Point( 1.0f,  2.0f),
      Point( 2.0f,  0.0f),
      Point( 2.0f,  1.0f),
      Point( 3.0f,  0),
      Point( 3.0f, -3.0f),
      Point( 2.0f, -1.0f),
      Point( 1.0f, -2.0f),
      Point( 1.0f, -3.0f),
      Point( 0.0f, -2.0f),
      Point(-1.0f, -3.0f),
      Point(-1.0f, -2.0f),
      Point(-2.0f, -1.0f),
      Point(-3.0f, -3.0f),
      Point(-3.0f,  0),
      Point(-2.0f,  1.0f),
      Point(-2.0f,  0.0f),
      Point(-1.0f,  2.0f),
    }));
    graphic.Write();
  }

  shared_ptr<tkgl::Camera> camera = make_shared<tkgl::Camera>(25.0f);
  camera->SetSize(width, height);
  shared_ptr<tkbox::Drawer> drawer = make_shared<tkbox::Drawer>(camera, 0.0f);

  shared_ptr<b2World> world = make_shared<b2World>(b2Vec2(0.0f, 0.0f));
  world->SetSubStepping(true);
  world->SetDebugDraw(drawer.get());

  vector<b2Vec2> vectors = {
    b2Vec2( 0,  5.0f),
    b2Vec2(-0.87f*5.0f,  0.5f*5.0f),
    b2Vec2(-0.87f*5.0f, -0.5f*5.0f),
    b2Vec2( 0, -5.0f),
    b2Vec2( 0.87f*5.0f, -0.5f*5.0f),
    b2Vec2( 0.87f*5.0f,  0.5f*5.0f),
  };
  b2PolygonShape shape;                  // 创建多边形形状
  shape.Set(&vectors[0], vectors.size());
  
  b2FixtureDef fd;                       // 创建夹具定义对象
  fd.shape = &shape;                     // 设置夹具形状
  fd.density = 1.0f;                     // 设置密度
  fd.friction = 0.3f;                    // 设置摩擦系数
  
  b2BodyDef bd;                          // 创建刚体定义对象
  bd.position.Set(0, 0.0f);              // 设置初始位置
  bd.type = b2_dynamicBody;              // 设置为动态刚体
  // bd.angle = 0.5f * b2_pi;
  bd.userData.pointer = reinterpret_cast<uintptr_t>(&graphic);

  b2Body *body = world->CreateBody(&bd);
  body->CreateFixture(&fd);
  body->SetLinearVelocity(b2Vec2(1.0f, 0.0f));

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);

    world->Step(1.0f / 60.0f, 10, 8);
    world->DebugDraw();
    drawer->Flush();

    Graphic* graphic = reinterpret_cast<Graphic*>(body->GetUserData().pointer);
    drawer_graphic->DrawGraphic(graphic, (Transform*)&body->GetTransform());
    drawer_graphic->Flush();

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 1;
}