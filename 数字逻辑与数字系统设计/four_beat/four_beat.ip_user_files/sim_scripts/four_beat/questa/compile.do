vlib questa_lib/work
vlib questa_lib/msim

vlib questa_lib/msim/xil_defaultlib

vmap xil_defaultlib questa_lib/msim/xil_defaultlib

vlog -work xil_defaultlib  \
"../../../../four_beat.srcs/sources_1/bd/four_beat/ip/four_beat_getXOR_0_0/sim/four_beat_getXOR_0_0.v" \
"../../../../four_beat.srcs/sources_1/bd/four_beat/ip/four_beat_getNOT_0_1/sim/four_beat_getNOT_0_1.v" \
"../../../../four_beat.srcs/sources_1/bd/four_beat/ip/four_beat_getw_0_0/sim/four_beat_getw_0_0.v" \
"../../../../four_beat.srcs/sources_1/bd/four_beat/sim/four_beat.v" \
"../../../../four_beat.srcs/sources_1/bd/four_beat/ip/four_beat_D_trigger_0_0/sim/four_beat_D_trigger_0_0.v" \
"../../../../four_beat.srcs/sources_1/bd/four_beat/ip/four_beat_D_trigger_2_0/sim/four_beat_D_trigger_2_0.v" \


vlog -work xil_defaultlib \
"glbl.v"

