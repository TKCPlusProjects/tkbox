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

  shared_ptr<tkbox::Drawer> drawer = make_shared<tkbox::Drawer>();
  drawer->SetSize(width, height);
  
  shared_ptr<b2World> world = make_shared<b2World>(b2Vec2(0.0f, 0.0f));
  world->SetSubStepping(true);
  world->SetDebugDraw(drawer.get());

  int count = 20;
  for (size_t i = 0; i < count; i++)
  {
    b2BodyDef bd;                          // 创建刚体定义对象
    bd.position.Set(-20.0f, 0.0f);         // 设置初始位置
    bd.type = b2_dynamicBody;              // 设置为动态刚体
    b2Body *body = world->CreateBody(&bd); // 创建刚体
    b2PolygonShape shape;                  // 创建多边形形状
    shape.SetAsBox(1.0f, 1.0f);            // 设置形状大小
    b2FixtureDef fd;                       // 创建夹具定义对象
    fd.shape = &shape;                     // 设置夹具形状
    fd.density = 1.0f;                     // 设置密度
    fd.friction = 0.3f;                    // 设置摩擦系数
    body->CreateFixture(&fd);
    body->SetLinearVelocity(b2Vec2(1.0f, 0.0f));
  }

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);

    world->Step(1.0f / 60.0f, 10, 8);
    world->DebugDraw();
    drawer->Flush();

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 1;
}