## Assign JA1 as PS/2 Clock
set_property -dict { PACKAGE_PIN N15   IOSTANDARD LVCMOS33 } [get_ports { ja_p0 }];

## Assign JA2 as PS/2 Data
set_property -dict { PACKAGE_PIN L14   IOSTANDARD LVCMOS33 } [get_ports { ja_p1 }];

## System clock (100 MHz onboard)
set_property -dict { PACKAGE_PIN L16   IOSTANDARD LVCMOS33 } [get_ports { clk }];
create_clock -add -name sys_clk_pin -period 10.00 -waveform {0 5} [get_ports { clk }];

## LEDs
set_property -dict { PACKAGE_PIN M14   IOSTANDARD LVCMOS33 } [get_ports { led[0] }];
set_property -dict { PACKAGE_PIN M15   IOSTANDARD LVCMOS33 } [get_ports { led[1] }];
set_property -dict { PACKAGE_PIN G14   IOSTANDARD LVCMOS33 } [get_ports { led[2] }];
set_property -dict { PACKAGE_PIN D18   IOSTANDARD LVCMOS33 } [get_ports { led[3] }];
