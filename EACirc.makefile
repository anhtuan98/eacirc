#*********************************************************************************
# EACirc project (makefile)
#
# This makefile is for UNIX platforms only (due to shell commands and paths format).
# Makefiles for GAlib and tinyXML can be used on other platforms, see details below.
#
# EACirc: unix environment required, compilation settings below.
#         g++ version 4.7 or higher is needed
# GAlib: Compilation settings and platform dependent variables are in galib/makefile.
# tinyXML: Compilation settings and platform dependent variables are in tinyXML/makefile.
#
# DEBUG can be set to YES to include debugging info, or NO otherwise
DEBUG		= NO
# PROFILE can be set to YES to include profiling info, or NO otherwise
PROFILE		= NO
# output name for the compiled and linked application
OUTNAME		= eacirc
# folder to put linked application and config file into
RUN_DIR		= run
#*********************************************************************************

# complation settings
#CXX			= g++
CXX			= g++-4.7
CXXFLAGS		= -std=c++11 # -Wall
DEBUG_CXXFLAGS		= -g -DDEBUG
RELEASE_CXXFLAGS	= -O3
PROFILE_CXXFLAGS	= -p

# libs and source (loaded from Qt project file)
include EACirc.pro
OBJECTS		=$(SOURCES:.cpp=.o)
INC_DIRS	= -IEACirc -IEACirc/galib -IEACirc/tinyXML
INC_LIBS	= -LEACirc/galib -LEACirc/tinyXML -lga -ltinyXML

# rules and targets
ifeq (YES, ${DEBUG})
   CXXFLAGS     += $(DEBUG_CXXFLAGS)
else
   CXXFLAGS     += $(RELEASE_CXXFLAGS)
endif
ifeq (YES, $(PROFILE))
   CXXFLAGS += $(PROFILE_CXXFLAGS)
endif

all: libs main

libs:
	cd EACirc/galib && $(MAKE)
	cd EACirc/tinyXML && $(MAKE)
	@echo === Libraries are now up-to-date. ===

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -c -o "$@" "$<"

main: $(OBJECTS)
	mkdir -p $(RUN_DIR)
	$(CXX) $(CXXFLAGS) -o $(RUN_DIR)/$(OUTNAME) $(OBJECTS) $(INC_DIRS) $(INC_LIBS)
	if [ ! -f $(RUN_DIR)/config.xml ]; then cp EACirc/config.xml $(RUN_DIR)/; fi
	@echo === $(OUTNAME) was successfully built. ===

clean:
	cd EACirc/galib && $(MAKE) clean
	cd EACirc/tinyXML && $(MAKE) clean
	rm -f $(OBJECTS) 
	cd $(RUN_DIR) && rm -f *.log *.txt *.bin *.c *.dot *.xml
	@echo === Successfully cleaned. ===

cleanmain:
	rm -f $(OBJECTS) $(RUN_DIR)/$(OUTNAME)
	@echo === Project successfully cleaned \(libraries untouched\). ===
