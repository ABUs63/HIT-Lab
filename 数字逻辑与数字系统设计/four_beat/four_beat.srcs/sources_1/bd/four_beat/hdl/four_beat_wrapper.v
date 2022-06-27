//Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
//Date        : Wed Oct 27 14:16:45 2021
//Host        : LANGLANG running 64-bit major release  (build 9200)
//Command     : generate_target four_beat_wrapper.bd
//Design      : four_beat_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module four_beat_wrapper
   (RST,
    clk,
    w0,
    w1,
    w2,
    w3);
  input RST;
  input clk;
  output w0;
  output w1;
  output w2;
  output w3;

  wire RST;
  wire clk;
  wire w0;
  wire w1;
  wire w2;
  wire w3;

  four_beat four_beat_i
       (.RST(RST),
        .clk(clk),
        .w0(w0),
        .w1(w1),
        .w2(w2),
        .w3(w3));
endmodule
