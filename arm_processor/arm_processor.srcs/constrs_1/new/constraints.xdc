# Clock constraint for Zybo-Z7 (125 MHz)
create_clock -period 8.000 [get_ports clk]

# Reset constraint
set_property PACKAGE_PIN K17 [get_ports reset]
set_property IOSTANDARD LVCMOS33 [get_ports reset]

# LED outputs for debugging (optional)
set_property PACKAGE_PIN M14 [get_ports pc_current[0]]
set_property IOSTANDARD LVCMOS33 [get_ports pc_current[0]]