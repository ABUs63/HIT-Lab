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
    output [2:0]data,//���Խ��ͳһ����
    input s1,//1�ű�����
    input s2,//2�ű�����
    input s3//3�ű�����
    );
    /* 
        �����Ա��������ݸ�data����
    */
    assign data[0]=s1;
    assign data[1]=s2;
    assign data[2]=s3;
endmodule
