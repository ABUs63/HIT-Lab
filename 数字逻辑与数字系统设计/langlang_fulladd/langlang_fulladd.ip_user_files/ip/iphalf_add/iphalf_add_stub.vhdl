-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
-- Date        : Thu Oct 21 22:59:08 2021
-- Host        : LANGLANG running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/Users/LANGLANG/Desktop/vivado/langlang_fulladd/langlang_fulladd.srcs/sources_1/ip/iphalf_add/iphalf_add_stub.vhdl
-- Design      : iphalf_add
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7a35tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity iphalf_add is
  Port ( 
    a : in STD_LOGIC;
    b : in STD_LOGIC;
    c : out STD_LOGIC;
    d : out STD_LOGIC
  );

end iphalf_add;

architecture stub of iphalf_add is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "a,b,c,d";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "half_add,Vivado 2020.1";
begin
end;
