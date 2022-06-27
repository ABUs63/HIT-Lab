// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
// Date        : Wed Oct 27 14:03:18 2021
// Host        : LANGLANG running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/Users/LANGLANG/Desktop/vivado/four_beat/four_beat.srcs/sources_1/bd/four_beat/ip/four_beat_getw_0_0/four_beat_getw_0_0_stub.v
// Design      : four_beat_getw_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a35tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "getw,Vivado 2020.1" *)
module four_beat_getw_0_0(w0, w1, w2, w3, Q2, Q1)
/* synthesis syn_black_box black_box_pad_pin="w0,w1,w2,w3,Q2,Q1" */;
  output w0;
  output w1;
  output w2;
  output w3;
  input Q2;
  input Q1;
endmodule
