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
    output reg [7:0] ledtemp=8'b1,//�����
    input clk);//ʱ���ź�
    reg[25:0]divclk=0;//��Ƶ�ź�
    reg ctrl=0;//��ˮ�Ʒ�������ź�
    always @(posedge clk)
        begin
            if(divclk<50000000)//�ظ���1ʵ�ַ�Ƶ����
                divclk=divclk+1;
            else
                begin 
                    divclk=0;
                    if(ctrl)
                        ledtemp=1;//�ع��ʼ״̬
                    else
                        ledtemp=ledtemp<<1;//����
                    if(ledtemp==128)
                        ctrl=1;//������
                    if(ledtemp==1)
                        ctrl=0;
                end
        end
endmodule
