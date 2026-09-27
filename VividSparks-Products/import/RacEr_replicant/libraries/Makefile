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

# This Makefile contains rules for building the RACER Manycore Runtime
# libraries.

# environment.mk verifies the build environment and sets the following
# variables
#
# TESTBENCH_PATH: The path to the testbench directory in the RacEr_f1 repository
# LIBRAIRES_PATH: The path to the libraries directory in the RacEr_f1 repository
# HARDARE_PATH: The path to the hardware directory in the RacEr_f1 repository
# BASEJUMP_STL_DIR: Path to a clone of BaseJump STL
# RACER_MANYCORE_DIR: Path to a clone of RACER Manycore
# CL_DIR: Path to the directory of this AWS F1 Project
include ../environment.mk

# libraries.mk defines rules for building the RACER Manycore Runtime libraries,
# flags, and a list of sources.
include $(LIBRARIES_PATH)/libraries.mk

_TARGETS :=
_DOCSTRING :=

_DOCSTRING += "Rules from Makefile\n"
_TARGETS :=

.DEFAULT_GOAL := help
_TARGETS += "help"
_DOCSTRING += "    help: \n"
_DOCSTRING += "        - Output a friendly help message\n"
help:
	@echo -e $(DOCSTRING)

_TARGETS += "build"
_DOCSTRING += "    build:\n"
_DOCSTRING += "        - Compile the RACER Manycore Runtime Libraries (libRacEr_manycore_runtime.so)\n"
_DOCSTRING += "          in RACER_PLATFORM_PATH (./$(shell realpath --relative-to . $(RACER_PLATFORM_PATH)))\n"
build: $(RACER_PLATFORM_PATH)/libRacEr_manycore_runtime.so.1.0
build: $(RACER_PLATFORM_PATH)/libbsgmc_cuda_legacy_pod_repl.so.1.0
build: $(RACER_PLATFORM_PATH)/libRacEr_manycore_regression.so.1.0

_TARGETS += "clean"
_DOCSTRING += "    clean:\n"
_DOCSTRING += "        - Remove all outputs\n"
clean: libraries.clean

.PHONY: build clean help

_TARGETS += $(TARGETS)
TARGETS := $(_TARGETS)
TARGETS := $(shell echo "$(TARGETS)" | tr -s " ")

_DOCSTRING += "\n"
_DOCSTRING += $(DOCSTRING)
DOCSTRING := "\nUsage: make {$(TARGETS)} (default: $(.DEFAULT_GOAL))\n" $(_DOCSTRING)

