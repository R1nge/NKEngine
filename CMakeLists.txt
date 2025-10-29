cmake_minimum_required(VERSION 4.0)
project(NKEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(NKEngine main.cpp
        NKEngine.cpp
        NKEngine.h
        NKReversibleVector2Double.cpp
        NKReversibleVector2Double.h
        Events/NKEvent.cpp
        Events/NKEvent.h
        Events/NKEventSubscriber.cpp
        Events/NKEventSubscriber.h
        Events/NKEventDispatcher.cpp
        Events/NKEventDispatcher.h
        MyGameEventSubscriber.cpp
        MyGameEventSubscriber.h
        uuid.h
        NKUuidGenerator.cpp
        NKUuidGenerator.h
        Systems/NKRenderingSystem.cpp
        Systems/NKRenderingSystem.h
        NKReversibleDouble.cpp
        NKReversibleDouble.h
        Components/NKReversiblePositionComponent.cpp
        Components/NKReversiblePositionComponent.h
        Components/NKComponent.cpp
        Components/NKComponent.h
        Systems/NKTransformSystem.cpp
        Systems/NKTransformSystem.h
        Systems/NKSystem.cpp
        Systems/NKSystem.h
        Components/NKRenderComponent.cpp
        Components/NKRenderComponent.h
        NKWindow.cpp
        NKWindow.h
        NKSpriteCreator.cpp
        NKSpriteCreator.h
        NKSpriteData.cpp
        NKSpriteData.h
        Components/NKInputComponent.cpp
        Components/NKInputComponent.h
        Systems/NKInputSystem.cpp
        Systems/NKInputSystem.h
        Systems/Game/GamePlayerMovementSystem.cpp
        Systems/Game/GamePlayerMovementSystem.h
        Components/Game/GamePlayerTag.cpp
        Components/Game/GamePlayerTag.h
        Systems/Game/GameRewindTriggerSystem.cpp
        Systems/Game/GameRewindTriggerSystem.h
        Components/NKCollisionComponent.cpp
        Components/NKCollisionComponent.h
        Systems/NKCollisionSystem.cpp
        Systems/NKCollisionSystem.h
        Components/NKCollisionTag.cpp
        Components/NKCollisionTag.h
        Systems/NKCollisionTransformSyncSystem.cpp
        Systems/NKCollisionTransformSyncSystem.h
        Systems/NKCollisionResetSystem.cpp
        Systems/NKCollisionResetSystem.h
        Systems/Game/GamePrintOnCollision.cpp
        Systems/Game/GamePrintOnCollision.h
        NKGroupType.cpp
        NKGroupType.h
        NKReversibleAction.cpp
        NKReversibleAction.h
        GameTestAction.cpp
        GameTestAction.h
        Components/NKCameraTag.cpp
        Components/NKCameraTag.h
        Systems/Game/GameCameraFollowPlayer.cpp
        Systems/Game/GameCameraFollowPlayer.h
)
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})