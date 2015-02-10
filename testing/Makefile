PLUGIN_NAME = IScale_DynClamp

HEADERS = IScale_DynClamp.h

SOURCES = IScale_DynClamp.cpp moc_IScale_DynClamp.cpp \
	include/IS_DC_MainWindowUI.cpp include/moc_IS_DC_MainWindowUI.cpp \
	include/IS_DC_Protocol.cpp include/moc_IS_DC_Protocol.cpp \
	include/IS_DC_AddStepDialogUI.cpp include/moc_IS_DC_AddStepDialogUI.cpp \
	include/MCL/ModelCell.cpp include/MCL/models/include/default_model.cpp \
	include/MCL/models/include/RealTimeMath.cpp include/MCL/models/include/PowFast.cpp \
	include/MCL/models/LivRudy2009/LivRudy2009.cpp \
	include/MCL/models/FaberRudy2000/FaberRudy2000.cpp \
	include/MCL/models/Pandit/Pandit.cpp \
	include/MCL/models/TenTusscher2006/TenTusscher2006.cpp \
	include/MCL/models/WangSobie/WangSobie.cpp

LIBS = -lgsl -lgslcblas

### Do not edit below this line ###

include $(shell rtxi_plugin_config --pkgdata-dir)/Makefile.plugin_compile

clean:
	rm -f $(OBJECTS)
	rm -f moc_*
	rm -f *.o
	rm -f $(PLUGIN_NAME).la
	rm -f $(PLUGIN_NAME).o
	rm -rf .libs
	rm -f include/*.o
	rm -f include/moc_*
	rm include/*/*.o
	rm include/*/*/*/*.o
