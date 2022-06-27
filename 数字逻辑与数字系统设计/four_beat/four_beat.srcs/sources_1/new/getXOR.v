`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/27 13:41:27
// Design Name: 
// Module Name: getXOR
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


module getXOR(
    output x,
    input y1,
    input y2
    );
    assign x=((~y1)&&y2)||(y1&&(~y2));
endmodule
