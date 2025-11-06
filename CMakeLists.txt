cmake_minimum_required(VERSION 4.0)
project(NKEngine)

set(CMAKE_CXX_STANDARD 23)

function(add_git_dependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG ${gitTag}
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(${libName})
    target_compile_options(${libName} PRIVATE "-w")
endfunction()

INCLUDE(FindPkgConfig)
INCLUDE(FetchContent)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG docking
)

FetchContent_MakeAvailable(imgui)

add_library(imgui)

target_include_directories(imgui
        PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

target_sources(
        imgui
        PUBLIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.cpp

)


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
        Systems/NKTransformRigidBodySyncSystem.cpp
        Systems/NKTransformRigidBodySyncSystem.h
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
        NKCoordinatesConverter.cpp
        Components/NKRigidBodyComponent.cpp
        Components/NKRigidBodyComponent.h
        NKFilter.cpp
        NKFilter.h
        Audio/NKAudioPlayer.cpp
        Audio/NKAudioPlayer.h
        box2cpp.h
)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer >= 2.0.0)

set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)

add_git_dependency(
        box2d
        https://github.com/erincatto/box2d.git
        v3.1.1
)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS} ${box2d_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES} box2d imgui)

add_custom_command(TARGET NKEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:NKEngine>/assets)