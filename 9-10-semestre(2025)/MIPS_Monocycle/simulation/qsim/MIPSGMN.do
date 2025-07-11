onerror {quit -f}
vlib work
vlog -work work MIPSGMN.vo
vlog -work work MIPSGMN.vt
vsim -novopt -c -t 1ps -L cycloneive_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.MIPSGMN_vlg_vec_tst
vcd file -direction MIPSGMN.msim.vcd
vcd add -internal MIPSGMN_vlg_vec_tst/*
vcd add -internal MIPSGMN_vlg_vec_tst/i1/*
add wave /*
run -all
