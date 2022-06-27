############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project four_beat_hls
open_solution "solution1"
set_part {xc7a35tcsg324-1}
create_clock -period 10 -name default
#source "./four_beat_hls/solution1/directives.tcl"
#csim_design
csynth_design
#cosim_design
export_design -format ip_catalog
