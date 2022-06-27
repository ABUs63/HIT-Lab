//Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
//Date        : Wed Oct 27 14:16:45 2021
//Host        : LANGLANG running 64-bit major release  (build 9200)
//Command     : generate_target four_beat.bd
//Design      : four_beat
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "four_beat,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=four_beat,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=5,numReposBlks=5,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=5,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "four_beat.hwdef" *) 
module four_beat
   (RST,
    clk,
    w0,
    w1,
    w2,
    w3);
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 RST.RST RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME RST.RST, INSERT_VIP 0, POLARITY ACTIVE_HIGH" *) input RST;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK, ASSOCIATED_RESET RST, CLK_DOMAIN four_beat_clk, FREQ_HZ 10000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.000" *) input clk;
  output w0;
  output w1;
  output w2;
  output w3;

  wire D_trigger_0_Q;
  wire D_trigger_2_Q;
  wire RST_1;
  wire clk_1;
  wire getNOT_0_x;
  wire getXOR_0_x;
  wire getw_0_w0;
  wire getw_0_w1;
  wire getw_0_w2;
  wire getw_0_w3;

  assign RST_1 = RST;
  assign clk_1 = clk;
  assign w0 = getw_0_w0;
  assign w1 = getw_0_w1;
  assign w2 = getw_0_w2;
  assign w3 = getw_0_w3;
  four_beat_D_trigger_0_0 D_trigger_0
       (.D(getXOR_0_x),
        .Q(D_trigger_0_Q),
        .clk(clk_1),
        .rst(RST_1));
  four_beat_D_trigger_2_0 D_trigger_2
       (.D(getNOT_0_x),
        .Q(D_trigger_2_Q),
        .clk(clk_1),
        .rst(RST_1));
  four_beat_getNOT_0_1 getNOT_0
       (.x(getNOT_0_x),
        .y(D_trigger_2_Q));
  four_beat_getXOR_0_0 getXOR_0
       (.x(getXOR_0_x),
        .y1(D_trigger_2_Q),
        .y2(D_trigger_0_Q));
  four_beat_getw_0_0 getw_0
       (.Q1(D_trigger_2_Q),
        .Q2(D_trigger_0_Q),
        .w0(getw_0_w0),
        .w1(getw_0_w1),
        .w2(getw_0_w2),
        .w3(getw_0_w3));
endmodule
