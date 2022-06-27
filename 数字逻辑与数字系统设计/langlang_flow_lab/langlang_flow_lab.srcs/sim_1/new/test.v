`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/24 09:54:41
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
    reg clk;//时钟信号
    wire [7:0]ledtemp;//灯信号
    flow_lab my(
    .ledtemp(ledtemp),
    .clk(clk));//元件例化
        initial begin
               clk=0;
               forever #5 clk=~clk;//时钟信号周期性取反
        end
endmodule
