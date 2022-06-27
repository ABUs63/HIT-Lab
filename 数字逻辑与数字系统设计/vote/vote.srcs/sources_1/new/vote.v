`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/18 22:16:31
// Design Name: 
// Module Name: vote
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


module vote(
    output result,
    input s1,
    input s2,
    input s3
    );
    wire [2:0]f;
    getBinary u1(f,s1,s2,s3);
    choose1from8 u2(result,0,0,0,1,0,1,1,1,f);
endmodule
