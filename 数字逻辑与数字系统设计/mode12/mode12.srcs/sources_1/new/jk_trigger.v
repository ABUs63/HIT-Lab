`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/26 19:27:41
// Design Name: 
// Module Name: jk_trigger
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


module jk_trigger(
    input clk,//时钟信号
    input RST,//异步清零信号
    input SET,//异步置位信号
    input j,//J输入信号
    input k,//K输入信号
    output reg Q//输出信号
    );
   always @(posedge clk or negedge SET or negedge RST)//时钟上升沿,异步清零、置位下降沿
   begin
        if(RST==0)//异步清零
          Q=0;
        else if(SET==0)//异步置位
            Q=1;
        else if(j==1&&k==1)//翻转功能
            Q=~Q;
        else if(j==0&&k==1)//置0功能
            Q=0;
        else if(j==1&&k==0)//置1功能
            Q=1;
        else//保持功能
            Q=Q;
    end
endmodule
