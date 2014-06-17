#############################################################################
# Makefile for building: PhysicsRPG
# Generated by qmake (3.0) (Qt 5.2.1)
# Project:  PhysicsRPG.pro
# Template: app
# Command: /opt/Qt5.2.1/5.2.1/gcc_64/bin/qmake -spec linux-g++ CONFIG+=debug CONFIG+=declarative_debug CONFIG+=qml_debug -o Makefile PhysicsRPG.pro
#############################################################################

MAKEFILE      = Makefile

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG
CFLAGS        = -pipe -g -Wall -W -fPIE $(DEFINES)
CXXFLAGS      = -pipe -std=c++11 -g -Wall -W -fPIE $(DEFINES)
INCPATH       = -I/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/linux-g++ -I. -Iinclude
LINK          = g++
LFLAGS        = -Wl,-rpath,/opt/Qt5.2.1/5.2.1/gcc_64
LIBS          = $(SUBLIBS) -lsfml-system -lsfml-graphics -lsfml-window -lBox2D 
AR            = ar cqs
RANLIB        = 
QMAKE         = /opt/Qt5.2.1/5.2.1/gcc_64/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = src/TextureManager.cpp \
		src/TestState.cpp \
		src/State.cpp \
		src/SpriteBody.cpp \
		src/PolygonBody.cpp \
		src/MapState.cpp \
		src/main.cpp \
		src/Globals.cpp \
		src/GameState.cpp \
		src/GameObject.cpp \
		src/GameManager.cpp \
		src/Flag.cpp \
		src/Entity.cpp \
		src/Entidade.cpp \
		src/Engine.cpp \
		src/DebugRender.cpp \
		src/ContactListenner.cpp \
		src/Character.cpp \
		src/BoxBody.cpp \
		src/Body.cpp \
		src/Animation.cpp 
OBJECTS       = TextureManager.o \
		TestState.o \
		State.o \
		SpriteBody.o \
		PolygonBody.o \
		MapState.o \
		main.o \
		Globals.o \
		GameState.o \
		GameObject.o \
		GameManager.o \
		Flag.o \
		Entity.o \
		Entidade.o \
		Engine.o \
		DebugRender.o \
		ContactListenner.o \
		Character.o \
		BoxBody.o \
		Body.o \
		Animation.o
DIST          = /opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/spec_pre.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/shell-unix.conf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/unix.conf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/linux.conf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/gcc-base.conf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/gcc-base-unix.conf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/g++-base.conf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/g++-unix.conf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/qconfig.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_bluetooth.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_bluetooth_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_clucene_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_concurrent.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_concurrent_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_core.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_core_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_dbus.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_dbus_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_declarative.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_declarative_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_designer.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_designer_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_designercomponents_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_gui.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_gui_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_help.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_help_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_multimedia.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_multimedia_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_multimediawidgets.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_multimediawidgets_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_network.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_network_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_nfc.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_nfc_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_opengl.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_opengl_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_openglextensions.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_positioning.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_positioning_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_printsupport.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_printsupport_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qml.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qml_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qmltest.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qmltest_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_quick.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_quick_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_quickparticles_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_script.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_script_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_scripttools.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_scripttools_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_sensors.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_sensors_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_serialport.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_serialport_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_sql.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_sql_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_svg.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_svg_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_testlib.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_testlib_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_uitools.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_uitools_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_webkit.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_webkit_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_webkitwidgets.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_webkitwidgets_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_widgets.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_widgets_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_x11extras.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_x11extras_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_xml.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_xml_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_xmlpatterns.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/qt_functions.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/qt_config.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/linux-g++/qmake.conf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/spec_post.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/exclusive_builds.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/default_pre.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/resolve_config.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/default_post.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/qml_debug.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/declarative_debug.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/unix/gdb_dwarf_index.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/warn_on.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/testcase_targets.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/exceptions.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/yacc.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/lex.prf \
		PhysicsRPG.pro \
		PhysicsRPG.pro
