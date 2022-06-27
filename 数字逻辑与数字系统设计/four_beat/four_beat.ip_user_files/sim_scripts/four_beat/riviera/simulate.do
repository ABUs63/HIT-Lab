onbreak {quit -force}
onerror {quit -force}

asim +access +r +m+four_beat -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip -O5 xil_defaultlib.four_beat xil_defaultlib.glbl

do {wave.do}

view wave
view structure

do {four_beat.udo}

run -all

endsim

quit -force
