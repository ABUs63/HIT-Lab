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
    input clk,//ʱ���ź�
    input RST,//�첽�����ź�
    input SET,//�첽��λ�ź�
    input j,//J�����ź�
    input k,//K�����ź�
    output reg Q//����ź�
    );
   always @(posedge clk or negedge SET or negedge RST)//ʱ��������,�첽���㡢��λ�½���
   begin
        if(RST==0)//�첽����
          Q=0;
        else if(SET==0)//�첽��λ
            Q=1;
        else if(j==1&&k==1)//��ת����
            Q=~Q;
        else if(j==0&&k==1)//��0����
            Q=0;
        else if(j==1&&k==0)//��1����
            Q=1;
        else//���ֹ���
            Q=Q;
    end
endmodule
