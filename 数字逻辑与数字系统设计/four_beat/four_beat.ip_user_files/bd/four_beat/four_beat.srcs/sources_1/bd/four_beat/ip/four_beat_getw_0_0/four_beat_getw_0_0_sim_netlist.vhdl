-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
-- Date        : Wed Oct 27 14:03:18 2021
-- Host        : LANGLANG running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               c:/Users/LANGLANG/Desktop/vivado/four_beat/four_beat.srcs/sources_1/bd/four_beat/ip/four_beat_getw_0_0/four_beat_getw_0_0_sim_netlist.vhdl
-- Design      : four_beat_getw_0_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7a35tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity four_beat_getw_0_0 is
  port (
    w0 : out STD_LOGIC;
    w1 : out STD_LOGIC;
    w2 : out STD_LOGIC;
    w3 : out STD_LOGIC;
    Q2 : in STD_LOGIC;
    Q1 : in STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of four_beat_getw_0_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of four_beat_getw_0_0 : entity is "four_beat_getw_0_0,getw,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of four_beat_getw_0_0 : entity is "yes";
  attribute IP_DEFINITION_SOURCE : string;
  attribute IP_DEFINITION_SOURCE of four_beat_getw_0_0 : entity is "module_ref";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of four_beat_getw_0_0 : entity is "getw,Vivado 2020.1";
end four_beat_getw_0_0;

architecture STRUCTURE of four_beat_getw_0_0 is
begin
w0_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => Q1,
      I1 => Q2,
      O => w0
    );
w1_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => Q1,
      I1 => Q2,
      O => w1
    );
w2_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => Q2,
      I1 => Q1,
      O => w2
    );
w3_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => Q2,
      I1 => Q1,
      O => w3
    );
end STRUCTURE;
