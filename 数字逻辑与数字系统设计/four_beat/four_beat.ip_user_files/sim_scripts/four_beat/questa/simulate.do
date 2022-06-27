onbreak {quit -f}
onerror {quit -f}

vsim -lib xil_defaultlib four_beat_opt

do {wave.do}

view wave
view structure
view signals

do {four_beat.udo}

run -all

quit -force
