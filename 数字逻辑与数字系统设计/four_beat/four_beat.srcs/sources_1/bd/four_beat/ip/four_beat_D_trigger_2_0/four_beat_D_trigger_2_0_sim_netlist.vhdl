-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
-- Date        : Wed Oct 27 14:17:58 2021
-- Host        : LANGLANG running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               c:/Users/LANGLANG/Desktop/vivado/four_beat/four_beat.srcs/sources_1/bd/four_beat/ip/four_beat_D_trigger_2_0/four_beat_D_trigger_2_0_sim_netlist.vhdl
-- Design      : four_beat_D_trigger_2_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7a35tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity four_beat_D_trigger_2_0_D_trigger is
  port (
    Q : out STD_LOGIC;
    D : in STD_LOGIC;
    clk : in STD_LOGIC;
    rst : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of four_beat_D_trigger_2_0_D_trigger : entity is "D_trigger";
end four_beat_D_trigger_2_0_D_trigger;

architecture STRUCTURE of four_beat_D_trigger_2_0_D_trigger is
  signal Q_i_1_n_0 : STD_LOGIC;
begin
Q_i_1: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => rst,
      O => Q_i_1_n_0
    );
Q_reg: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => '1',
      CLR => Q_i_1_n_0,
      D => D,
      Q => Q
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity four_beat_D_trigger_2_0 is
  port (
    Q : out STD_LOGIC;
    clk : in STD_LOGIC;
    rst : in STD_LOGIC;
    D : in STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of four_beat_D_trigger_2_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of four_beat_D_trigger_2_0 : entity is "four_beat_D_trigger_2_0,D_trigger,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of four_beat_D_trigger_2_0 : entity is "yes";
  attribute IP_DEFINITION_SOURCE : string;
  attribute IP_DEFINITION_SOURCE of four_beat_D_trigger_2_0 : entity is "module_ref";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of four_beat_D_trigger_2_0 : entity is "D_trigger,Vivado 2020.1";
end four_beat_D_trigger_2_0;

architecture STRUCTURE of four_beat_D_trigger_2_0 is
  attribute X_INTERFACE_INFO : string;
  attribute X_INTERFACE_INFO of clk : signal is "xilinx.com:signal:clock:1.0 clk CLK";
  attribute X_INTERFACE_PARAMETER : string;
  attribute X_INTERFACE_PARAMETER of clk : signal is "XIL_INTERFACENAME clk, ASSOCIATED_RESET rst, FREQ_HZ 10000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN four_beat_clk, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of rst : signal is "xilinx.com:signal:reset:1.0 rst RST";
  attribute X_INTERFACE_PARAMETER of rst : signal is "XIL_INTERFACENAME rst, POLARITY ACTIVE_HIGH, INSERT_VIP 0";
begin
inst: entity work.four_beat_D_trigger_2_0_D_trigger
     port map (
      D => D,
      Q => Q,
      clk => clk,
      rst => rst
    );
end STRUCTURE;
