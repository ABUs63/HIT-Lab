vlib work
vlib activehdl

vlib activehdl/xil_defaultlib

vmap xil_defaultlib activehdl/xil_defaultlib

vlog -work xil_defaultlib  -v2k5 \
"../../../../langlang_fulladd.srcs/sources_1/ip/iphalf_add/sources_1/new/half_add.v" \
"../../../../langlang_fulladd.srcs/sources_1/ip/iphalf_add/sim/iphalf_add.v" \


vlog -work xil_defaultlib \
"glbl.v"

