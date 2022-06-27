-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
-- Date        : Wed Oct 27 14:03:18 2021
-- Host        : LANGLANG running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/Users/LANGLANG/Desktop/vivado/four_beat/four_beat.srcs/sources_1/bd/four_beat/ip/four_beat_getw_0_0/four_beat_getw_0_0_stub.vhdl
-- Design      : four_beat_getw_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7a35tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity four_beat_getw_0_0 is
  Port ( 
    w0 : out STD_LOGIC;
    w1 : out STD_LOGIC;
    w2 : out STD_LOGIC;
    w3 : out STD_LOGIC;
    Q2 : in STD_LOGIC;
    Q1 : in STD_LOGIC
  );

end four_beat_getw_0_0;

architecture stub of four_beat_getw_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "w0,w1,w2,w3,Q2,Q1";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "getw,Vivado 2020.1";
begin
end;