QMAKE_TARGET  = PhysicsRPG
DESTDIR       = #avoid trailing-slash linebreak
TARGET        = PhysicsRPG


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9][^0-9]*\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: PhysicsRPG.pro /opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/linux-g++/qmake.conf /opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/spec_pre.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/shell-unix.conf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/unix.conf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/linux.conf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/gcc-base.conf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/gcc-base-unix.conf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/g++-base.conf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/g++-unix.conf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/qconfig.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_bluetooth.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_bluetooth_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_clucene_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_concurrent.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_concurrent_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_core.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_core_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_dbus.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_dbus_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_declarative.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_declarative_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_designer.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_designer_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_designercomponents_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_gui.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_gui_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_help.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_help_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_multimedia.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_multimedia_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_multimediawidgets.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_multimediawidgets_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_network.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_network_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_nfc.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_nfc_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_opengl.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_opengl_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_openglextensions.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_positioning.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_positioning_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_printsupport.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_printsupport_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qml.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qml_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qmltest.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qmltest_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_quick.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_quick_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_quickparticles_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_script.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_script_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_scripttools.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_scripttools_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_sensors.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_sensors_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_serialport.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_serialport_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_sql.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_sql_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_svg.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_svg_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_testlib.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_testlib_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_uitools.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_uitools_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_webkit.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_webkit_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_webkitwidgets.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_webkitwidgets_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_widgets.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_widgets_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_x11extras.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_x11extras_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_xml.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_xml_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_xmlpatterns.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/qt_functions.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/qt_config.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/linux-g++/qmake.conf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/spec_post.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/exclusive_builds.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/default_pre.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/resolve_config.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/default_post.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/qml_debug.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/declarative_debug.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/unix/gdb_dwarf_index.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/warn_on.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/testcase_targets.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/exceptions.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/yacc.prf \
		/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/lex.prf \
		PhysicsRPG.pro
	$(QMAKE) -spec linux-g++ CONFIG+=debug CONFIG+=declarative_debug CONFIG+=qml_debug -o Makefile PhysicsRPG.pro
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/spec_pre.prf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/shell-unix.conf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/unix.conf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/linux.conf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/gcc-base.conf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/gcc-base-unix.conf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/g++-base.conf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/common/g++-unix.conf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/qconfig.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_bluetooth.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_bluetooth_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_bootstrap_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_clucene_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_concurrent.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_concurrent_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_core.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_core_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_dbus.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_dbus_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_declarative.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_declarative_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_designer.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_designer_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_designercomponents_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_gui.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_gui_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_help.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_help_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_multimedia.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_multimedia_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_multimediawidgets.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_multimediawidgets_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_network.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_network_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_nfc.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_nfc_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_opengl.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_opengl_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_openglextensions.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_openglextensions_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_platformsupport_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_positioning.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_positioning_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_printsupport.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_printsupport_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qml.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qml_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qmldevtools_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qmltest.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qmltest_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_quick.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_quick_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_quickparticles_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_script.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_script_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_scripttools.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_scripttools_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_sensors.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_sensors_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_serialport.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_serialport_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_sql.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_sql_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_svg.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_svg_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_testlib.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_testlib_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_uitools.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_uitools_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_webkit.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_webkit_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_webkitwidgets.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_webkitwidgets_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_widgets.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_widgets_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_x11extras.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_x11extras_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_xml.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_xml_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_xmlpatterns.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/modules/qt_lib_xmlpatterns_private.pri:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/qt_functions.prf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/qt_config.prf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/linux-g++/qmake.conf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/spec_post.prf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/exclusive_builds.prf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/default_pre.prf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/resolve_config.prf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/default_post.prf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/qml_debug.prf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/declarative_debug.prf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/unix/gdb_dwarf_index.prf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/warn_on.prf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/testcase_targets.prf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/exceptions.prf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/yacc.prf:
/opt/Qt5.2.1/5.2.1/gcc_64/mkspecs/features/lex.prf:
PhysicsRPG.pro:
qmake: FORCE
	@$(QMAKE) -spec linux-g++ CONFIG+=debug CONFIG+=declarative_debug CONFIG+=qml_debug -o Makefile PhysicsRPG.pro

