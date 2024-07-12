cmake_minimum_required(VERSION 3.5)

project(LS_Midterm LANGUAGES C)

add_definitions(-DDEBUG_MODE_ENABLED)

add_executable(LS_Midterm main.c
    flags.h
    setFlags.c
    setFlags.h
    checkFlags.h
    checkFlags.c
    checkFileType.h
    checkFileType.c
    getDir.h
    getDir.c
    getFile.h
    getFile.c
    strFileMode.h
    strFileMode.c


    sortArray.h
    sortArray.c
    fileListing.h
    printListing.h
    printListing.c
    strFileTime.h
    strFileTime.c
    strFileSize.h
    strFileSize.c
    strFileName.h
    strFileName.c
    dirQueue.c
    dirQueue.h)

target_link_libraries(LS_Midterm m)

include(GNUInstallDirs)
install(TARGETS LS_Midterm
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
