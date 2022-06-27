`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/26 21:29:46
// Design Name: 
// Module Name: D_trigger
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


module D_trigger(
    output reg Q,
    input clk,
    input rst,
    input D
    );
    always @(posedge clk or negedge rst)
        begin
           if(rst==0)
              Q=0;
           else
                Q=D;
        end
endmodule
