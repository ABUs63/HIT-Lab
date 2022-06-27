`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/27 13:10:21
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
    reg clk,rst,set,D;
    wire Q;
    initial
        begin 
            clk=0;rst=1;set=1;D=0;
            #5 set=0;
            #8 rst=0;
            #10 rst=1;set=1;
        end
    always #3 clk=~clk;
    always #2 D=~D;
    d_trigger my(Q,clk,rst,set,D);
endmodule
