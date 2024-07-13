cmake_minimum_required(VERSION 3.5)

project(LS_Midterm LANGUAGES C)

add_definitions(-DDEBUG_MODE_ENABLED)

add_executable(LS_Midterm main.c
    flags/flags.h
    flags/setFlags.c
    flags/setFlags.h
    flags/checkFlags.h
    flags/checkFlags.c
    file/checkFileType.h
    file/checkFileType.c
    file/fileListing.h
    get/getDir.h
    get/getDir.c
    get/getFile.h
    get/getFile.c

    str/strFileMode.h
    str/strFileMode.c
    str/strFileTime.h
    str/strFileTime.c
    str/strFileSize.h
    str/strFileSize.c
    str/strFileName.h
    str/strFileName.c
    sort/sortArray.h
    sort/sortArray.c
    print/printListing.h
    print/printListing.c

    queue/dirQueue.c
    queue/dirQueue.h
    get/recurDir.c
    get/recurDir.h
)

target_link_libraries(LS_Midterm m)

include(GNUInstallDirs)
install(TARGETS LS_Midterm
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
