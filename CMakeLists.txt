cmake_minimum_required(VERSION 3.16)

project(models VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appmodels
    main.cpp
)

qt_add_qml_module(appmodels
    URI models
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES model/interface_items/template_vector_items.hpp
        SOURCES model/composed_model.hpp
        SOURCES model/template_items/template_vector_items.hpp
        SOURCES domain/animal.hpp
        SOURCES model_factory/animal_model_factory.hpp
        SOURCES view_model/animal_view_model.hpp
        SOURCES models_application.hpp
        SOURCES view_model/factory/view_model_factory.hpp
        SOURCES application/read_file.hpp
        SOURCES data/file_controller.hpp
        RESOURCES
        QML_FILES AnimalView.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appmodels PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appmodels
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appmodels
    PRIVATE Qt6::Quick
)
target_link_libraries(appmodels PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS appmodels
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
