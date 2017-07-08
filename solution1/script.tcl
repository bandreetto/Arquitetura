############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Arquitetura
set_top sha_init
add_files Arq-2-SHA/sha.cpp
add_files Arq-2-SHA/sha.h
add_files Arq-2-SHA/sha_sysc.cpp
add_files Arq-2-SHA/sha_sysc.h
add_files -tb Arquitetura/sha_driver.cpp
open_solution "solution1"
set_part {xcku5p-ffvb676-2-e}
create_clock -period 2 -name default
#source "./Arquitetura/solution1/directives.tcl"
csim_design -argv {input_large.asc > output_large.txt}
csynth_design
cosim_design
export_design -format ip_catalog
