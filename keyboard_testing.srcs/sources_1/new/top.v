module top(
    input wire clk,           // System clock (e.g., 100MHz on Zybo)
    input wire ja_p0,         // PS/2 clock
    input wire ja_p1,         // PS/2 data
    output reg [3:0] led      // LEDs: ON only for blink duration
);

    wire [7:0] sc;
    wire new_data;

    ps2_keyboard ps2 (
        .clk(clk),
        .ps2_clk(ja_p0),
        .ps2_data(ja_p1),
        .scancode(sc),
        .new_data(new_data)
    );

    // Blink timer logic
    reg [20:0] counter = 0;
    reg blink = 0;

    // Set blink duration (adjust for desired effect)
    parameter BLINK_CYCLES = 2000000; // ~20ms for 100MHz clock

    always @(posedge clk) begin
        if (new_data) begin
            counter <= BLINK_CYCLES;
            blink <= 1;
        end else if (counter > 0) begin
            counter <= counter - 1;
            blink <= 1;
        end else begin
            blink <= 0;
        end
    end

    always @(*) begin
        // Light all LEDs ON during blink, OFF otherwise.
        led = blink ? 4'b1111 : 4'b0000;
    end

endmodule
