module memory_vga_top(
    input wire clk,           // 100MHz clock from board
    input wire reset,         // Reset button
    output wire [3:0] vga_r,
    output wire [3:0] vga_g,
    output wire [3:0] vga_b,
    output wire vga_hsync,
    output wire vga_vsync,
    output wire [3:0] led     // LEDs for debugging
);

// VGA timing parameters for 640x480 @ 60Hz
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

// Clock divider: 100MHz to 25MHz for VGA pixel clock
reg [1:0] clk_div = 0;
wire pixel_clk = clk_div[1];
always @(posedge clk) 
    clk_div <= clk_div + 1;

// VGA counters
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

// Sync signals (negative polarity for VGA)
assign vga_hsync = ~((h_count >= H_DISPLAY + H_FRONT) && 
                    (h_count < H_DISPLAY + H_FRONT + H_SYNC));
assign vga_vsync = ~((v_count >= V_DISPLAY + V_FRONT) && 
                    (v_count < V_DISPLAY + V_FRONT + V_SYNC));

// Display enable signal
wire display_enable = (h_count < H_DISPLAY) && (v_count < V_DISPLAY);

// Instruction memory instance
wire [31:0] instruction;
reg [31:0] mem_address = 0;

instruction_memory imem (
    .clk(clk),
    .address(mem_address),
    .instruction(instruction)
);

// Memory address counter - cycles through first 16 memory locations
reg [23:0] addr_counter = 0;
reg [3:0] current_addr = 0;

