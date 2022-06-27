// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
// Date        : Wed Oct 27 14:03:21 2021
// Host        : LANGLANG running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/Users/LANGLANG/Desktop/vivado/four_beat/four_beat.srcs/sources_1/bd/four_beat/ip/four_beat_getNOT_0_1/four_beat_getNOT_0_1_stub.v
// Design      : four_beat_getNOT_0_1
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a35tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "getNOT,Vivado 2020.1" *)
module four_beat_getNOT_0_1(x, y)
/* synthesis syn_black_box black_box_pad_pin="x,y" */;
  output x;
  input y;
endmodule
