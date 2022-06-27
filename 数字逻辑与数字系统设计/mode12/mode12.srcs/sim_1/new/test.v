`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/26 20:47:59
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
    reg clk,X;//时钟信号、计数清零信号
    wire Q4,Q3,Q2,Q1;//单周期记满信号（下降沿为一个周期）
    initial 
        begin
            clk=0;X=1;
            #2 X=0;//预置
            #13 X=1;//清零操作测试
            #14 X=0;
        end
    always #3 clk=~clk;
    mode12 my(Q4,Q3,Q2,Q1,X,clk);//元件例化
endmodule
