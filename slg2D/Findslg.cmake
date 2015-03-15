find_path(slg_INCLUDE_DIRS slgGraphics.h realFFTW.h slgCircularBuffer.h Thread.h slgUtils.h /usr/include "$ENV{SLG_ROOT}")

  find_library(Namer_LIBRARIES slg /usr/lib "$ENV{SLG_ROOT}")

  set(slg_FOUND TRUE)

  if (NOT slg_INCLUDE_DIRS)
    set(slg_FOUND FALSE)
  endif (NOT slg_INCLUDE_DIRS)

  if (NOT slg_LIBRARIES)
    set(slg_FOUND FALSE)
  endif (NOT slg_LIBRARIES)