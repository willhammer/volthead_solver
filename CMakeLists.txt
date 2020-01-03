#================OPTIONS==========================
option(USE_PYTHON_LOADER "Use python loader" ON)

#================ESSENTIALS=======================
cmake_minimum_required(VERSION 3.10)

#==================CONFIG=========================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(MAIN_PROJECT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(MAIN_PROJECT_DIR main)
set(MAIN_PROJECT_NAME volthead_main)
set(SUPPORTED_FILE_EXTENSIONS "cxx;cpp;c;h;hpp;hxx;py")
set(SOURCE_FILES "")

#====PYTHON, EH ?======
set(PYTHON_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/python_include")
set(PYTHON_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/python_lib")

#====ALL LIBRARIES SHOULD BE MENTIONED HERE=======
set(AVAILABLE_LIBRARIES python_loader)

#==============PROJECT SETUP======================
project(${MAIN_PROJECT_NAME} VERSION 0.1 LANGUAGES C CXX)
configure_file(${MAIN_PROJECT_NAME}_config.h.in "${MAIN_PROJECT_SOURCE_DIR}/${MAIN_PROJECT_DIR}/${MAIN_PROJECT_NAME}_config.h")

message(STATUS "Python includes path: ${PYTHON_INCLUDES}")
message(STATUS "Python libs path: ${PYTHON_LIBS}")

#================FUNCTIONS========================
function(populate_files_for_library library_name) 
	set(SOURCE_FILES "")
	set(FULL_PATH ${MAIN_PROJECT_SOURCE_DIR}/${library_name})
	foreach(extension ${SUPPORTED_FILE_EXTENSIONS})		
		file(GLOB FOUND_FILES ${FULL_PATH}/*.${extension})		
		list(APPEND SOURCE_FILES ${FOUND_FILES})
	endforeach()
	set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
endfunction()

populate_files_for_library(main)
add_executable(${MAIN_PROJECT_NAME} ${SOURCE_FILES})

#==========REPEAT THIS FOR EACH LIBRARY===========
populate_files_for_library(python_loader)
add_library(python_loader ${SOURCE_FILES})

#====PYTHON, EH ?======
#for python_loader
target_include_directories(python_loader PUBLIC ${PYTHON_INCLUDES})
target_include_directories(python_loader PUBLIC ${PYTHON_LIBS})
target_link_libraries(python_loader ${PYTHON_LIBS}/python38.lib)
target_link_libraries(python_loader ${PYTHON_LIBS}/python3.lib)

#for the main project. temporary. remove after you fix python_loader includes into the main proj
target_include_directories(${MAIN_PROJECT_NAME} PUBLIC ${PYTHON_INCLUDES})
target_include_directories(${MAIN_PROJECT_NAME} PUBLIC ${PYTHON_LIBS})
target_link_libraries(${MAIN_PROJECT_NAME} ${PYTHON_LIBS}/python38.lib)
target_link_libraries(${MAIN_PROJECT_NAME} ${PYTHON_LIBS}/python3.lib)

#=====THIS LINKS ALL LIBRARIES TO MAIN FOR NOW====
target_link_libraries(${MAIN_PROJECT_NAME} ${AVAILABLE_LIBRARIES})