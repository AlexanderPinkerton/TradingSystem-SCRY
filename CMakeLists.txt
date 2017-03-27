cmake_minimum_required(VERSION 3.6)
project(TradingSystem)
set(CMAKE_CXX_STANDARD 11)


#----------------Prepare and Load Dependencies--------------------------------
#My PoloniexAPIWrapper
set(poloniex_api_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/PoloniexAPI)
add_subdirectory(PoloniexAPI)

#Check if QtCmakePath environment variable is set before proceeding.
if(EXISTS "$ENV{QtCmakePath}")
    #Change the windows path separators to cmake ones
    file(TO_CMAKE_PATH "$ENV{QtCmakePath}" QtCmakePath)
else()
    message(FATAL_ERROR "Could not find QtCmakePath environment variable")
endif(EXISTS "$ENV{QtCmakePath}")


#set(Qt5Charts_DIR "X:/Libraries/QtSDK-x86_64/5.8/msvc2015_64/lib/cmake/Qt5Charts")
#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QtCmakePath})
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# Find the Qt Modules
find_package(Qt5 COMPONENTS Core Network Gui Widgets Charts REQUIRED )
# Instruct CMake to run moc automatically when needed. [For Qt]
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


# Find the BOOST library
#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "X:/Libraries/boost_1_63_0/boost")
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "X:/Libraries/boost_1_63_0/stage/lib")
#FIND_PACKAGE( Boost 1.63 COMPONENTS system REQUIRED )

#INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
include_directories(${poloniex_api_include_dir})

# Tell Cmake what user files to include in the build process.
file(GLOB SOURCE_FILES "./cpp/*.cpp" "./hpp/*.hpp")

add_executable(TradingSystem ${SOURCE_FILES})


#------------------Attach Dependencies to Executable-----------------------

# Specify which QT modules to add to the executable.
target_link_libraries(TradingSystem
        Qt5::Core
        Qt5::Network
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
        PoloniexAPI)

add_dependencies(TradingSystem PoloniexAPI)

# Link Dependencies.
#TARGET_LINK_LIBRARIES( PoloniexAPIWrapper ${Boost_LIBRARIES} )

message(status "** Cmake Prefix Path: ${CMAKE_PREFIX_PATH}")
message(status "** Source Files: ${SOURCE_FILES}")
