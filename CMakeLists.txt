cmake_minimum_required(VERSION 4.0)
project(NKEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(NKEngine main.cpp
        NKEngine.cpp
        NKEngine.h
        NKSprite.cpp
        NKSprite.h
        NKVector2Int.cpp
        NKVector2Int.h
        NKEvent.cpp
        NKEvent.h
        NKEventSubscriber.cpp
        NKEventSubscriber.h
        NKEventDispatcher.cpp
        NKEventDispatcher.h
        MyGameEventSubscriber.cpp
        MyGameEventSubscriber.h
        uuid.h
        NKUuidGenerator.cpp
        NKUuidGenerator.h
        NKSpriteData.h
        NKRenderer.cpp
        NKRenderer.h
        NKEntity.cpp
        NKEntity.h
)
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})