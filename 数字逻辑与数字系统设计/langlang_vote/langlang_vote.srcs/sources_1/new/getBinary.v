`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/19 22:01:17
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
    output [2:0]data,//各自结果统一变量
    input s1,//1号表决结果
    input s2,//2号表决结果
    input s3//3号表决结果
    );
    /* 
        将各自表决结果传递给data变量
    */
    assign data[0]=s1;
    assign data[1]=s2;
    assign data[2]=s3;
endmodule
