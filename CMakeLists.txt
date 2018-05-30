cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project("pbcvt")

#----------------------------CMAKE & GLOBAL PROPERTIES-------------------------#
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

###============= C++11 support====================================
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if (COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif (COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else ()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif ()


#=============== Find Packages 
find_package(OpenCV  REQUIRED)
include("DetectPython")

find_package(Boost COMPONENTS REQUIRED python)


#========pick python stuff========================================

SET(PYTHON_INCLUDE_DIRS /usr/include/python2.7)
SET(PYTHON_LIBRARIES ${PYTHON2_LIBRARY})
SET(PYTHON_EXECUTABLE ${PYTHON2_EXECUTABLE})
SET(PYTHON_PACKAGES_PATH ${PYTHON2_PACKAGES_PATH})
SET(ARCHIVE_OUTPUT_NAME pbcvt_py2)



#====================== add module=========================================
add_executable(add 
${CMAKE_CURRENT_SOURCE_DIR}/src/pyboost_cv2_converter.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/src/add.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/src/pyboost_cv3_converter.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/include/pyboostcvconverter/pyboostcvconverter.hpp)

target_include_directories(add PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/include 
${Boost_INCLUDE_DIRS} 
${OpenCV_INCLUDE_DIRS} 
${PYTHON_INCLUDE_DIRS}
${PCL_INCLUDE_DIRS})

target_link_libraries(add ${Boost_LIBRARIES} ${OpenCV_LIBS} ${PYTHON_LIBRARIES} ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})



#==========================image module=====================================
add_executable(image 
${CMAKE_CURRENT_SOURCE_DIR}/src/pyboost_cv2_converter.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/src/image.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/src/pyboost_cv3_converter.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/include/pyboostcvconverter/pyboostcvconverter.hpp)

target_include_directories(image PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/include 
${Boost_INCLUDE_DIRS} 
${OpenCV_INCLUDE_DIRS} 
${PYTHON_INCLUDE_DIRS}
${PCL_INCLUDE_DIRS})

target_link_libraries(image ${Boost_LIBRARIES} ${OpenCV_LIBS} ${PYTHON_LIBRARIES} ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})
