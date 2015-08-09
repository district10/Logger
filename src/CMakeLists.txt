# set project's name
project( Logger )

# Set the include directories
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB HDRS_FILES *.h *.hpp)
file(GLOB SRCS_FILES *.cpp)
file(GLOB UI_FILES *.ui)
file(GLOB CD_FILES *.cd)

# Qt4 
find_package( Qt4 REQUIRED)
set(QT_USE_QTMAIN TRUE)
set(QT_USE_QTOPENGL TRUE)
set(QT_USE_QTXML TRUE)
set(QT_USE_QTNETWORK TRUE)
set(QT_USE_PHONON TURE)
qt4_wrap_cpp(MOC_SRCS ${HDRS_FILES})
#qt4_add_resources(RSC_SRCS ${RSCS})
qt4_wrap_ui(UI_HDRS ${UI_FILES})
include( ${QT_USE_FILE} )

# Boost
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost REQUIRED COMPONENTS filesystem thread)
MESSAGE(STATUS "Boost_LIBS: ${Boost_LIBRARIES}")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIR})

set(FILES_TO_TRANSLATE ${FILES_TO_TRANSLATE} ${SRCS_FILES} ${UI_FILES} ${HDRS_FILES} PARENT_SCOPE)

source_group("UI Files" FILES ${UI_FILES})
source_group("Generated Files" FILES ${MOC_SRCS} ${UI_HDRS} ${RSC_SRCS})
source_group("Class Diagrams" FILES ${CD_FILES} )

add_executable(${PROJECT_NAME} ${SRCS_FILES} ${UI_FILES} ${HDRS_FILES} ${MOC_SRCS} ${UI_HDRS} ${RSC_SRCS} ${CD_FILES})
# set_source_files_properties(${CD_FILES} PROPERTIES HEADER_FILE_ONLY TRUE) #DO NOT COMPILE CS FILES
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER SRC/Utils)  	