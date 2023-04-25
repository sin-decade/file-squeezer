cmake_minimum_required(VERSION 3.18)

project(file-squeezer)

set(QT_MIN_VERSION "5.15.2")
set(KF5_MIN_VERSION "5.78.0")

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
        Core    # QCommandLineParser, QStringLiteral
        Widgets # QApplication
        Svg
        )

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
        CoreAddons      # KAboutData
        I18n            # KLocalizedString
        XmlGui          # KXmlGuiWindow, KActionCollection
        TextWidgets     # KTextEdit
        ConfigWidgets   # KStandardActions
        WidgetsAddons   # KMessageBox
        KIO             # KIO
        )

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(file-squeezer_SRCS src/main.cpp src/mainwindow.cpp
        src/tabs/texttab.cpp src/tabs/digitaltab.cpp src/tabs/settingstab.cpp
        src/widgets/tabsplitter.cpp src/widgets/spoiler.cpp)

add_executable(file-squeezer ${file-squeezer_SRCS})

target_link_libraries(file-squeezer
        Qt5::Widgets
        Qt5::Svg
        KF5::CoreAddons
        KF5::I18n
        KF5::XmlGui
        KF5::TextWidgets
        KF5::ConfigWidgets
        KF5::WidgetsAddons
        KF5::KIOCore
        )

install(TARGETS file-squeezer ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES src/file-squeezerui.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/file-squeezer)