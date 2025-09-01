module vga_csd(
    input wire clk,           // 100MHz clock
    input wire reset,         // Active high reset
    output reg [3:0] vga_r,
    output reg [3:0] vga_g,
    output reg [3:0] vga_b,
    output reg vga_hsync,
    output reg vga_vsync
);

    // VGA 640x480 @ 60Hz params
    parameter H_DISPLAY = 640;
    parameter H_FRONT   = 16;
    parameter H_SYNC    = 96;
    parameter H_BACK    = 48;
    parameter H_TOTAL   = 800;

    parameter V_DISPLAY = 480;
    parameter V_FRONT   = 10;
    parameter V_SYNC    = 2;
    parameter V_BACK    = 33;
    parameter V_TOTAL   = 525;

    // Clock divider: 100 MHz → 25 MHz
    reg [1:0] clk_div = 0;
    wire pixel_clk = clk_div[1];
    always @(posedge clk) clk_div <= clk_div + 1;

    // Counters
    reg [9:0] h_count = 0;
    reg [9:0] v_count = 0;

    always @(posedge pixel_clk) begin
        if (reset) begin
            h_count <= 0;
            v_count <= 0;
        end else begin
            if (h_count == H_TOTAL-1) begin
                h_count <= 0;
                if (v_count == V_TOTAL-1)
                    v_count <= 0;
                else
                    v_count <= v_count + 1;
            end else begin
                h_count <= h_count + 1;
            end
        end
    end

    // Sync signals
    always @(posedge pixel_clk) begin
        vga_hsync <= ~((h_count >= H_DISPLAY + H_FRONT) && 
                      (h_count < H_DISPLAY + H_FRONT + H_SYNC));
        vga_vsync <= ~((v_count >= V_DISPLAY + V_FRONT) && 
                      (v_count < V_DISPLAY + V_FRONT + V_SYNC));
    end

    // Display enable
    wire display_enable = (h_count < H_DISPLAY) && (v_count < V_DISPLAY);

    // Divide screen into 80x60 grid
    wire [6:0] grid_x = h_count / 8; // 0..79
    wire [5:0] grid_y = v_count / 8; // 0..59

    // Character ROM: define "CSD"
    reg pixel_on;
    always @(*) begin
        pixel_on = 0;
        if (display_enable) begin
            // "C" at columns 10..19, rows 20..40
            if (grid_x >= 25 && grid_x <= 34 && grid_y >= 20 && grid_y <= 40) begin
                if (grid_x == 25 || grid_y == 20 || grid_y == 40)
                    pixel_on = 1;
            end
            // "S" at columns 25..34
            if (grid_x >= 40 && grid_x <= 49 && grid_y >= 20 && grid_y <= 40) begin
                if (grid_y == 20 || grid_y == 30 || grid_y == 40 ||
                    (grid_x == 40 && grid_y < 30) ||
                    (grid_x == 49 && grid_y > 30))
                    pixel_on = 1;
            end
      
        end
    end

    // Assign colors
    always @(posedge pixel_clk) begin
        if (pixel_on) begin
            vga_r <= 4'hF;
            vga_g <= 4'hF;
            vga_b <= 4'hF;
        end else begin
            vga_r <= 4'h0;
            vga_g <= 4'h0;
            vga_b <= 4'h0;
        end
    end

endmodule
