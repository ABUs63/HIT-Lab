`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/29 12:26:40
// Design Name: 
// Module Name: test_light
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


module test_light();
    reg clk;//时钟输入
    reg [3:0]dire;//方向控制,不含倒车
    reg double_flash;//故障双闪
    reg close;//是否启动
    reg speed;//是否加速
    reg back;//倒车状态
    reg shift;//漂移模式
    reg door1;//判断门是否关好
    reg change;//调整亮灯的时间
    wire [7:0]dm1;//段码1
    wire [3:0]wm1;//位码1
    wire [7:0]dm2;//段码2
    wire [3:0]wm2;//位码2
    wire [2:0]left;//左侧尾灯
    wire [2:0]right;//右侧尾灯
    wire [7:0]xklsd;//炫酷流水灯
    
    car_light car_test(clk,dire,double_flash,close,speed,shift,door1,change,back,dm1,wm1,dm2,wm2,left,right,xklsd);
    
    initial 
    begin //初始状态,车辆未启动且门关好
        clk = 0;dire = 4'b0000;close = 0;double_flash = 0;speed = 0;back = 0;shift = 0;door1 = 1;change = 0;
        #50 door1 = 0;//未启动，门未关好，报警模式
        #50 close = 1;//启动，门未关好
        #50 door1=0;close=0;//未启动，门没关好
        #50 door1=1;close=1;//启动，门关好
        #50 dire = 4'b0001;//低速正向行驶
        #100 dire = 4'b0011;//低速左转
        #100 dire = 4'b0101;//低速右转
        #100 dire = 4'b1000;//低速刹车
        #100 dire = 4'b0000;speed = 1;//高速模式
        #100 dire = 4'b0001;//高速正向行驶
        #100 dire = 4'b0011;//高速左转
        #100 dire = 4'b0101;//高速右转
        #100 dire = 4'b1000;//高速刹车
        #100 dire = 4'b0000;shift = 1;//漂移模式
        #100 dire = 4'b0001;
        #100 dire = 4'b0011;//左漂移
        #100 dire = 4'b0101;//右漂移
        #100 dire = 4'b1000;
        #100 dire = 4'b0000;shift = 0;double_flash = 1;//故障模式
        #100 double_flash = 0;
        #100 dire = 4'b0000;back = 1;//倒车模式
        #100 back = 0;
    end
    always #1 clk = ~clk;
    
endmodule
