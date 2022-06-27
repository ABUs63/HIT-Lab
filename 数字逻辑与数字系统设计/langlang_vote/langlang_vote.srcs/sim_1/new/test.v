`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/19 22:02:58
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
    wire choice;//表决结果
    reg s1,s2,s3;//三人各自表决情况
     initial//各自表决初始化
        begin
            s1=0;
            s2=0;
            s3=0;
        end
      always #20{s1,s2,s3}={s1,s2,s3}+1;//每20时间单位表决结果变化1位
    vote my(choice,s1,s2,s3);//例化vote模块，测试功能
endmodule
