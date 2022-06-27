-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
-- Date        : Wed Oct 27 14:03:22 2021
-- Host        : LANGLANG running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ four_beat_d_trigger_0_1_sim_netlist.vhdl
-- Design      : four_beat_d_trigger_0_1
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7a35tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_d_trigger is
  port (
    Q : out STD_LOGIC;
    D : in STD_LOGIC;
    clk : in STD_LOGIC;
    set : in STD_LOGIC;
    rst : in STD_LOGIC
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_d_trigger;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_d_trigger is
  signal Q_reg_C_n_0 : STD_LOGIC;
  signal Q_reg_LDC_i_1_n_0 : STD_LOGIC;
  signal Q_reg_LDC_i_2_n_0 : STD_LOGIC;
  signal Q_reg_LDC_n_0 : STD_LOGIC;
  signal Q_reg_P_n_0 : STD_LOGIC;
  attribute OPT_MODIFIED : string;
  attribute OPT_MODIFIED of Q_reg_LDC : label is "MLO";
  attribute XILINX_LEGACY_PRIM : string;
  attribute XILINX_LEGACY_PRIM of Q_reg_LDC : label is "LDC";
  attribute OPT_MODIFIED of Q_reg_P : label is "MLO";
begin
Q_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => Q_reg_P_n_0,
      I1 => Q_reg_LDC_n_0,
      I2 => Q_reg_C_n_0,
      O => Q
    );
Q_reg_C: unisim.vcomponents.FDCE
     port map (
      C => clk,
      CE => '1',
      CLR => Q_reg_LDC_i_2_n_0,
      D => D,
      Q => Q_reg_C_n_0
    );
Q_reg_LDC: unisim.vcomponents.LDCE
    generic map(
      INIT => '0',
      IS_G_INVERTED => '1'
    )
        port map (
      CLR => Q_reg_LDC_i_2_n_0,
      D => '1',
      G => set,
      GE => '1',
      Q => Q_reg_LDC_n_0
    );
Q_reg_LDC_i_1: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => set,
      O => Q_reg_LDC_i_1_n_0
    );
Q_reg_LDC_i_2: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => rst,
      O => Q_reg_LDC_i_2_n_0
    );
Q_reg_P: unisim.vcomponents.FDPE
     port map (
      C => clk,
      CE => '1',
      D => D,
      PRE => Q_reg_LDC_i_1_n_0,
      Q => Q_reg_P_n_0
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  port (
    Q : out STD_LOGIC;
    clk : in STD_LOGIC;
    rst : in STD_LOGIC;
    set : in STD_LOGIC;
    D : in STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "four_beat_d_trigger_0_1,d_trigger,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "yes";
  attribute IP_DEFINITION_SOURCE : string;
  attribute IP_DEFINITION_SOURCE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "package_project";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "d_trigger,Vivado 2020.1";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  attribute X_INTERFACE_INFO : string;
  attribute X_INTERFACE_INFO of clk : signal is "xilinx.com:signal:clock:1.0 clk CLK";
  attribute X_INTERFACE_PARAMETER : string;
  attribute X_INTERFACE_PARAMETER of clk : signal is "XIL_INTERFACENAME clk, ASSOCIATED_RESET rst, FREQ_HZ 10000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN four_beat_clk, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of rst : signal is "xilinx.com:signal:reset:1.0 rst RST";
  attribute X_INTERFACE_PARAMETER of rst : signal is "XIL_INTERFACENAME rst, POLARITY ACTIVE_HIGH, INSERT_VIP 0";
begin
inst: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_d_trigger
     port map (
      D => D,
      Q => Q,
      clk => clk,
      rst => rst,
      set => set
    );
end STRUCTURE;
