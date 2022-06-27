`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/26 21:41:23
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


module test(
    );
    reg clk,rst;
    wire w0,w1,w2,w3;
    initial
        begin
            clk=0;rst=1;
            #3 rst=0;
            #4 rst=1;
        end
    always #5 clk=~clk;
    four_beat my(rst,clk,w0,w1,w2,w3);
endmodule
