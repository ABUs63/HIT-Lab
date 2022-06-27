`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/19 22:02:21
// Design Name: 
// Module Name: vote
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


module vote(
    output result,//三人表决结果，高电平为同意，低电平为拒绝
    input s1,//1号表决结果，高电平同意，低电平拒绝
    input s2,//2号表决结果，高电平同意，低电平拒绝
    input s3//3号表决结果，高电平同意，低电平拒绝
    );
    wire [2:0]f;//存储三人各自表决结果
    wire [7:0]d;//存储8选1部件的表决选择规则
    assign d[0]=0,d[1]=0,d[2]=0,d[3]=1;
    assign d[4]=0,d[5]=1,d[6]=1,d[7]=1;
    getBinary u1(f,s1,s2,s3);//各自表决存储至f变量中
    choose1from8 u2(result,f,d);//调用8选1部件获得整体表决结果
endmodule
