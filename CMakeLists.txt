cmake_minimum_required(VERSION 3.5)

project(Debate VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(OpenCV_DIR F:/opencv-build)
set(OpenCV_DIR F:/opencv4.8.0/bin)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 COMPONENTS Multimedia REQUIRED)
find_package(Qt6 COMPONENTS MultimediaWidgets REQUIRED)
find_package(OpenCV REQUIRED)

#连接静态库
set(OpenCV_LIB_DIR ${OpenCV_DIR}/lib)
link_libraries(${OpenCV_DIR}/include)
link_libraries(${OpenCV_DIR}/opencv2)

LINK_LIBRARIES(${OpenCV_LIB_DIR}/libopencv_calib3d480.dll.a)
LINK_LIBRARIES(${OpenCV_LIB_DIR}/libopencv_core480.dll.a)
LINK_LIBRARIES(${OpenCV_LIB_DIR}/libopencv_dnn480.dll.a)
LINK_LIBRARIES(${OpenCV_LIB_DIR}/libopencv_features2d480.dll.a)
LINK_LIBRARIES(${OpenCV_LIB_DIR}/libopencv_flann480.dll.a)
LINK_LIBRARIES(${OpenCV_LIB_DIR}/libopencv_gapi480.dll.a)
LINK_LIBRARIES(${OpenCV_LIB_DIR}/libopencv_highgui480.dll.a)
LINK_LIBRARIES(${OpenCV_LIB_DIR}/libopencv_imgcodecs480.dll.a)
LINK_LIBRARIES(${OpenCV_LIB_DIR}/libopencv_imgproc480.dll.a)
LINK_LIBRARIES(${OpenCV_LIB_DIR}/libopencv_ml480.dll.a)
LINK_LIBRARIES(${OpenCV_LIB_DIR}/libopencv_objdetect480.dll.a)
LINK_LIBRARIES(${OpenCV_LIB_DIR}/libopencv_photo480.dll.a)
LINK_LIBRARIES(${OpenCV_LIB_DIR}/libopencv_stitching480.dll.a)
LINK_LIBRARIES(${OpenCV_LIB_DIR}/libopencv_ts480.a)
LINK_LIBRARIES(${OpenCV_LIB_DIR}/libopencv_video480.dll.a)
LINK_LIBRARIES(${OpenCV_LIB_DIR}/libopencv_videoio480.dll.a)

set(PROJECT_SOURCES
    main.cpp
    ckernel.h
    ckernel.cpp
    tttmp.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Debate
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        #camera
        #camera/camera.cpp
        #camera/camera.h

        #mainwindow
        mainwindow/mainwindow.cpp
        mainwindow/mainwindow.h

        #room_main
        Room_main/room_main.h
        Room_main/room_main.cpp

        #ui
        ui//mainwindow.ui
        ui/camera.ui
        ui/room_main.ui


        #pkg
        #json_config
        pkg/thrift_json/thrift_json_config.h
        pkg/thrift_json/thrift_json_config.cpp
        pkg/thrift_json/thrift_json_echo.cpp
        pkg/thrift_json/thrift_json_video.cpp

        #web
        pkg/web/web.cpp
        pkg/web/web.h

        #video
        pkg/Video/videodeal.h
        pkg/Video/videodeal.cpp
        pkg/Video/video_config.h


        #camera
        pkg/Camera/camera.h
        pkg/Camera/camera.cpp

        #audio
        pkg/Audio/audio.h
        pkg/Audio/audio.cpp

        #config
        config.h

        #.pri
        #pri/video.pri

        #ckernel
        ckernel.cpp
        ckernel.h
        pkg/thrift_json/thrift_json_audio.cpp

        #Audio
        pkg/audioread/audioread.h
        pkg/audioread/audioread.cpp
        pkg/audiowrite/audiowrite.h
        pkg/audiowrite/audiowrite.cpp

        #world
        world.h

    )

include_directories( ${OpenCV_INCLUDE_DIRS})



# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Debate APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Debate SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Debate
            ${PROJECT_SOURCES}
        )
    endif()
endif()



target_link_libraries(Debate PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Debate PRIVATE Qt6::Multimedia)
target_link_libraries(Debate PRIVATE Qt6::MultimediaWidgets)
target_link_libraries(Debate PRIVATE ${OpenCV_LIBS})


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Debate)
endif()
set_target_properties(Debate PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Debate
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Debate)
endif()
