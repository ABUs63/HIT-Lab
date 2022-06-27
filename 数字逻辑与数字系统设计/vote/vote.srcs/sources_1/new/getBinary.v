`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/18 22:24:12
// Design Name: 
// Module Name: getBinary
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


module getBinary(
    output [2:0]data,
    input s1,
    input s2,
    input s3
    );
    assign data[0]=s1;
    assign data[1]=s2;
    assign data[2]=s3;
endmodule
