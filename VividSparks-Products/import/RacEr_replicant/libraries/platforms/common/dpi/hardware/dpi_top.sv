module replicant_tb_top
  import RacEr_manycore_pkg::*;
  import RacEr_bladerunner_pkg::*;
  ();

   // RACER_VERILATOR_WAVEFORM turns on waveform generation
`ifdef RACER_VERILATOR_WAVEFORM
   initial begin
    $display("[%0t] Tracing to debug.fst...\n", $time);
    $dumpfile("debug.fst");
    $dumpvars();
   end
`endif

   initial begin
`ifndef VERILATOR
      #0;
`endif
      
      $display("==================== RACER MACHINE SETTINGS: ====================");

      $display("[INFO][TESTBENCH] RacEr_machine_pods_cycle_time_ps_gp     = %d", RacEr_machine_pods_cycle_time_ps_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_pods_x_gp                 = %d", RacEr_machine_pods_x_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_pods_y_gp                 = %d", RacEr_machine_pods_y_gp);

      $display("[INFO][TESTBENCH] RacEr_machine_pod_tiles_x_gp            = %d", RacEr_machine_pod_tiles_x_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_pod_tiles_y_gp            = %d", RacEr_machine_pod_tiles_y_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_pod_tiles_subarray_x_gp   = %d", RacEr_machine_pod_tiles_subarray_x_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_pod_tiles_subarray_y_gp   = %d", RacEr_machine_pod_tiles_subarray_y_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_pod_llcache_rows_gp       = %d", RacEr_machine_pod_llcache_rows_gp);

      $display("[INFO][TESTBENCH] RacEr_machine_core_icache_line_words_gp = %d", RacEr_machine_core_icache_line_words_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_core_icache_entries_gp    = %d", RacEr_machine_core_icache_entries_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_core_icache_tag_width_gp  = %d", RacEr_machine_core_icache_tag_width_gp);

      $display("[INFO][TESTBENCH] RacEr_machine_noc_cfg_gp                = %s", RacEr_machine_noc_cfg_gp.name());
      $display("[INFO][TESTBENCH] RacEr_machine_noc_ruche_factor_X_gp     = %d", RacEr_machine_noc_ruche_factor_X_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_barrier_ruche_factor_X_gp = %d", RacEr_machine_barrier_ruche_factor_X_gp);

      $display("[INFO][TESTBENCH] RacEr_machine_noc_epa_width_gp          = %d", RacEr_machine_noc_epa_width_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_noc_data_width_gp         = %d", RacEr_machine_noc_data_width_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_noc_coord_x_width_gp      = %d", RacEr_machine_noc_coord_x_width_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_noc_coord_y_width_gp      = %d", RacEr_machine_noc_coord_y_width_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_noc_pod_coord_x_width_gp  = %d", RacEr_machine_noc_pod_coord_x_width_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_noc_pod_coord_y_width_gp  = %d", RacEr_machine_noc_pod_coord_y_width_gp);

      $display("[INFO][TESTBENCH] RacEr_machine_llcache_sets_gp           = %d", RacEr_machine_llcache_sets_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_llcache_ways_gp           = %d", RacEr_machine_llcache_ways_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_llcache_line_words_gp     = %d", RacEr_machine_llcache_line_words_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_llcache_words_gp          = %d", RacEr_machine_llcache_words_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_llcache_miss_fifo_els_gp  = %d", RacEr_machine_llcache_miss_fifo_els_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_llcache_channel_width_gp  = %d", RacEr_machine_llcache_channel_width_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_llcache_dram_channel_ratio_gp = %d", RacEr_machine_llcache_dram_channel_ratio_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_llcache_word_tracking_gp  = %d", RacEr_machine_llcache_word_tracking_gp);

      $display("[INFO][TESTBENCH] RacEr_machine_dram_bank_words_gp        = %d", RacEr_machine_dram_bank_words_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_dram_channels_gp          = %d", RacEr_machine_dram_channels_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_dram_words_gp             = %d", RacEr_machine_dram_words_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_dram_cfg_gp               = %s", RacEr_machine_dram_cfg_gp.name());

      $display("[INFO][TESTBENCH] RacEr_machine_io_coord_x_gp             = %d", RacEr_machine_io_coord_x_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_io_coord_y_gp             = %d", RacEr_machine_io_coord_y_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_origin_coord_y_gp         = %d", RacEr_machine_origin_coord_y_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_origin_coord_x_gp         = %d", RacEr_machine_origin_coord_x_gp);

      $display("[INFO][TESTBENCH] RacEr_machine_origin_coord_y_gp         = %d", RacEr_machine_origin_coord_y_gp);
      $display("[INFO][TESTBENCH] RacEr_machine_origin_coord_x_gp         = %d", RacEr_machine_origin_coord_x_gp);

      $display("[INFO][TESTBENCH] RacEr_machine_enable_vcore_profiling_lp = %d", RacEr_machine_enable_vcore_profiling_lp);
      $display("[INFO][TESTBENCH] RacEr_machine_enable_router_profiling_lp= %d", RacEr_machine_enable_router_profiling_lp);
      $display("[INFO][TESTBENCH] RacEr_machine_enable_cache_profiling_lp = %d", RacEr_machine_enable_cache_profiling_lp);
      $display("[INFO][TESTBENCH] RacEr_machine_enable_vcore_pc_histogram_lp = %d", RacEr_machine_enable_vcore_pc_histogram_lp);     
      $display("[INFO][TESTBENCH] RacEr_machine_enable_remote_op_profiling_lp = %d", RacEr_machine_enable_remote_op_profiling_lp);
      $display("[INFO][TESTBENCH] RacEr_machine_name_gp                   = %s", RacEr_machine_name_gp);
   end

   localparam RacEr_machine_llcache_data_width_lp = RacEr_machine_noc_data_width_gp;
   localparam RacEr_machine_llcache_addr_width_lp=(RacEr_machine_noc_epa_width_gp-1+`RACER_SAFE_CLOG2(RacEr_machine_noc_data_width_gp>>3));

   localparam RacEr_machine_wh_flit_width_lp = RacEr_machine_llcache_channel_width_gp;
   localparam RacEr_machine_wh_cid_width_lp = `RACER_SAFE_CLOG2(RacEr_machine_wh_ruche_factor_gp*2);
   localparam RacEr_machine_wh_len_width_lp = `RACER_SAFE_CLOG2(1 + ((RacEr_machine_llcache_line_words_gp * RacEr_machine_llcache_data_width_lp) / RacEr_machine_llcache_channel_width_gp));
   localparam RacEr_machine_wh_coord_width_lp = RacEr_machine_noc_coord_x_width_gp;

// These are macros... for reasons. 
`ifndef RACER_MACHINE_DISABLE_VCORE_PROFILING
   localparam RacEr_machine_enable_vcore_profiling_lp = 1;
`else
   localparam RacEr_machine_enable_vcore_profiling_lp = 0;
`endif

`ifndef RACER_MACHINE_DISABLE_ROUTER_PROFILING
   localparam RacEr_machine_enable_router_profiling_lp = 1;
`else
   localparam RacEr_machine_enable_router_profiling_lp = 0;
`endif

`ifndef RACER_MACHINE_DISABLE_CACHE_PROFILING
   localparam RacEr_machine_enable_cache_profiling_lp = 1;
`else
   localparam RacEr_machine_enable_cache_profiling_lp = 0;
`endif

`ifndef RACER_MACHINE_DISABLE_REMOTE_OP_PROFILING
   localparam RacEr_machine_enable_remote_op_profiling_lp = 1;
`else
   localparam RacEr_machine_enable_remote_op_profiling_lp = 0;
`endif

`ifndef RACER_MACHINE_DISABLE_VCORE_PC_HISTOGRAM
  localparam RacEr_machine_enable_vcore_pc_histogram_lp = 1;
`else
  localparam RacEr_machine_enable_vcore_pc_histogram_lp = 0;
`endif

   // Reset generator depth
   localparam reset_depth_lp = 3;

   // Global Counter for Profilers, Tracing, Debugging
   localparam global_counter_width_lp = 64;
   logic [global_counter_width_lp-1:0] global_ctr;

   logic host_clk;
   logic host_reset;

   // RacEr_nonsynth_clock_gen and RacEr_nonsynth_reset_gen BOTH have bit
   // inputs and outputs (they're non-synthesizable). Casting between
   // logic and bit can produce unexpected edges as logic types switch
   // from X to 0/1 at Time 0 in simulation. This means that the input
   // and outputs of both modules must have type bit, AND the wires
   // between them. Therefore, we use bit_clk and bit_reset for the
   // inputs/outputs of these modules to avoid unexpected
   // negative/positive edges and other modules can choose between bit
   // version (for non-synthesizable modules) and the logic version
   // (otherwise).
   bit   core_bit_clk;
   bit   core_bit_reset;
   logic core_clk;
   logic core_reset;

   // reset_done is deasserted when tag programming is done.
   logic core_reset_done_lo, core_reset_done_r;

   logic dram_clk;
   logic dram_reset;
   bit   dram_bit_clk;

   logic cache_clk;
   logic cache_reset;

   // Snoop wires for Print Stat
   logic                                       print_stat_v;
   logic [RacEr_machine_noc_data_width_gp-1:0]   print_stat_tag;

   logic [RacEr_machine_noc_coord_x_width_gp-1:0] host_x_coord_li = (RacEr_machine_noc_coord_x_width_gp)'(RacEr_machine_io_coord_x_gp);
   logic [RacEr_machine_noc_coord_y_width_gp-1:0] host_y_coord_li = (RacEr_machine_noc_coord_y_width_gp)'(RacEr_machine_io_coord_y_gp);

   `declare_RacEr_manycore_link_sif_s(RacEr_machine_noc_epa_width_gp, RacEr_machine_noc_data_width_gp, RacEr_machine_noc_coord_x_width_gp, RacEr_machine_noc_coord_y_width_gp);

   RacEr_manycore_link_sif_s host_link_sif_li;
   RacEr_manycore_link_sif_s host_link_sif_lo;

   // Trace Enable wire for runtime argument to enable tracing (+trace)
   logic                                        trace_en;
   logic                                        log_en;
   logic                                        dpi_trace_en;
   logic                                        dpi_log_en;
   logic                                        tag_done_lo;
   assign trace_en = dpi_trace_en;
   assign log_en = dpi_log_en;

   RacEr_nonsynth_clock_gen
     #(.cycle_time_p(RacEr_machine_pods_cycle_time_ps_gp))
   core_clk_gen
     (.o(core_bit_clk));
   assign core_clk = core_bit_clk;

   RacEr_nonsynth_clock_gen
`ifdef RACER_MACHINE_DRAMSIM3_PKG
  `define dram_pkg `RACER_MACHINE_DRAMSIM3_PKG
     #(.cycle_time_p(`dram_pkg::tck_ps))
 `else
     #(.cycle_time_p(RacEr_machine_pods_cycle_time_ps_gp))
 `endif
   dram_clk_gen
     (.o(dram_bit_clk));
   assign dram_clk = dram_bit_clk;

   RacEr_nonsynth_reset_gen
     #(
       .num_clocks_p(1)
       ,.reset_cycles_lo_p(0)
       ,.reset_cycles_hi_p(16)
       )
   reset_gen
     (
      .clk_i(core_bit_clk)
      ,.async_reset_o(core_bit_reset)
      );
   assign core_reset = core_bit_reset;

   RacEr_nonsynth_manycore_testbench
     #(
       .num_pods_x_p(RacEr_machine_pods_x_gp)
       ,.num_pods_y_p(RacEr_machine_pods_y_gp)
       ,.pod_x_cord_width_p(RacEr_machine_noc_pod_coord_x_width_gp)
       ,.pod_y_cord_width_p(RacEr_machine_noc_pod_coord_y_width_gp)

       ,.num_tiles_x_p(RacEr_machine_pod_tiles_x_gp)
       ,.num_tiles_y_p(RacEr_machine_pod_tiles_y_gp)
       ,.num_subarray_x_p(RacEr_machine_pod_tiles_subarray_x_gp)
       ,.num_subarray_y_p(RacEr_machine_pod_tiles_subarray_y_gp)

       ,.x_cord_width_p(RacEr_machine_noc_coord_x_width_gp)
       ,.y_cord_width_p(RacEr_machine_noc_coord_y_width_gp)

       ,.addr_width_p(RacEr_machine_noc_epa_width_gp)
       ,.data_width_p(RacEr_machine_noc_data_width_gp)
       ,.dmem_size_p(RacEr_machine_core_dmem_words_gp)
       ,.icache_block_size_in_words_p(RacEr_machine_core_icache_line_words_gp)
       ,.icache_entries_p(RacEr_machine_core_icache_entries_gp)
       ,.icache_tag_width_p(RacEr_machine_core_icache_tag_width_gp)

       ,.ruche_factor_X_p(RacEr_machine_noc_ruche_factor_X_gp)
       ,.barrier_ruche_factor_X_p(RacEr_machine_barrier_ruche_factor_X_gp)

       ,.num_vcache_rows_p(RacEr_machine_pod_llcache_rows_gp)
       ,.num_vcaches_per_channel_p(RacEr_machine_llcache_dram_channel_ratio_gp)
       ,.vcache_data_width_p(RacEr_machine_llcache_data_width_lp)
       ,.vcache_addr_width_p(RacEr_machine_llcache_addr_width_lp)
       ,.vcache_size_p(RacEr_machine_llcache_words_gp)
       ,.vcache_sets_p(RacEr_machine_llcache_sets_gp)
       ,.vcache_ways_p(RacEr_machine_llcache_ways_gp)
       ,.vcache_block_size_in_words_p(RacEr_machine_llcache_line_words_gp)
       ,.vcache_dma_data_width_p(RacEr_machine_llcache_channel_width_gp)
       ,.vcache_word_tracking_p(RacEr_machine_llcache_word_tracking_gp)
       ,.ipoly_hashing_p(RacEr_machine_llcache_ipoly_hashing_gp)

       ,.wh_flit_width_p(RacEr_machine_wh_flit_width_lp)
       ,.wh_ruche_factor_p(RacEr_machine_wh_ruche_factor_gp)
       ,.wh_cid_width_p(RacEr_machine_wh_cid_width_lp)
       ,.wh_len_width_p(RacEr_machine_wh_len_width_lp)
       ,.wh_cord_width_p(RacEr_machine_wh_coord_width_lp)

       ,.RacEr_manycore_mem_cfg_p(RacEr_machine_dram_cfg_gp)
       ,.RacEr_dram_size_p(RacEr_machine_dram_words_gp)

       ,.enable_vcore_profiling_p(RacEr_machine_enable_vcore_profiling_lp)
       ,.enable_router_profiling_p(RacEr_machine_enable_router_profiling_lp)
       ,.enable_cache_profiling_p(RacEr_machine_enable_cache_profiling_lp)
       ,.enable_remote_op_profiling_p(RacEr_machine_enable_remote_op_profiling_lp)
       ,.enable_vanilla_core_pc_histogram_p(RacEr_machine_enable_vcore_pc_histogram_lp)
       ,.hetero_type_vec_p(RacEr_machine_hetero_type_vec_gp)

       ,.reset_depth_p(reset_depth_lp)
       )
   testbench
     (
      .clk_i(core_clk)
      ,.dram_clk_i(dram_clk)
      ,.reset_i(core_reset)

      ,.io_link_sif_i(host_link_sif_li)
      ,.io_link_sif_o(host_link_sif_lo)

      ,.tag_done_o(core_reset_done_lo)
      );

   RacEr_nonsynth_dpi_gpio
     #(
       .width_p(2)
       ,.init_o_p('0)
       ,.use_output_p('1)
       ,.debug_p('1)
       )
   trace_control
     (.gpio_o({dpi_log_en, dpi_trace_en})
      ,.gpio_i('0)
      );

   // --------------------------------------------------------------------------
   // IO Complex
   // --------------------------------------------------------------------------
   localparam dpi_fifo_width_lp = (1 << $clog2(`RacEr_manycore_packet_width(RacEr_machine_noc_epa_width_gp,RacEr_machine_noc_data_width_gp,RacEr_machine_noc_coord_x_width_gp,RacEr_machine_noc_coord_y_width_gp)));
   localparam ep_fifo_els_lp = 4;
   assign host_clk = core_clk;
   assign host_reset = core_reset;

   RacEr_nonsynth_dpi_manycore
     #(
       .x_cord_width_p(RacEr_machine_noc_coord_x_width_gp)
       ,.y_cord_width_p(RacEr_machine_noc_coord_y_width_gp)
       ,.addr_width_p(RacEr_machine_noc_epa_width_gp)
       ,.data_width_p(RacEr_machine_noc_data_width_gp)
       ,.ep_fifo_els_p(ep_fifo_els_lp)
       ,.dpi_fifo_els_p(RacEr_machine_dpi_fifo_els_gp)
       ,.icache_block_size_in_words_p(RacEr_machine_core_icache_line_words_gp)
       ,.fifo_width_p(128) // It would HE better to read this from somewhere
       ,.rev_fifo_els_p(3) // Necessary for manycore correctness.
       ,.rom_els_p(RacEr_machine_rom_els_gp)
       ,.rom_width_p(RacEr_machine_rom_width_gp)
       ,.rom_arr_p(RacEr_machine_rom_arr_gp)
       ,.credit_counter_width_p(`RACER_WIDTH(RacEr_machine_io_credits_max_gp))
       )
   mc_dpi
     (
      .clk_i(host_clk)
      // DR: I don't particularly like this, but we'll leave it for now
      ,.reset_i(host_reset | (~core_reset_done_r))
      ,.reset_done_i(core_reset_done_lo)

      // manycore link
      ,.link_sif_i(host_link_sif_lo)
      ,.link_sif_o(host_link_sif_li)

      ,.global_y_i(host_y_coord_li)
      ,.global_x_i(host_x_coord_li)

      ,.debug_o()
      );

   RacEr_dff_chain
     #(
       .width_p(1)
       ,.num_stages_p(reset_depth_lp)
       )
   reset_dff
     (
      .clk_i(core_clk)
      ,.data_i(core_reset_done_lo)
      ,.data_o(core_reset_done_r)
      );

   RacEr_nonsynth_dpi_cycle_counter
     #(.width_p(global_counter_width_lp))
   ctr
     (
      .clk_i(core_clk)
      ,.reset_i(core_reset)
      ,.ctr_r_o(global_ctr)

      ,.debug_o()
      );

   RacEr_print_stat_snoop
     #(
       .data_width_p(RacEr_machine_noc_data_width_gp)
       ,.addr_width_p(RacEr_machine_noc_epa_width_gp)
       ,.x_cord_width_p(RacEr_machine_noc_coord_x_width_gp)
       ,.y_cord_width_p(RacEr_machine_noc_coord_y_width_gp)
       ,.enable_vcore_profiling_p(RacEr_machine_enable_vcore_profiling_lp)
       )
   print_stat_snoop
     (
      .clk_i(core_clk)
      ,.reset_i(core_reset)
      ,.global_ctr_i(global_ctr)

      ,.loader_link_sif_in_i(host_link_sif_lo) // output from manycore
      ,.loader_link_sif_out_i(host_link_sif_li) // output from host

      ,.print_stat_v_o(print_stat_v)
      ,.print_stat_tag_o(print_stat_tag)
      );

   // In VCS, the C/C++ testbench is controlled by the
   // simulator. Therefore, we need to "call into" the C/C++ program
   // using the cosim_main function, during the initial block.
   //
   // DPI Calls in cosim_main will cause simulator time to progress.
   //
   // This mirrors the DPI functions in aws simulation
`ifndef VERILATOR
   import "DPI-C" context task cosim_main(output int unsigned exit_code, input string args, input string path);
   initial begin
      int exit_code;
      string args;
      string path;
      longint t;
      $value$plusargs("c_path=%s", path);
      $value$plusargs("c_args=%s", args);
      replicant_tb_top.cosim_main(exit_code, args, path);
      if(exit_code < 0) begin
        $display("RACER COSIM FAIL: Test failed with exit code: %d", exit_code);
        $fatal;
      end else begin
        $display("RACER COSIM PASS: Test passed!");
        $finish;
      end
   end
`endif

`ifdef RACER_MACHINE_ENABLE_SAIF
   wor saif_en = 0;

   bind vanilla_core vanilla_core_saif_dumper
     #(
       )
   saif_dumper
   (
    .*
    ,.saif_en_i($root.`HOST_MODULE_PATH.saif_en)
    ,.saif_en_o($root.`HOST_MODULE_PATH.saif_en)
   );
`endif
endmodule
