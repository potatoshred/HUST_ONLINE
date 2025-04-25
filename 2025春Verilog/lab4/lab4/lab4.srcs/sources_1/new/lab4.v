`timescale 1ns / 1ps

module adder(x, y,c_in, sum, c_out);
    parameter N = 32;
    input [N-1:0] x, y;
    input c_in;
    output [N-1:0] sum;
    output c_out;
    
    assign {c_out, sum} = x+y+c_in;
    
endmodule

module mux(sel, x, y, ret);
    parameter N = 32;
    input sel;
    input [N-1:0] x, y;
    output [N-1:0] ret;
    
    assign ret = sel ? y : x;
endmodule

module compare(x, y, g,e,l);
    parameter N = 32;
    input [N-1:0] x, y;
    output g,e,l;
    
    assign g=(x>y)?1'b1:1'b0;
    assign e=(x==y)?1'b1:1'b0;
    assign l=(x<y)?1'b1:1'b0;    
endmodule

module dflipflop(clk, D, rst, load, Q);
    parameter N = 32;
    input clk,rst,load;
    input [N-1:0] D;
    output reg [N-1:0] Q;
    
    always @(posedge clk) begin
        if (rst==1) Q <= 0;         // 低电平触发
        else if (load == 1) Q <= D; // 高电平触发
        
    end
endmodule


module ram(clk, WE, addr, dataR, dataW);
    parameter DATA_WIDTH = 8;
    parameter ADDR_WIDTH = 3;

    input clk, WE;
    input [DATA_WIDTH-1:0] dataW;
    input [ADDR_WIDTH-1:0] addr;
    output reg [DATA_WIDTH-1:0] dataR;

    // 申明存储器数
    reg [DATA_WIDTH-1:0] ram[2**ADDR_WIDTH - 1:0];

    initial begin
        $readmemh("D:/D2B/verilog/proj/lab4/memlinknode.data", ram); 
    end

    always @(addr) begin
        if (WE) ram[addr] <= dataW;
        else dataR <= ram[addr];
    end    
endmodule


module pipeline(clk, rst, LD_SUM, LD_NEXT, SUM_SEL, NEXT_SEL, A_SEL, NEXT_ZERO, ret);
    parameter DATA_WIDTH = 8;
    parameter ADDR_WIDTH = 3;
    input clk;
    input rst;
    input LD_SUM, LD_NEXT, SUM_SEL, NEXT_SEL, A_SEL;
    output NEXT_ZERO;
    output [DATA_WIDTH-1:0] ret;

    wire [ADDR_WIDTH-1:0] addr;
    wire [DATA_WIDTH-1:0] data, add1, add2, sum, next, mux1, mux2;

    assign ret=sum;

    adder #(DATA_WIDTH) ADDER_1(sum, data, 0, add1, );
    adder #(DATA_WIDTH) ADDER_2(  1, next, 0, add2, );
    
    mux #(DATA_WIDTH) MUX_1(SUM_SEL, 0, add1, mux1);
    mux #(DATA_WIDTH) MUX_2(NEXT_SEL,0, data, mux2);
    mux #(DATA_WIDTH) MUX_3(A_SEL,next, add2, addr);

    dflipflop #(DATA_WIDTH)  DFF_sum(clk, mux1, rst,  LD_SUM, sum);
    dflipflop #(DATA_WIDTH) DFF_next(clk, mux2, rst, LD_NEXT, next);

    compare #(DATA_WIDTH) COMPARE_nextzero(0, mux2, , NEXT_ZERO, );

    ram #(DATA_WIDTH, ADDR_WIDTH) RAM_memory(clk, 0, addr, data, 0);
endmodule


module fsm(clk, rst, start, next_zero, ld_sum, ld_next, sum_sel, next_sel, a_sel, done);

    input clk, rst, start, next_zero;
    output reg ld_sum, ld_next, sum_sel, next_sel, a_sel, done;

    reg [1:0] state_cur, state_nxt;
    
    localparam START = 0, COMPUTE_SUM = 1, GET_NEXT = 2, DONE = 3;

    always @(posedge clk) begin
        state_cur <= rst ? start : state_nxt;
    end

    always @(start, state_cur, next_zero) begin
        case (state_cur)
            START: begin
                {ld_sum, ld_next, sum_sel, next_sel, a_sel, done} <= 6'b000000;
                state_nxt <= (state_cur==COMPUTE_SUM) ? COMPUTE_SUM : START;
                end
            COMPUTE_SUM:begin
                {ld_sum, ld_next, sum_sel, next_sel, a_sel, done} <= 6'b101110;
                state_nxt <= GET_NEXT;
                end
            GET_NEXT:begin
                {ld_sum, ld_next, sum_sel, next_sel, a_sel, done} <= 6'b011100;
                state_nxt <= (next_zero==1) ? DONE : COMPUTE_SUM;
                end
            default:begin // DONE
                {ld_sum, ld_next, sum_sel, next_sel, a_sel, done} <= 6'b000001;
                state_nxt <= (start==1) ? DONE : START;
                end 
        endcase
    end

endmodule

module accumulator (clk, rst, start, done, sum_out);
    parameter DATA_WIDTH = 32; 
    input clk,rst,start;
    output done;
    output [DATA_WIDTH-1:0] sum_out;

    wire ld_sum, ld_next, sum_sel, next_sel, a_sel, next_zero;

    pipeline #(32, 4) PPL_accum(clk, rst, ld_sum, ld_next, sum_sel, next_sel, a_sel, next_zero, sum_out);
    fsm FSM_accum(clk, rst, start, next_zero, ld_sum, ld_next, sum_sel, next_sel, a_sel, done);
endmodule

module divider(clk, clk_N);
    input wire clk;               // 系统时钟
    output clk_N;                 // 分频后的时钟
    parameter N = 4_000_000;      // 1Hz的时钟,N=fclk/fclk_N
    reg [31:0] counter;           /* 计数器变量，通过计数实现分频。
                                     当计数器从0计数到(N/2-1)时，
                                     输出时钟翻转，计数器清零 */
    reg flag = 0;
    assign clk_N = flag;
    
    always @(posedge clk)  begin  // 时钟上升沿
                                  // 功能实现
        if(counter == (N/2-1)) begin
            flag <= ~flag; 
            counter <= 0;
        end
        else counter <= counter + 1;
    end
endmodule

module counter(clk, out);
    input clk;                   // 计数时钟
    output reg [2:0] out;        // 计数值

    always @(posedge clk)  begin // 在时钟上升沿计数器加1
        out <= out + 1;          // 在时钟上升沿计数器加1
    end                           
endmodule

module pattern(code, patt);
    input [3: 0] code;
    output [7:0] patt;

    reg [7:0] SEG_w;
    assign patt = SEG_w; 
	always @(code[3:0]) begin
        case(code[3:0])
            4'h0:    SEG_w = 8'b11000000;
            4'h1:    SEG_w = 8'b11111001;
            4'h2:    SEG_w = 8'b10100100;
            4'h3:    SEG_w = 8'b10110000;
            4'h4:    SEG_w = 8'b10011001;
            4'h5:    SEG_w = 8'b10010010;
            4'h6:    SEG_w = 8'b10000010;
            4'h7:    SEG_w = 8'b11111000;
            4'h8:    SEG_w = 8'b10000000;
            4'h9:    SEG_w = 8'b10011000;
            4'hA:    SEG_w = 8'b10001000;
            4'hB:    SEG_w = 8'b10000011;
            4'hC:    SEG_w = 8'b11000110;
            4'hD:    SEG_w = 8'b10100001;
            4'hE:    SEG_w = 8'b10000110;
            default: SEG_w = 8'b10001110;
        endcase
	end
endmodule

module router(clk, sum_out, index, AN, SEG);
    input clk;
    input [31:0] sum_out;
    input [2:0]  index;
    output reg [7:0]AN;
	output reg [7:0]SEG;

    wire [7:0] patt[7:0];
    reg  [7:0] patt_cur;
    reg  [7:0] AN_t;
    wire [3:0] digit[7:0];
 
    assign digit[0] = (sum_out)%10;
    assign digit[1] = (sum_out/10)%10;
    assign digit[2] = (sum_out/100)%10;
    assign digit[3] = (sum_out/1000)%10;
    assign digit[4] = (sum_out/10000)%10;
    assign digit[5] = (sum_out/100000)%10;
    assign digit[6] = (sum_out/1000000)%10;
    assign digit[7] = (sum_out/10000000)%10;


    pattern PATTERN_0(digit[0], patt[0]);
    pattern PATTERN_1(digit[1], patt[1]);
    pattern PATTERN_2(digit[2], patt[2]);
    pattern PATTERN_3(digit[3], patt[3]);
    pattern PATTERN_4(digit[4], patt[4]);
    pattern PATTERN_5(digit[5], patt[5]);
    pattern PATTERN_6(digit[6], patt[6]);
    pattern PATTERN_7(digit[7], patt[7]);
    // pattern PATTERN_0(  sum_out[3:0], patt[0]);
    // pattern PATTERN_1(  sum_out[7:4], patt[1]);
    // pattern PATTERN_2( sum_out[11:8], patt[2]);
    // pattern PATTERN_3(sum_out[15:12], patt[3]);
    // pattern PATTERN_4(sum_out[19:16], patt[4]);
    // pattern PATTERN_5(sum_out[23:20], patt[5]);
    // pattern PATTERN_6(sum_out[27:24], patt[6]);
    // pattern PATTERN_7(sum_out[31:28], patt[7]);

    initial AN = 8'b11111110;

    // decoder3_8 DECODER_an(index, AN_t);
    // assign AN = AN_t;

    always @(posedge clk) begin
        AN = 8'hFF ^ (8'h01 << index);
        SEG <= patt[index];
    end

endmodule

module display(clk, rst, start, Done, SEG, AN);
    input clk, rst, start;
    output Done;
    output [7:0] SEG;
    output [7:0] AN;

    wire clk_accu, clk_an;
    wire  [2:0] index;
    wire [31:0] sum_out;

    // initial sum_out = 32'h00000000;
    
    divider #(50000000) DIVIDER_1(clk, clk_accu);
    divider #(200000) DIVIDER_2(clk, clk_an);

    counter COUNTER_index(clk_an, index);

    accumulator ACCU_pc(clk_accu, rst, start, Done, sum_out);
    router ROUTER_an(clk_an, sum_out, index, AN, SEG);

endmodule

