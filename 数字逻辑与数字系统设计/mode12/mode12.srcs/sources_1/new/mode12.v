`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/26 19:28:09
// Design Name: 
// Module Name: mode12
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


module mode12(
    output Q4,//�ĸ�״̬�ź�
    output Q3,
    output Q2,
    output Q1,
    input X,//���������ź�
    input clk//ʱ���ź�
    );
    wire J4,J3,J2,J1,K4,K3,K2,K1;//��Ӧ4����������J,K
    wire Q4,Q3,Q2,Q1;//��Ӧ4����������̬
    assign J1=1,K1=1; //J1,K1Ϊ��ƽ1
    jk_trigger u1(clk,~X,1,J1,K1,Q1);//�����̬Q1
    assign J2=Q1,K2=Q1;
    jk_trigger u2(clk,~X,1,J2,K2,Q2);//�����̬Q2
    assign J3=(~Q4)&&Q2&&Q1,K3=Q2&&Q1;
    jk_trigger u3(clk,~X,1,J3,K3,Q3);//�����̬Q3
    assign J4=Q3&&Q2&&Q1,K4=~(Q3&&Q2&&Q1||~(Q2&&Q1));
    jk_trigger u4(clk,~X,1,J4,K4,Q4);//�����̬Q4
endmodule
