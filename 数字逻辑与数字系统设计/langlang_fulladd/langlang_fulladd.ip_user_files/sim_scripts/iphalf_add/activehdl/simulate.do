onbreak {quit -force}
onerror {quit -force}

asim +access +r +m+iphalf_add -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip -O5 xil_defaultlib.iphalf_add xil_defaultlib.glbl

do {wave.do}

view wave
view structure

do {iphalf_add.udo}

run -all

endsim

quit -force
