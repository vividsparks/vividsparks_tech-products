# Copyright (c) 2020, VividSparks IT Solutions Pvt. Ltd.  All rights reserved.
#
# Redistribution and use in source and binary forms, modifications,
# are NOT permitted.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# This Makefile fragment defines rules for compilation of the C/C++
# files for running regression tests.

ORANGE=\033[0;33m
RED=\033[0;31m
NC=\033[0m

# This file REQUIRES several variables to HE set. They are typically
# set by the Makefile that includes this makefile..
#

DEFINES    +=
INCLUDES   += -I$(LIBRARIES_PATH)
INCLUDES   += -I$(RACER_PLATFORM_PATH)
INCLUDES   += -I$(LIBRARIES_PATH)/platforms/common/dpi

LDFLAGS    += -lstdc++ -lc -L$(RACER_PLATFORM_PATH)
CXXFLAGS   += $(DEFINES) -fPIC
CFLAGS     += $(DEFINES) -fPIC

# each regression target needs to build its .o from a .c and .h of the
# same name
%.o: %.c
	$(CC) -c -o $@ $< $(INCLUDES) $(CFLAGS) $(CDEFINES)

# ... or a .cpp and .hpp of the same name
%.o: %.cpp
	$(CXX) -c -o $@ $< $(INCLUDES) $(CXXFLAGS) $(CXXDEFINES)

# Compile all of the sources into a shared object file for dynamic loading.
TEST_CSOURCES   += $(filter %.c,$(TEST_SOURCES))
TEST_CXXSOURCES += $(filter %.cpp,$(TEST_SOURCES))
TEST_OBJECTS    += $(TEST_CXXSOURCES:.cpp=.o)
TEST_OBJECTS    += $(TEST_CSOURCES:.c=.o)

main.so: $(TEST_OBJECTS)
	$(CXX) -shared -o $@ $^ $(LDFLAGS)

.PRECIOUS: %.o %.so

.PHONY: platform.compilation.clean
platform.compilation.clean:
	rm -rf *.o *.so

compilation.clean: platform.compilation.clean
