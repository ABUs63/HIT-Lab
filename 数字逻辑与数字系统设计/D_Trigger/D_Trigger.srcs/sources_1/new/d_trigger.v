`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/27 13:09:37
// Design Name: 
// Module Name: d_trigger
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

module d_trigger(
    output reg Q,
    input clk,
    input rst,
    input set,
    input D
    );
    always @(posedge clk or negedge rst or negedge set)
        begin
           if(rst==0)
              Q=0;
           else if(set==0)
                Q=1;
           else
                Q=D;
        end
endmodule
