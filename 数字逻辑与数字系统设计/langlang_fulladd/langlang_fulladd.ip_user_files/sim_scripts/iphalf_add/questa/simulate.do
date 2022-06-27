onbreak {quit -f}
onerror {quit -f}

vsim -lib xil_defaultlib iphalf_add_opt

do {wave.do}

view wave
view structure
view signals

do {iphalf_add.udo}

run -all

quit -force
