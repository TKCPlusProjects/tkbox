add_library(
  ${PROJECT_NAME} STATIC
  ${PROJECT_BASE_INCLUDE_LIST}
  ${PROJECT_BASE_SRC_LIST}
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_BASE_INCLUDE}>
    $<INSTALL_INTERFACE:include>
)

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)
find_package(tkcore CONFIG REQUIRED)
find_package(tkgl CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
  GLEW::GLEW
  glfw
  imgui::imgui
  box2d::box2d
  tkcore::tkcore
  tkgl::tkgl)