qmake_all: FORCE

dist: 
	@test -d .tmp/PhysicsRPG1.0.0 || mkdir -p .tmp/PhysicsRPG1.0.0
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/PhysicsRPG1.0.0/ && (cd `dirname .tmp/PhysicsRPG1.0.0` && $(TAR) PhysicsRPG1.0.0.tar PhysicsRPG1.0.0 && $(COMPRESS) PhysicsRPG1.0.0.tar) && $(MOVE) `dirname .tmp/PhysicsRPG1.0.0`/PhysicsRPG1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/PhysicsRPG1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

TextureManager.o: src/TextureManager.cpp include/TextureManager.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TextureManager.o src/TextureManager.cpp

TestState.o: src/TestState.cpp include/TestState.h \
		include/State.h \
		include/DebugRender.h \
		include/BoxBody.h \
		include/SpriteBody.h \
		include/Body.h \
		include/Animation.h \
		include/Globals.h \
		include/TextureManager.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TestState.o src/TestState.cpp

State.o: src/State.cpp include/State.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o State.o src/State.cpp

SpriteBody.o: src/SpriteBody.cpp include/SpriteBody.h \
		include/Body.h \
		include/Animation.h \
		include/Globals.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o SpriteBody.o src/SpriteBody.cpp

PolygonBody.o: src/PolygonBody.cpp include/PolygonBody.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o PolygonBody.o src/PolygonBody.cpp

MapState.o: src/MapState.cpp include/MapState.h \
		include/State.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MapState.o src/MapState.cpp

main.o: src/main.cpp include/GameManager.h \
		include/State.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o src/main.cpp

Globals.o: src/Globals.cpp include/Globals.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Globals.o src/Globals.cpp

GameState.o: src/GameState.cpp include/GameState.h \
		include/State.h \
		include/DebugRender.h \
		include/BoxBody.h \
		include/SpriteBody.h \
		include/Body.h \
		include/Animation.h \
		include/ContactListenner.h \
		include/Globals.h \
		include/TextureManager.h \
		include/Engine.h \
		include/Flag.h \
		include/Entity.h \
		include/Character.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o GameState.o src/GameState.cpp

GameObject.o: src/GameObject.cpp include/GameObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o GameObject.o src/GameObject.cpp

GameManager.o: src/GameManager.cpp include/GameManager.h \
		include/State.h \
		include/TestState.h \
		include/DebugRender.h \
		include/BoxBody.h \
		include/SpriteBody.h \
		include/Body.h \
		include/Animation.h \
		include/GameState.h \
		include/ContactListenner.h \
		include/Engine.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o GameManager.o src/GameManager.cpp

Flag.o: src/Flag.cpp include/Flag.h \
		include/Entity.h \
		include/SpriteBody.h \
		include/Body.h \
		include/Animation.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Flag.o src/Flag.cpp

Entity.o: src/Entity.cpp include/Entity.h \
		include/SpriteBody.h \
		include/Body.h \
		include/Animation.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Entity.o src/Entity.cpp

Entidade.o: src/Entidade.cpp include/Entidade.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Entidade.o src/Entidade.cpp

Engine.o: src/Engine.cpp include/Engine.h \
		include/Globals.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Engine.o src/Engine.cpp

DebugRender.o: src/DebugRender.cpp include/DebugRender.h \
		include/Globals.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o DebugRender.o src/DebugRender.cpp

ContactListenner.o: src/ContactListenner.cpp include/ContactListenner.h \
		include/Body.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ContactListenner.o src/ContactListenner.cpp

Character.o: src/Character.cpp include/Character.h \
		include/Entity.h \
		include/SpriteBody.h \
		include/Body.h \
		include/Animation.h \
		include/Globals.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Character.o src/Character.cpp

BoxBody.o: src/BoxBody.cpp include/BoxBody.h \
		include/Globals.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o BoxBody.o src/BoxBody.cpp

Body.o: src/Body.cpp include/Body.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Body.o src/Body.cpp

Animation.o: src/Animation.cpp include/Animation.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Animation.o src/Animation.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

