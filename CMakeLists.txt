cmake_minimum_required(VERSION 3.5)

project(DoseCalculation VERSION 0.1 LANGUAGES CXX)

add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        dosecaluculation.cpp
        dosecaluculation.h
        dosecaluculation.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DoseCalculation
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc
        table_data.h table_data.cpp table_data.ui
        savepackage.h savepackage.cpp savepackage.ui
        databaseheader.h
        customer_table.h customer_table.cpp customer_table.ui
        datamanager.h datamanager.cpp
        databaseheader.cpp
        importpackage.h importpackage.cpp importpackage.ui




    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DoseCalculation APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DoseCalculation SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DoseCalculation
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DoseCalculation PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)


if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DoseCalculation)
endif()
set_target_properties(DoseCalculation PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DoseCalculation
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DoseCalculation)
endif()
