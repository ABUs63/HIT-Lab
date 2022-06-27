`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/27 13:52:42
// Design Name: 
// Module Name: getw
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


module getw(
    output w0,
    output w1,
    output w2,
    output w3,
    input Q2,
    input Q1
    );
    assign w0=~(Q1||Q2);
    assign w1=(~Q2)&&Q1;
    assign w2=Q2&&(~Q1);
    assign w3=Q2&&Q1;
endmodule
