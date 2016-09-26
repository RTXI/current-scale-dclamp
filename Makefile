PLUGIN_NAME = current_scale_dclamp

RTXI_INCLUDES=/usr/local/lib/rtxi_includes

HEADERS = IScale_DynClamp.h \
          include/IS_DC_MainWindowUI.h \
          include/IS_DC_Protocol.h \
          include/IS_DC_AddStepDialogUI.h \
          include/MCL/ModelCell.h \
          ${RTXI_INCLUDES}/rtmath.h \
          ${RTXI_INCLUDES}/powfast.hpp \
          include/MCL/models/include/default_model.h \
          include/MCL/models/LivRudy2009/LivRudy2009.h \
          include/MCL/models/FaberRudy2000/FaberRudy2000.h \
          include/MCL/models/Pandit/Pandit.h \
          include/MCL/models/TenTusscher2006/TenTusscher2006.h \
          include/MCL/models/WangSobie/WangSobie.h

SOURCES = IScale_DynClamp.cpp \
          moc_IScale_DynClamp.cpp \
          include/IS_DC_MainWindowUI.cpp \
          include/moc_IS_DC_MainWindowUI.cpp \
          include/IS_DC_Protocol.cpp \
          include/moc_IS_DC_Protocol.cpp \
          include/IS_DC_AddStepDialogUI.cpp \
          include/moc_IS_DC_AddStepDialogUI.cpp \
          include/MCL/ModelCell.cpp \
          ${RTXI_INCLUDES}/rtmath.cpp \
          ${RTXI_INCLUDES}/powfast.cpp \
          include/MCL/models/include/default_model.cpp \
          include/MCL/models/LivRudy2009/LivRudy2009.cpp \
          include/MCL/models/FaberRudy2000/FaberRudy2000.cpp \
          include/MCL/models/Pandit/Pandit.cpp \
          include/MCL/models/TenTusscher2006/TenTusscher2006.cpp \
          include/MCL/models/WangSobie/WangSobie.cpp

LIBS = -lgsl -lgslcblas

### Do not edit below this line ###

include $(shell rtxi_plugin_config --pkgdata-dir)/Makefile.plugin_compile

clean: extraclean

extraclean: 
	rm -rf include/.libs
	rm -rf include/*/.libs
	rm -rf include/*/*/.libs
	rm -rf include/*/*/*/.libs
	rm -f include/*.o
	rm -f include/moc_*
	rm include/*/*.o
	rm include/*/*/*/*.o
