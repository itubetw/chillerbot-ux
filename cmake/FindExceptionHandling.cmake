if(TARGET_OS STREQUAL "windows")
  set_extra_dirs_lib(EXCEPTION_HANDLING drmingw)
  find_file(EXCEPTION_HANDLING_LIBRARY
    NAMES exchndl.dll
    HINTS ${HINTS_EXCEPTION_HANDLING_LIBDIR}
    PATHS ${PATHS_EXCEPTION_HANDLING_LIBDIR}
    ${CROSSCOMPILING_NO_CMAKE_SYSTEM_PATH}
  )

  is_bundled(EXCEPTION_HANDLING_BUNDLED "${EXCEPTION_HANDLING_LIBRARY}")
  if(NOT EXCEPTION_HANDLING_BUNDLED)
    message(FATAL_ERROR "could not find exception handling paths")
  endif()
  if(TARGET_CPU_ARCHITECTURE STREQUAL "arm64")
    set(EXCEPTION_HANDLING_COPY_FILES
      "${EXTRA_EXCEPTION_HANDLING_LIBDIR}/exchndl.dll"
      "${EXTRA_EXCEPTION_HANDLING_LIBDIR}/mgwhelp.dll"
    )
  else()
    set(EXCEPTION_HANDLING_COPY_FILES
      "${EXTRA_EXCEPTION_HANDLING_LIBDIR}/exchndl.dll"
      "${EXTRA_EXCEPTION_HANDLING_LIBDIR}/dbgcore.dll"
      "${EXTRA_EXCEPTION_HANDLING_LIBDIR}/dbghelp.dll"
      "${EXTRA_EXCEPTION_HANDLING_LIBDIR}/mgwhelp.dll"
      "${EXTRA_EXCEPTION_HANDLING_LIBDIR}/symsrv.dll"
    )
  endif()
endif()
