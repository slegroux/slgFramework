cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME audio_app) 
#project($PROJECT_NAME)

MESSAGE(STATUS "starting compilation")
set(SLG "../slg")
set(RTA "../RtAudio/")

set(SRCS
  main.cpp
  ${RTA}/RtAudio.cpp
  ${SLG}/slgAudio.cpp
)

include_directories(${PROJECT_NAME} PUBLIC
  ${RTA}
  ${SLG}
)
# add_subdirectory(${AUDIO_LIB_DIR})
# link_directories(${AUDIO_LIB_DIR})

add_executable(${PROJECT_NAME}
  ${SRCS}
)

if (UNIX)
  # pulse audio
  MESSAGE(STATUS "Linux build")
  target_link_libraries(${PROJECT_NAME} PUBLIC -Wall -lpthread -lpulse-simple -lpulse -lstdc++ -lm)
  add_definitions(-D__LINUX_PULSE__)
endif()

if (APPLE)
  MESSAGE(STATUS "OSX build")
  find_library(CA CoreAudio)
  find_library(CF CoreFoundation)
  target_link_libraries(${PROJECT_NAME} PUBLIC ${CA} ${CF})
  add_definitions(-D__MACOSX_CORE__)
endif()



#target_link_libraries(${PROJECT_NAME}
#  slgaudio
#)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

