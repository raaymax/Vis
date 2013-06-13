find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include_directories(${KDE4_INCLUDES})

set(katefilebrowsermodifiedplugin_PART_SRCS katefilebrowserplugin.cpp katefilebrowserconfig.cpp katefilebrowser.cpp katebookmarkhandler.cpp )

kde4_add_plugin(katefilebrowsermodifiedplugin ${katefilebrowsermodifiedplugin_PART_SRCS})

target_link_libraries(katefilebrowsermodifiedplugin ${KDE4_KFILE_LIBS} ${KDE4_KPARTS_LIBS} kateinterfaces )

install(TARGETS katefilebrowsermodifiedplugin  DESTINATION ${PLUGIN_INSTALL_DIR} )


########### install files ###############

install( FILES katefilebrowsermodifiedplugin.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )

