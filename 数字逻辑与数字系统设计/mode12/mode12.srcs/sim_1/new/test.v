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
    reg clk,X;//ʱ���źš����������ź�
    wire Q4,Q3,Q2,Q1;//�����ڼ����źţ��½���Ϊһ�����ڣ�
    initial 
        begin
            clk=0;X=1;
            #2 X=0;//Ԥ��
            #13 X=1;//�����������
            #14 X=0;
        end
    always #3 clk=~clk;
    mode12 my(Q4,Q3,Q2,Q1,X,clk);//Ԫ������
endmodule
