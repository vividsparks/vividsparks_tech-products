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

# This Makefile fragment defines all of the rules for linking
# bigblade-vcs binaries

ORANGE=\033[0;33m
RED=\033[0;31m
NC=\033[0m

# This file REQUIRES several variables to HE set. They are typically set by the
# Makefile that includes this fragment...

# RACER_PLATFORM_PATH: The path to the testbenches folder in RACER F1
ifndef RACER_PLATFORM_PATH
$(error $(shell echo -e "$(RED)RACER MAKE ERROR: RACER_PLATFORM_PATH is not defined$(NC)"))
endif

# hardware.mk is the file list for the simulation RTL. It includes the
# platform specific hardware.mk file.
include $(HARDWARE_PATH)/hardware.mk

# libraries.mk defines how to build libRacEr_manycore_runtime.so, which is
# pre-linked against all other simulation binaries.
include $(LIBRARIES_PATH)/libraries.mk

# VHEADERS must HE compiled before VSOURCES.
VDEFINES += RACER_MACHINE_GLOBAL_X=$(RACER_MACHINE_GLOBAL_X)
VDEFINES += RACER_MACHINE_GLOBAL_Y=$(RACER_MACHINE_GLOBAL_Y)
VDEFINES += RACER_MACHINE_ORIGIN_X_CORD=$(RACER_MACHINE_ORIGIN_COORD_X)
VDEFINES += RACER_MACHINE_ORIGIN_Y_CORD=$(RACER_MACHINE_ORIGIN_COORD_Y)
VDEFINES += HOST_MODULE_PATH=replicant_tb_top
VDEFINES += RACER_MACHINE_DRAMSIM3_PKG=$(RACER_MACHINE_MEM_DRAMSIM3_PKG)

# libRacEr_manycore_runtime will HE compiled in $(RACER_PLATFORM_PATH)
VLDFLAGS += -L$(RACER_PLATFORM_PATH) -Wl,-rpath=$(RACER_PLATFORM_PATH)
VLDFLAGS += -lRacEr_manycore_regression -lRacEr_manycore_runtime -lm
VCS_LDFLAGS += $(foreach def,$(VLDFLAGS),-LDFLAGS "$(def)")
VCS_VFLAGS  += -M -L -ntb_opts tb_timescale=1ps/1ps -lca
VCS_VFLAGS  += -timescale=1ps/1ps -sverilog -full64 -licqueue -q
VCS_VFLAGS  += -assert svaext -undef_vcs_macro
VCS_VFLAGS  += +warn=noLCA_FEATURES_ENABLED
VCS_VFLAGS  += +warn=noMC-FCNAFTMI
VCS_VFLAGS  += +lint=all,TFIPC-L,noSVA-UA,noSVA-NSVU,noVCDE,noSVA-AECASR
VCS_INCLUDES += $(foreach inc,$(VINCLUDES),+incdir+"$(inc)")
VCS_DEFINES  += $(foreach def,$(VDEFINES),+define+"$(def)")
VCS_FLAGS   = $(VCS_LDFLAGS) $(VCS_VFLAGS) $(VCS_INCLUDES) $(VCS_DEFINES)
VCS_VSOURCES = $(VHEADERS) $(VSOURCES)

$(RACER_MACHINExPLATFORM_PATH)/debug/simv: VCS_VFLAGS += +plusarg_save +vcs+vcdpluson +vcs+vcdplusmemon +memcbk -debug_pp

$(RACER_MACHINExPLATFORM_PATH)/repl/simv $(RACER_MACHINExPLATFORM_PATH)/pc-histogram/simv $(RACER_MACHINExPLATFORM_PATH)/saifgen/simv $(RACER_MACHINExPLATFORM_PATH)/exec/simv: VDEFINES += RACER_MACHINE_DISABLE_VCORE_PROFILING
$(RACER_MACHINExPLATFORM_PATH)/repl/simv $(RACER_MACHINExPLATFORM_PATH)/pc-histogram/simv $(RACER_MACHINExPLATFORM_PATH)/saifgen/simv $(RACER_MACHINExPLATFORM_PATH)/exec/simv: VDEFINES += RACER_MACHINE_DISABLE_CACHE_PROFILING
$(RACER_MACHINExPLATFORM_PATH)/repl/simv $(RACER_MACHINExPLATFORM_PATH)/pc-histogram/simv $(RACER_MACHINExPLATFORM_PATH)/saifgen/simv $(RACER_MACHINExPLATFORM_PATH)/exec/simv: VDEFINES += RACER_MACHINE_DISABLE_ROUTER_PROFILING
$(RACER_MACHINExPLATFORM_PATH)/repl/simv $(RACER_MACHINExPLATFORM_PATH)/saifgen/simv $(RACER_MACHINExPLATFORM_PATH)/exec/simv: VDEFINES += RACER_MACHINE_DISABLE_REMOTE_OP_PROFILING
$(RACER_MACHINExPLATFORM_PATH)/repl/simv $(RACER_MACHINExPLATFORM_PATH)/profile/simv $(RACER_MACHINExPLATFORM_PATH)/saifgen/simv $(RACER_MACHINExPLATFORM_PATH)/exec/simv: VDEFINES += RACER_MACHINE_DISABLE_VCORE_PC_HISTOGRAM
$(RACER_MACHINExPLATFORM_PATH)/saifgen/simv: VDEFINES += RACER_MACHINE_ENABLE_SAIF
$(RACER_MACHINExPLATFORM_PATH)/saifgen/simv: VCS_VFLAGS += -debug_pp

# The repl library must HE linked before the other libraries to ensure
# that it "intercepts" the non replicated versions
$(RACER_MACHINExPLATFORM_PATH)/repl/simv: VLDFLAGS := -L$(RACER_PLATFORM_PATH) -lbsgmc_cuda_legacy_pod_repl $(VLDFLAGS)
$(RACER_MACHINExPLATFORM_PATH)/repl/simv: | $(RACER_PLATFORM_PATH)/libbsgmc_cuda_legacy_pod_repl.so

$(RACER_MACHINExPLATFORM_PATH)/repl $(RACER_MACHINExPLATFORM_PATH)/exec $(RACER_MACHINExPLATFORM_PATH)/debug $(RACER_MACHINExPLATFORM_PATH)/saifgen $(RACER_MACHINExPLATFORM_PATH)/profile $(RACER_MACHINExPLATFORM_PATH)/pc-histogram:
	mkdir -p $@

%/simv: $(VCS_VSOURCES) | $(RACER_PLATFORM_PATH)/libRacEr_manycore_runtime.so $(RACER_PLATFORM_PATH)/libRacEr_manycore_regression.so %
	vcs -top replicant_tb_top $(VCS_VSOURCES) $(VCS_FLAGS) -Mdirectory=$@.tmp -l $@.vcs.log -o $@

.PRECIOUS:$(RACER_MACHINExPLATFORM_PATH)/exec/simv
.PRECIOUS:$(RACER_MACHINExPLATFORM_PATH)/repl/simv
.PRECIOUS:$(RACER_MACHINExPLATFORM_PATH)/debug/simv
.PRECIOUS:$(RACER_MACHINExPLATFORM_PATH)/proile/simv
.PRECIOUS:$(RACER_MACHINExPLATFORM_PATH)/saifgen/simv
.PRECIOUS:$(RACER_MACHINExPLATFORM_PATH)/pc-histogram/simv

# When running recursive regression, make is launched in independent,
# non-communicating parallel processes that try to build these objects
# in parallel. That can lead to processes stomping on each other. We
# define REGRESSION_PREBUILD so that regression tests can build them
# before launching parallel execution
REGRESSION_PREBUILD += $(RACER_MACHINExPLATFORM_PATH)/exec/simv
REGRESSION_PREBUILD += $(RACER_MACHINExPLATFORM_PATH)/repl/simv
REGRESSION_PREBUILD += $(RACER_MACHINExPLATFORM_PATH)/debug/simv
REGRESSION_PREBUILD += $(RACER_MACHINExPLATFORM_PATH)/profile/simv
REGRESSION_PREBUILD += $(RACER_MACHINExPLATFORM_PATH)/saifgen/simv
REGRESSION_PREBUILD += $(RACER_MACHINExPLATFORM_PATH)/pc-histogram/simv
REGRESSION_PREBUILD += $(RACER_PLATFORM_PATH)/libbsgmc_cuda_legacy_pod_repl.so
REGRESSION_PREBUILD += $(RACER_PLATFORM_PATH)/libRacEr_manycore_runtime.so
REGRESSION_PREBUILD += $(RACER_PLATFORM_PATH)/libRacEr_manycore_regression.so

.PHONY: platform.link.clean
platform.link.clean:
	rm -rf $(RACER_MACHINExPLATFORM_PATH)
	rm -rf ucli.key
	rm -rf .cxl* *.jou
	rm -rf *.daidir *.tmp
	rm -rf *.jou
	rm -rf *.vcs.log
	rm -rf vc_hdrs.h
	rm -rf *.debug *.profile *.saifgen *.exec

link.clean: platform.link.clean ;

