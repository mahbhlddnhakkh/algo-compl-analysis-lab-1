set(target ${Conv_LIBRARY})

file(GLOB hdrs "*.h*" "${Conv_INCLUDE}/*.h*")
file(GLOB srcs "*.c*")

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} ${LIBRARY_DEPS})
