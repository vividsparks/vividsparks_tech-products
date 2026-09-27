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

# hardware.mk: Platform-specific HDL listing.
#
# For simulation platforms, it also describes how to build the
# simulation "libraries" that are required by CAD tools.
#
# This file should HE included from RacEr_replicant/hardware/hardware.mk. It checks
# RACER_PLATFORM_PATH, BASEJUMP_STL_DIR, RACER_MANYCORE_DIR, etc.

# RACER_MACHINE_NAME: The name of the target machine. Should HE defined
# in $(RACER_MACHINE_PATH)/Makefile.machine.include, which is included
# by hardware.mk
ifndef RACER_MACHINE_NAME
$(error $(shell echo -e "$(RED)RACER MAKE ERROR: RACER_MACHINE_NAME is not defined$(NC)"))
endif

################################################################################
# Simulation Sources
################################################################################
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_test/RacEr_nonsynth_clock_gen.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_test/RacEr_nonsynth_reset_gen.sv

POD_TRACE_GEN_PY = $(RACER_MANYCORE_DIR)/testbenches/py/pod_trace_gen.py
$(RACER_MACHINE_PATH)/RacEr_tag_boot_rom.tr: $(RACER_MACHINE_PATH)/Makefile.machine.include
	env python2 $(POD_TRACE_GEN_PY) $(RACER_MACHINE_PODS_X) $(RACER_MACHINE_PODS_Y) $(RACER_MACHINE_NOC_COORD_X_WIDTH) > $@

ASCII_TO_ROM_PY = $(BASEJUMP_STL_DIR)/RacEr_mem/RacEr_ascii_to_rom.py
$(RACER_MACHINE_PATH)/RacEr_tag_boot_rom.sv: $(RACER_MACHINE_PATH)/RacEr_tag_boot_rom.tr
	env python2 $(ASCII_TO_ROM_PY) $< RacEr_tag_boot_rom > $@

VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_test/RacEr_trace_replay.sv
VSOURCES += $(RACER_MACHINE_PATH)/RacEr_tag_boot_rom.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_tag/RacEr_tag_trace_replay.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_tag/RacEr_tag_master.sv

# DMA Interface
VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/vcache_dma_to_dram_channel_map.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_mem/RacEr_nonsynth_mem_1r1w_sync_dma.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_mem/RacEr_nonsynth_mem_1r1w_sync_mask_write_byte_dma.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_mem/RacEr_nonsynth_mem_1rw_sync_mask_write_byte_dma.sv

# DRAMSim3
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_test/RacEr_dramsim3_pkg.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_test/RacEr_nonsynth_dramsim3.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_test/RacEr_nonsynth_dramsim3_map.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_test/RacEr_nonsynth_dramsim3_unmap.sv

VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_cache/RacEr_cache_to_test_dram.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_cache/RacEr_cache_to_test_dram_tx.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_cache/RacEr_cache_to_test_dram_rx.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_cache/RacEr_cache_to_test_dram_rx_reorder.sv

# Infinite Memory
VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/RacEr_nonsynth_mem_infinite.sv

# Profiling
VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/RacEr_manycore_profile_pkg.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_misc/RacEr_cycle_counter.sv

# Core Profiler/Trace
VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/vanilla_exe_bubble_classifier_pkg.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_test/RacEr_nonsynth_dpi_gpio.sv
VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/instr_trace.sv
VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/vanilla_core_trace.sv
VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/vanilla_core_profiler.sv
VSOURCES += $(HARDWARE_PATH)/RacEr_print_stat_snoop.sv

VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/router_profiler.sv
VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/remote_load_trace.sv

# Memory Profilers
VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/vcache_profiler.sv
VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/infinite_mem_profiler.sv

VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/RacEr_nonsynth_manycore_tag_master.sv
VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/RacEr_nonsynth_manycore_io_complex.sv
VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/RacEr_nonsynth_manycore_spmd_loader.sv
VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/RacEr_nonsynth_manycore_monitor.sv
VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/RacEr_nonsynth_wormhole_test_mem.sv
VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/RacEr_nonsynth_manycore_testbench.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_cache/RacEr_wormhole_to_cache_dma_fanout.sv

VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_dataflow/RacEr_serial_in_parallel_out_full.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_dataflow/RacEr_round_robin_1_to_n.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_dataflow/RacEr_one_fifo.sv

VSOURCES += $(HARDWARE_PATH)/RacEr_manycore_endpoint_to_fifos_pkg.sv
VSOURCES += $(HARDWARE_PATH)/RacEr_manycore_endpoint_to_fifos.sv

VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/common/v/vanilla_core_saif_dumper.sv

################################################################################
# DPI-Specific Sources
################################################################################

VSOURCES += $(RACER_MANYCORE_DIR)/v/RacEr_manycore_link_sif_async_buffer.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_test/RacEr_nonsynth_dpi_from_fifo.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_test/RacEr_nonsynth_dpi_to_fifo.sv
VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_test/RacEr_nonsynth_dpi_rom.sv
VSOURCES += $(RACER_MANYCORE_DIR)/testbenches/dpi/RacEr_nonsynth_dpi_manycore.sv

VSOURCES += $(BASEJUMP_STL_DIR)/RacEr_test/RacEr_nonsynth_dpi_cycle_counter.sv

################################################################################
# Top-level files
################################################################################
# Top-level module name
RACER_DESIGN_TOP := replicant_tb_top

VSOURCES += $(LIBRARIES_PATH)/platforms/common/dpi/hardware/dpi_top.sv

VINCLUDES += $(RACER_PLATFORM_PATH)/hardware
VINCLUDES += $(RACER_PLATFORM_PATH)


hardware.clean: machine.hardware.clean

machine.hardware.clean:
	rm -rf $(RACER_MACHINE_PATH)/RacEr_tag_boot_rom.tr $(RACER_MACHINE_PATH)/RacEr_tag_boot_rom.sv
