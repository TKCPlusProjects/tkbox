set(DEMO_NAME demo)

add_executable(${DEMO_NAME} demo.cpp)
target_link_libraries(${DEMO_NAME} ${PROJECT_NAME})

set_target_properties(
    ${DEMO_NAME}
    PROPERTIES 
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)
