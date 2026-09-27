`ifndef RACER_BLADERUNNER_PKG
`define RACER_BLADERUNNER_PKG

package RacEr_bladerunner_pkg;

import RacEr_manycore_pkg::*;
import RacEr_manycore_network_cfg_pkg::*;
import RacEr_manycore_mem_cfg_pkg::*;

parameter RacEr_machine_dpi_fifo_els_gp = 32;

parameter RacEr_machine_rom_width_gp = 32;
parameter RacEr_machine_rom_els_gp = 42;
parameter bit [RacEr_machine_rom_width_gp-1:0] RacEr_machine_rom_arr_gp [RacEr_machine_rom_els_gp-1:0] = '{32'b00000000000000000000000000000000, 32'b00000000000000000000000000000101, 32'b00000000000000000000000000011100, 32'b00000000000000000000000000011001, 32'b00000000000000000000000000001010, 32'b00000000000000000000000000000101, 32'b00000000000000000000000000000101, 32'b00000000000000000000000000000010, 32'b00000000000000000000000000000011, 32'b00000000000000000000000000001111, 32'b00100000000000000000000000000000, 32'b00000000000000000000000000000010, 32'b00110010010011010100001001001000, 32'b00010101110010100010000000100010, 32'b00000000000000000000000000000000, 32'b00000000000000000000000000100000, 32'b00000000000000000000000000100000, 32'b00000000000000000000000000100000, 32'b00000000000000000000000000001000, 32'b00000000000000000000000000001000, 32'b00000000000000000000000001000000, 32'b00000000000000000000000000000100, 32'b01000010110000001111111111101110, 32'b11111110111011011100101011111110, 32'b11011110101011011011111011101111, 32'b00000000000000000000000000000001, 32'b00000000000000000000000000000001, 32'b00000000000000000000000000000001, 32'b00000000000000000000000000000111, 32'b00000000000000000000000000000111, 32'b00000000000000000000000000000010, 32'b00000000000000000000000000000010, 32'b00000000000000000000000000000000, 32'b00000000000000000000000000000010, 32'b00000000000000000000000000000010, 32'b00000000000000000000000000000010, 32'b00000000000000000000000000000001, 32'b00000000000000000000000000000001, 32'b00000000000000000000000000100000, 32'b00000000000000000000000000011100, 32'b00000110000000110010000000100110, 32'b00000000000000000000000000000000};
parameter int RacEr_machine_pods_x_gp = 1;
parameter int RacEr_machine_pods_y_gp = 1;
parameter int RacEr_machine_pods_cycle_time_ps_gp = 666;

parameter int RacEr_machine_pod_tiles_y_gp = 2;
parameter int RacEr_machine_pod_tiles_x_gp = 2;
parameter int RacEr_machine_pod_llcache_rows_gp = 1;

parameter int RacEr_machine_pod_tiles_subarray_y_gp = 1;
parameter int RacEr_machine_pod_tiles_subarray_x_gp = 1;

parameter RacEr_manycore_network_cfg_e RacEr_machine_noc_cfg_gp = e_network_mesh;
parameter int RacEr_machine_noc_ruche_factor_X_gp = 1;
parameter int RacEr_machine_barrier_ruche_factor_X_gp = 1;
parameter int RacEr_machine_wh_ruche_factor_gp = 1;
parameter int RacEr_machine_noc_epa_width_gp = 28;
parameter int RacEr_machine_noc_data_width_gp = 32;
parameter int RacEr_machine_noc_coord_x_width_gp = 7;
parameter int RacEr_machine_noc_coord_y_width_gp = 7;
parameter int RacEr_machine_noc_pod_coord_x_width_gp = RacEr_machine_noc_coord_x_width_gp - $clog2(RacEr_machine_pod_tiles_x_gp);
parameter int RacEr_machine_noc_pod_coord_y_width_gp = RacEr_machine_noc_coord_y_width_gp - $clog2(RacEr_machine_pod_tiles_y_gp);

parameter int RacEr_machine_llcache_sets_gp = 64;
parameter int RacEr_machine_llcache_ways_gp = 4;
parameter int RacEr_machine_llcache_line_words_gp = 8;
parameter int RacEr_machine_llcache_words_gp = RacEr_machine_llcache_line_words_gp * RacEr_machine_llcache_ways_gp * RacEr_machine_llcache_sets_gp;
parameter int RacEr_machine_llcache_miss_fifo_els_gp = 32;
parameter int RacEr_machine_llcache_channel_width_gp = 32;
parameter int RacEr_machine_llcache_dram_channel_ratio_gp = 2;
parameter int RacEr_machine_llcache_word_tracking_gp = 0;
parameter int RacEr_machine_llcache_ipoly_hashing_gp = 0;

parameter int RacEr_machine_dram_bank_words_gp = 134217728;
parameter int RacEr_machine_dram_channels_gp = 2;
parameter int RacEr_machine_dram_words_gp = 536870912;
parameter RacEr_manycore_mem_cfg_e RacEr_machine_dram_cfg_gp = e_vcache_hbm2;

parameter bit RacEr_machine_branch_trace_en_gp = 0;

parameter int RacEr_machine_io_coord_y_gp = 0;
parameter int RacEr_machine_io_coord_x_gp = 2;
parameter int RacEr_machine_io_credits_max_gp = 32;

parameter int RacEr_machine_origin_coord_y_gp = 2;
parameter int RacEr_machine_origin_coord_x_gp = 2;

parameter int RacEr_machine_pod_num_cores_gp = RacEr_machine_pod_tiles_x_gp * RacEr_machine_pod_tiles_y_gp;
parameter int RacEr_machine_hetero_type_vec_gp [0:(RacEr_machine_pod_num_cores_gp)-1] = '{default:0};

parameter RacEr_machine_core_dmem_words_gp = 1024;
parameter RacEr_machine_core_icache_entries_gp = 1024;
parameter RacEr_machine_core_icache_tag_width_gp = 12;
parameter RacEr_machine_core_icache_line_words_gp = 4;

parameter string RacEr_machine_name_gp = "RACER_PX1PY1_DX2DY2_vcache_hbm2";

endpackage

`endif
