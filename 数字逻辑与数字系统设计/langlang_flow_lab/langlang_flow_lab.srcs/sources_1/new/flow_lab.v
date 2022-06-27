`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/24 09:47:31
// Design Name: 
// Module Name: flow_lab
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


module flow_lab(
    output reg [7:0] ledtemp=8'b1,//灯输出
    input clk);//时钟信号
    reg[25:0]divclk=0;//分频信号
    reg ctrl=0;//流水灯方向控制信号
    always @(posedge clk)
        begin
            if(divclk<50000000)//重复加1实现分频操作
                divclk=divclk+1;
            else
                begin 
                    divclk=0;
                    if(ctrl)
                        ledtemp=1;//回归初始状态
                    else
                        ledtemp=ledtemp<<1;//左移
                    if(ledtemp==128)
                        ctrl=1;//换方向
                    if(ledtemp==1)
                        ctrl=0;
                end
        end
endmodule
