`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/26 18:52:01
// Design Name: 
// Module Name: test
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


module test;
reg clk,RST,SET,j,k;
    wire Q;
    initial
        begin 
            clk=0;RST=1;SET=1;j=0;k=0;
            #3 SET=0;
            #6 RST=0;
            #9 RST=1;SET=1;
            forever #10 clk=~clk;
        end
        always #4 {j,k}={j,k}+1;
    jk_trigger my(clk,RST,SET,j,k,Q);
endmodule
