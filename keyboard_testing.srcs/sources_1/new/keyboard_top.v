// Simple PS/2 Debug for Zybo Z7-10
// Toggles LED0 when PS/2 clock has a falling edge
// Mirrors current PS/2 data line level onto LED1

module ps2_debug_top (
    input  wire clk,        // 125 MHz system clock
    input  wire reset,      // Active-high reset (BTN0)
    input  wire ps2_clk,    // PS/2 Clock from keyboard (JA1)
    input  wire ps2_data,   // PS/2 Data from keyboard (JA2)
    output reg  led_clk_seen,   // LED0 toggles on falling edge
    output reg  led_data_level  // LED1 shows data line level
);

    // Synchronizers to avoid metastability
    reg ps2_clk_sync, ps2_clk_prev;
    reg ps2_data_sync;

    always @(posedge clk) begin
        ps2_clk_sync  <= ps2_clk;
        ps2_clk_prev  <= ps2_clk_sync;
        ps2_data_sync <= ps2_data;
    end

    // Falling edge detect
    wire ps2_clk_falling = ps2_clk_prev & ~ps2_clk_sync;

    // LED logic
    always @(posedge clk) begin
        if (reset) begin
            led_clk_seen   <= 1'b0;
            led_data_level <= 1'b0;
        end else begin
            if (ps2_clk_falling)
                led_clk_seen <= ~led_clk_seen; // Toggle LED0
            led_data_level <= ps2_data_sync;   // LED1 shows current data level
        end
    end

endmodule
