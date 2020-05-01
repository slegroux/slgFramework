cmake_minimum_required(VERSION 3.13)

set(PROJECT audio_app) 
project(${PROJECT})

MESSAGE(STATUS "starting compilation")
set(SLG "../slg")
set(RTA "../RtAudio/")

set(SRCS
  main.cpp
  ${RTA}/RtAudio.cpp
  ${SLG}/slgAudio.cpp
)

include_directories(${PROJECT} PUBLIC
  ${RTA}
  ${SLG}
)
# add_subdirectory(${AUDIO_LIB_DIR})
# link_directories(${AUDIO_LIB_DIR})

add_executable(${PROJECT}
  ${SRCS}
)

if (UNIX AND NOT APPLE)
  # pulse audio
  MESSAGE(STATUS "Linux build")
  target_link_libraries(${PROJECT} PUBLIC -Wall -lpthread -lpulse-simple -lpulse -lstdc++ -lm)
  add_definitions(-D__LINUX_PULSE__)
endif()

if (APPLE)
  MESSAGE(STATUS "OSX build")
  find_library(CA CoreAudio)
  find_library(CF CoreFoundation)
  target_link_libraries(${PROJECT} PUBLIC ${CA} ${CF} -Wall -lpthread -lm)
  add_definitions(-D__MACOSX_CORE__ -Wno-c++11-extensions)
endif()

#target_link_libraries(${PROJECT}
#  slgaudio
#)

install(TARGETS ${PROJECT} DESTINATION bin)

