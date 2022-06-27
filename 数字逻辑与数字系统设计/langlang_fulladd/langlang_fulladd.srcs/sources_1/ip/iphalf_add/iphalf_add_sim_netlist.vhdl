-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
-- Date        : Thu Oct 21 22:59:08 2021
-- Host        : LANGLANG running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               c:/Users/LANGLANG/Desktop/vivado/langlang_fulladd/langlang_fulladd.srcs/sources_1/ip/iphalf_add/iphalf_add_sim_netlist.vhdl
-- Design      : iphalf_add
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7a35tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity iphalf_add_half_add is
  port (
    a : in STD_LOGIC;
    b : in STD_LOGIC;
    c : out STD_LOGIC;
    d : out STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of iphalf_add_half_add : entity is "half_add";
end iphalf_add_half_add;

architecture STRUCTURE of iphalf_add_half_add is
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of c_INST_0 : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of d_INST_0 : label is "soft_lutpair0";
begin
c_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => b,
      I1 => a,
      O => c
    );
d_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => a,
      I1 => b,
      O => d
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity iphalf_add is
  port (
    a : in STD_LOGIC;
    b : in STD_LOGIC;
    c : out STD_LOGIC;
    d : out STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of iphalf_add : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of iphalf_add : entity is "iphalf_add,half_add,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of iphalf_add : entity is "yes";
  attribute IP_DEFINITION_SOURCE : string;
  attribute IP_DEFINITION_SOURCE of iphalf_add : entity is "package_project";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of iphalf_add : entity is "half_add,Vivado 2020.1";
end iphalf_add;

architecture STRUCTURE of iphalf_add is
begin
inst: entity work.iphalf_add_half_add
     port map (
      a => a,
      b => b,
      c => c,
      d => d
    );
end STRUCTURE;
