# 源文件
set(GODNET_SRC
    ./network/endpoint.cpp
)

# 动态库
add_library(godnet SHARED ${GODNET_SRC})