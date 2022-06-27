vlib modelsim_lib/work
vlib modelsim_lib/msim

vlib modelsim_lib/msim/xil_defaultlib

vmap xil_defaultlib modelsim_lib/msim/xil_defaultlib

vlog -work xil_defaultlib  -incr \
"../../../../langlang_fulladd.srcs/sources_1/ip/iphalf_add/sources_1/new/half_add.v" \
"../../../../langlang_fulladd.srcs/sources_1/ip/iphalf_add/sim/iphalf_add.v" \


vlog -work xil_defaultlib \
"glbl.v"

