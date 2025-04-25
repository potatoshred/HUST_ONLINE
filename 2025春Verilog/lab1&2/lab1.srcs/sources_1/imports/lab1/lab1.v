`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: lab1
//////////////////////////////////////////////////////////////////////////////////


module _7Seg_Driver_Direct(SW, CA, CB, CC, CD, CE, CF, CG, DP, AN, LED);
	input [15:0] SW;                          // 16位拨动开关
	output CA, CB, CC, CD, CE, CF, CG, DP;  // 7段数码管驱动，低电平有效
	output [7:0] AN;                          // 7段数码管片选信号，低电平有效
	output [15:0] LED;                        // 16位LED显示，高电平有效
	
	assign LED[15:0] = SW[15:0];
	assign AN[7:0] = ~SW[15:8];
	assign {CA,CB,CC,CD,CE,CF,CG,DP} = ~SW[7:0];
endmodule


module _7Seg_Driver_Decode(SW, SEG, AN, LED);
	input [15:0] SW;       // 16位拨动开关
	output [7:0] SEG;      // 7段数码管驱动，低电平有效
	output [7:0] AN;       // 7段数码管片选信号，低电平有效
	output [15:0] LED;     // 16位LED显示
	
	
    assign LED[15:0] = SW[15:0];
    assign AN[7:0] = ~SW[15:8];
    
    reg [7:0] SEG_w;
    assign SEG = SEG_w; 
	always @(SW[3:0]) begin
        case(SW[3:0])
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


module _7Seg_Driver_Choice(SW, SEG, AN, LED);
    input [15:0] SW;       // 16位拨动开关
    output [7:0] SEG;      // 7段数码管驱动，低电平有效
    output [7:0] AN;       // 7段数码管片选信号，低电平有效
    output [15:0] LED;     // 16位LED显示
    
    assign LED[15:0] = SW[15:0];

    reg [7:0] SEG_w, AN_w;
    assign SEG = SEG_w; 
    assign AN = AN_w; 
    
	always @(SW[15:0]) begin
        case(SW[3:0])
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
        
        case(SW[15:13])
            4'h0:AN_w     = 8'b11111110;
            4'h1:AN_w     = 8'b11111101;
            4'h2:AN_w     = 8'b11111011;
            4'h3:AN_w     = 8'b11110111;
            4'h4:AN_w     = 8'b11101111;
            4'h5:AN_w     = 8'b11011111;
            4'h6:AN_w     = 8'b10111111;
            default :AN_w = 8'b01111111;
        endcase
        
	end
    
endmodule

module _7Seg_Driver_BCD(SW, SEG, AN, LED);
    input [15:0] SW;       // 16位拨动开关
    output [7:0] SEG;      // 7段数码管驱动，低电平有效
    output [7:0] AN;       // 7段数码管片选信号，低电平有效
    output [15:0] LED;     // 16位LED显示
    
    assign LED[15:0] = SW[15:0];
    
    reg [7:0] SEG_w, AN_w;
    assign SEG = SEG_w; 
    assign AN = AN_w; 
    
	always @(SW[15:0]) begin        
        case(SW[14:12])
            4'h0:AN_w     = 8'b11111110;
            4'h1:AN_w     = 8'b11111101;
            4'h2:AN_w     = 8'b11111011;
            4'h3:AN_w     = 8'b11110111;
            4'h4:AN_w     = 8'b11101111;
            4'h5:AN_w     = 8'b11011111;
            4'h6:AN_w     = 8'b10111111;
            default :AN_w = 8'b01111111;
        endcase
        
        if(SW[15] == 1'b0 && SW[3:0]<=4'h9) begin
            case(SW[3:0])
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
                default :SEG_w = 8'b10000110;
            endcase
        end
        else if(SW[15] == 1'b0 && SW[3:0]>4'h9) begin
              case(SW[3:0]-4'hA)
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
                
                default :SEG_w = 8'b10000110;
            endcase
        end
        else if(SW[15] == 1'b1 && SW[3:0]<=4'h9) begin
            SEG_w     = 8'b11000000;
        end
        else begin
            SEG_w     = 8'b11111001;
        end
        
    end
endmodule