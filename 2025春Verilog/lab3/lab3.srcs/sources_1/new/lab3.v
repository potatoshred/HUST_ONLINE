`timescale 1ns / 1ps


module divider(clk, clk_N);
    input wire clk;                      // 系统时钟
    output clk_N;                   // 分频后的时钟
    parameter N = 4_000_000;      // 1Hz的时钟,N=fclk/fclk_N
    reg [31:0] counter;             /* 计数器变量，通过计数实现分频。
                                       当计数器从0计数到(N/2-1)时，
                                       输出时钟翻转，计数器清零 */
    reg flag = 0;
    assign clk_N = flag;
    
    always @(posedge clk)  begin    // 时钟上升沿
                                  // 功能实现
        if(counter == (N/2-1)) begin
            flag <= ~flag; 
            counter <= 0;
        end
        else 
            counter <= counter + 1;
        
    end
endmodule

module counter(clk, out);
    input clk;                    // 计数时钟
    output reg [2:0] out;             // 计数值

    always @(posedge clk)  begin  // 在时钟上升沿计数器加1
        out <= out + 1;        // 在时钟上升沿计数器加1
    end                           
endmodule

module decrease(clk, out);
    input clk;                    // 计数时钟
    output reg [2:0] out;             // 计数值

    always @(posedge clk)  begin  // 在时钟上升沿计数器加1
        out <= out - 1;        // 在时钟上升沿计数器加1
    end                           
endmodule

module counter2(clk, out);
    input clk;                    // 计数时钟
    output [2:0] out;             // 计数值
    
    wire clk2;
    divider divider1(.clk(clk), .clk_N(clk2));
    
    wire [2:0] count_out;
    counter counter1 (.clk(clk2), .out(count_out));

    assign out = count_out;

endmodule

module rom8x4(addr,
              data);
    input [2:0] addr;           
    output reg [3:0] data;          
    
    reg [3: 0] mem [7: 0];      
    
    initial begin
        mem[0] = 4'h0;
        mem[1] = 4'h2;
        mem[2] = 4'h4;
        mem[3] = 4'h6;
        mem[4] = 4'h8;
        mem[5] = 4'hA;
        mem[6] = 4'hC;
        mem[7] = 4'hE;
    end

    always @(addr[2:0]) begin
        data = mem[addr[2:0]];
    end

endmodule

module decoder3_8(num, sel);
    input [2: 0] num;
    output [7:0] sel;

    reg [7:0] SEG_w;
    assign sel = SEG_w; 

    always @(num[2:0]) begin
        case(num[2:0])
            3'h0:SEG_w     = 8'b11111110;
            3'h1:SEG_w     = 8'b11111101;
            3'h2:SEG_w     = 8'b11111011;
            3'h3:SEG_w     = 8'b11110111;
            3'h4:SEG_w     = 8'b11101111;
            3'h5:SEG_w     = 8'b11011111;
            3'h6:SEG_w     = 8'b10111111;
            default :SEG_w = 8'b01111111;
        endcase
	end
endmodule
    
module pattern(code, patt);
    input [3: 0] code;
    output [7:0] patt;

    reg [7:0] SEG_w;
    assign patt = SEG_w; 
	always @(code[3:0]) begin
        case(code[3:0])
            4'h0:SEG_w     = 8'b11000000;
            4'h1:SEG_w     = 8'b11111001;
            4'h2:SEG_w     = 8'b10100100;
            4'h3:SEG_w     = 8'b10110000;
            4'h4:SEG_w     = 8'b10011001;
            4'h5:SEG_w     = 8'b10010010;
            4'h6:SEG_w     = 8'b10000010;
            4'h7:SEG_w     = 8'b11111000;
            4'h8:SEG_w     = 8'b10000000;
            4'h9:SEG_w     = 8'b10011000;
            4'hA:SEG_w     = 8'b10001000;
            4'hB:SEG_w     = 8'b10000011;
            4'hC:SEG_w     = 8'b11000110;
            4'hD:SEG_w     = 8'b10100001;
            4'hE:SEG_w     = 8'b10000110;
            default :SEG_w = 8'b10001110;
        endcase
	end
    
endmodule

module dynamic_scan(clk,
                     SEG,
                     AN);
    input clk;
    output [7:0] SEG;
    output [7:0] AN;

    
    wire clk2;
    divider #(200000) Divider(.clk(clk), .clk_N(clk2));

    wire [2:0]num;
    counter Counter(.clk(clk2), .out(num));

    decoder3_8 Decoder3_8(.num(num), .sel(AN));

    wire [3:0] data;
    rom8x4 Rom8x4(.addr(num), .data(data));
    pattern Pattern(.code(data), .patt(SEG));

endmodule


module dynamic_scan2(clk,
                     dir,
                     SEG,
                     AN);
    input clk;
    input [2:0]dir;
    output [7:0] SEG;
    output [7:0] AN;

    

    wire clkLR;
    wire clkM;
    
    wire [2:0]numL;
    wire [2:0]numM;
    wire [2:0]numR;
    
    reg [2:0]num;
    
    divider #(5000000) DividerLR(.clk(clk), .clk_N(clkLR));
    divider #(200000) DividerM(.clk(clk), .clk_N(clkM));
    counter CounterL(.clk(clkLR), .out(numL));
    decrease CounterR(.clk(clkLR), .out(numR));
    counter CounterM(.clk(clkM), .out(numM));
    
    always @(dir[2:0]) begin
        case (dir[2:0])
            3'b000: num = 3'b000;
            3'b100: num = numL;
            3'b001: num = numR;
            default : num = numM;
        endcase 
    end

    decoder3_8 Decoder3_8(.num(num), .sel(AN));

    wire [3:0] data;
    rom8x4 Rom8x4(.addr(num), .data(data));
    pattern Pattern(.code(data), .patt(SEG));

endmodule

