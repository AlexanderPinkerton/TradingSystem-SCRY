#cmake_minimum_required(VERSION 3.6)
#project(PoloniexAPI)
#set(CMAKE_CXX_STANDARD 11)


#----------------Prepare and Load Dependencies--------------------------------
#Add the QT Cmake path to the current cmake path.
#If it cannot find QT, make sure it is installed and then set the QtCmakePath

#Add the <Qt5Dir>/lib/cmake/Qt5 Enivronment Variable to the prefix path
SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "~/Qt5.8.0/5.8/gcc_64/lib/cmake/Qt5")
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find the Qt Modules
find_package(Qt5 COMPONENTS Network REQUIRED )

# Instruct CMake to run moc automatically when needed. [For Qt]
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


# Tell Cmake what user files to include in the build process.
file(GLOB SOURCE_FILES "*.cpp" "*.hpp")



#------------------Create executable target with source files----------------
#add_executable(PoloniexAPI ${SOURCE_FILES})

#------------------Create library  target with source files----------------
add_library(PoloniexAPI SHARED ${SOURCE_FILES})


#------------------Attach Dependencies to Executable-----------------------

# Specify which libraries to add to the executable.
target_link_libraries(PoloniexAPI
        Qt5::Network)

