module ps2_keyboard(
    input wire clk,             // FPGA system clock (e.g. 100MHz on Zybo)
    input wire ps2_clk,         // PS/2 clock from keyboard
    input wire ps2_data,        // PS/2 data from keyboard
    output reg [7:0] scancode,  // Last received scan code
    output reg new_data         // High for one sys_clk when new data valid
);

    reg [3:0] bitcount = 0;
    reg [10:0] shiftreg = 0; // 1 start + 8 data + 1 parity + 1 stop
    reg ps2_clk_sync, ps2_clk_prev;

    // Synchronize PS2 clock domain to system clock
    always @(posedge clk) begin
        ps2_clk_sync <= ps2_clk;
        ps2_clk_prev <= ps2_clk_sync;
    end

    // Detect falling edge of PS/2 clock
    wire ps2_clk_falling = (ps2_clk_prev == 1'b1 && ps2_clk_sync == 1'b0);

    always @(posedge clk) begin
        new_data <= 0;

        if (ps2_clk_falling) begin
            shiftreg <= {ps2_data, shiftreg[10:1]};
            bitcount <= bitcount + 1;

            if (bitcount == 10) begin
                // Finished receiving 11 bits
                bitcount <= 0;
                scancode <= shiftreg[8:1]; // extract 8-bit data
                new_data <= 1; // Signal new byte received
            end
        end
    end
endmodule