always @(posedge clk) begin
    if (reset) begin
        addr_counter <= 0;
        current_addr <= 0;
    end else begin
        addr_counter <= addr_counter + 1;
        // Change address every ~167ms (100MHz / 2^24 ≈ 6Hz)
        if (addr_counter == 0) begin
            current_addr <= current_addr + 1;
            mem_address <= {28'b0, current_addr};
        end
    end
end

// Create 8x8 character grid for display (80x60 chars on 640x480)
wire [6:0] char_x = h_count[9:3];  // h_count / 8
wire [5:0] char_y = v_count[9:3];  // v_count / 8
wire [2:0] pixel_x = h_count[2:0]; // h_count % 8
wire [2:0] pixel_y = v_count[2:0]; // v_count % 8

// Display memory contents as hexadecimal
reg pixel_on;
reg [3:0] hex_digit;

// Extract hex digit based on position
always @(*) begin
    case(char_x)
        // Display "MEM:" at positions 10-13
        7'd10: hex_digit = 4'hD; // 'M'
        7'd11: hex_digit = 4'hE; // 'E' 
        7'd12: hex_digit = 4'hD; // 'M'
        7'd13: hex_digit = 4'hF; // ':'
        
        // Display address in hex at positions 15-16
        7'd15: hex_digit = current_addr[3:0];
        
        // Display "=" at position 18
        7'd18: hex_digit = 4'hF; // '='
        
        // Display instruction value in hex at positions 20-27
        7'd20: hex_digit = instruction[31:28];
        7'd21: hex_digit = instruction[27:24];
        7'd22: hex_digit = instruction[23:20];
        7'd23: hex_digit = instruction[19:16];
        7'd24: hex_digit = instruction[15:12];
        7'd25: hex_digit = instruction[11:8];
        7'd26: hex_digit = instruction[7:4];
        7'd27: hex_digit = instruction[3:0];
        
        default: hex_digit = 4'h0;
    endcase
end

// Simple 8x8 hex character patterns (simplified)
always @(*) begin
    pixel_on = 0;
    if (display_enable && char_y >= 20 && char_y <= 25) begin
        case(hex_digit)
            4'h0: // '0'
                if ((pixel_x == 0 || pixel_x == 7) && pixel_y >= 1 && pixel_y <= 6 ||
                    (pixel_y == 0 || pixel_y == 7) && pixel_x >= 1 && pixel_x <= 6)
                    pixel_on = 1;
            4'h1: // '1'
                if (pixel_x == 4 || (pixel_y == 7 && pixel_x >= 2 && pixel_x <= 6))
                    pixel_on = 1;
            4'h2: // '2'
                if ((pixel_y == 0 || pixel_y == 3 || pixel_y == 7) ||
                    (pixel_x == 7 && pixel_y <= 3) || (pixel_x == 0 && pixel_y >= 3))
                    pixel_on = 1;
            4'h3: // '3'
                if ((pixel_y == 0 || pixel_y == 3 || pixel_y == 7) ||
                    (pixel_x == 7 && (pixel_y <= 3 || pixel_y >= 3)))
                    pixel_on = 1;
            4'h4: // '4'
                if ((pixel_x == 0 && pixel_y <= 3) || pixel_y == 3 || 
                    (pixel_x == 7))
                    pixel_on = 1;
            4'h5: // '5'
                if ((pixel_y == 0 || pixel_y == 3 || pixel_y == 7) ||
                    (pixel_x == 0 && pixel_y <= 3) || (pixel_x == 7 && pixel_y >= 3))
                    pixel_on = 1;
            4'h6: // '6'
                if ((pixel_y == 0 || pixel_y == 3 || pixel_y == 7) ||
                    (pixel_x == 0) || (pixel_x == 7 && pixel_y >= 3))
                    pixel_on = 1;
            4'h7: // '7'
                if (pixel_y == 0 || pixel_x == 7)
                    pixel_on = 1;
            4'h8: // '8'
                if ((pixel_y == 0 || pixel_y == 3 || pixel_y == 7) ||
                    (pixel_x == 0 || pixel_x == 7))
                    pixel_on = 1;
            4'h9: // '9'
                if ((pixel_y == 0 || pixel_y == 3 || pixel_y == 7) ||
                    (pixel_x == 7) || (pixel_x == 0 && pixel_y <= 3))
                    pixel_on = 1;
            4'hA: // 'A'
                if ((pixel_y == 0 || pixel_y == 3) ||
                    ((pixel_x == 0 || pixel_x == 7) && pixel_y >= 1))
                    pixel_on = 1;
            4'hB: // 'B'
                if ((pixel_y == 0 || pixel_y == 3 || pixel_y == 7) ||
                    (pixel_x == 0) || (pixel_x == 7 && (pixel_y == 1 || pixel_y == 2 || pixel_y == 5 || pixel_y == 6)))
                    pixel_on = 1;
            4'hC: // 'C'
                if ((pixel_x == 0 && pixel_y >= 1 && pixel_y <= 6) ||
                    ((pixel_y == 0 || pixel_y == 7) && pixel_x >= 1 && pixel_x <= 6))
                    pixel_on = 1;
            4'hD: // 'D' or 'M' for MEM
                if (char_x == 10 || char_x == 12) begin // 'M'
                    if ((pixel_x == 0 || pixel_x == 7) || 
                        (pixel_y == 0 && pixel_x >= 2 && pixel_x <= 5) ||
                        (pixel_x == 3 && pixel_y >= 1 && pixel_y <= 3))
                        pixel_on = 1;
                end else begin // 'D'
                    if ((pixel_y == 0 || pixel_y == 7) ||
                        (pixel_x == 0) || (pixel_x == 7 && pixel_y >= 1 && pixel_y <= 6))
                        pixel_on = 1;
                end
            4'hE: // 'E'
                if ((pixel_y == 0 || pixel_y == 3 || pixel_y == 7) ||
                    (pixel_x == 0))
                    pixel_on = 1;
            4'hF: // 'F' or special chars
                if (char_x == 13) begin // ':'
                    if ((pixel_y == 2 || pixel_y == 5) && pixel_x == 3)
                        pixel_on = 1;
                end else if (char_x == 18) begin // '='
                    if ((pixel_y == 2 || pixel_y == 5) && pixel_x >= 1 && pixel_x <= 6)
                        pixel_on = 1;
                end else begin // 'F'
                    if ((pixel_y == 0 || pixel_y == 3) || (pixel_x == 0))
                        pixel_on = 1;
                end
        endcase
    end
end

// Color assignment
assign vga_r = display_enable && pixel_on ? 4'hF : 4'h0;
assign vga_g = display_enable && pixel_on ? 4'hF : 4'h0;
assign vga_b = display_enable && pixel_on ? 4'hF : 4'h0;

// LED indicators for debugging
assign led[0] = current_addr[0];
assign led[1] = current_addr[1];
assign led[2] = current_addr[2];
assign led[3] = current_addr[3];

endmodule