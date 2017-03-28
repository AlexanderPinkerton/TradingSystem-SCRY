cmake_minimum_required(VERSION 3.6)
project(TradingSystem)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed. [For Qt]
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)

#----------------Prepare and Load Dependencies--------------------------------
#My PoloniexAPIWrapper
set(poloniex_api_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/PoloniexAPI)
add_subdirectory(PoloniexAPI)

#Check if QtCmakePath environment variable is set before proceeding.
if(EXISTS "$ENV{QtCmakePath}")
    #Change the windows path separators to cmake ones
    file(TO_CMAKE_PATH "$ENV{QtCmakePath}" QtCmakePath)
else()
    #message(FATAL_ERROR "Could not find QtCmakePath environment variable")
endif(EXISTS "$ENV{QtCmakePath}")


# Find the Qt Modules
find_package(Qt5 COMPONENTS Core Network Gui Widgets Charts REQUIRED )

#Set the Source and Header directory variables.
set (MyProjectLib_src ${PROJECT_SOURCE_DIR}/cpp/*.cpp)
set (MyProjectLib_hdr ${PROJECT_SOURCE_DIR}/hpp/*.h)

file(GLOB SOURCE_FILES "./cpp/*.cpp")
file(GLOB HEADER_FILES "./hpp/*.hpp" "./hpp/*.h")

#Explicitly tell Qt to moc the headers.
qt5_wrap_cpp(MyProjectLib_hdr_moc ${HEADER_FILES})

#Specify the directories to include files from.
include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})
include_directories (${poloniex_api_include_dir})

add_library (MyProjectLib STATIC
        ${SOURCE_FILES}
        ${MyProjectLib_hdr_moc}
        )


# Tell Cmake what user files to include in the build process.
#file(GLOB SOURCE_FILES "./cpp/*.cpp" "./hpp/*.hpp")

add_executable(TradingSystem ${SOURCE_FILES})


#------------------Attach Dependencies to Executable-----------------------

target_link_libraries (MyProjectLib
        Qt5::Widgets
        Qt5::Core
        Qt5::Network
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts)

# Link Dependencies.
# Specify which QT modules to add to the executable.
target_link_libraries(TradingSystem
        MyProjectLib
        PoloniexAPI)

#Specify dependencies to ensure they are built first.
add_dependencies(TradingSystem PoloniexAPI MyProjectLib)



message(status "** Cmake Prefix Path: ${CMAKE_PREFIX_PATH}")
message(status "** Source Files: ${SOURCE_FILES}")
message(status "** ${PROJECT_SOURCE_DIR}")
