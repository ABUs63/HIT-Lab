`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/18 21:58:54
// Design Name: 
// Module Name: choose1from8
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module choose1from8(
    output reg choice,
    input d0,
    input d1,
    input d2,
    input d3,
    input d4,
    input d5,
    input d6,
    input d7,
    input [2:0]f
    );
    always@*
        begin
            case (f)
                 3'b000:choice=d0;
                 3'b001:choice=d1; 
                 3'b010:choice=d2; 
                 3'b011:choice=d3; 
                 3'b100:choice=d4; 
                 3'b101:choice=d5; 
                 3'b110:choice=d6; 
                 3'b111:choice=d7;
                 default;
            endcase
        end
endmodule
