`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/17 10:08:30
// Design Name: 
// Module Name: fulladd
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


module fulladd(
    input a,
    input b,
    input c,
    output S,
    output C
    );
    wire x1,x2,x3;
    halfadd u1(a,b,x1,x2);
    halfadd u2(c,x1,S,x3);
    or u3(C,x2,x3);
endmodule
