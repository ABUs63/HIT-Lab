`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/19 22:01:54
// Design Name: 
// Module Name: choose1from8
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


module choose1from8(
    output reg choice,//8ѡ1����ѡ����ѡ����
    input [2:0]f,//ѡ����ѡ����ƶ�
    input [7:0]d//ѡ�������������
    );
    always@*
        begin
            case (f)//����ѡ����ƶ��ź�ѡ��Ӧ���
                 3'b000:choice=d[0];//0��ͬ��
                 3'b001:choice=d[1];//1��ͬ��
                 3'b010:choice=d[2];//1��ͬ��
                 3'b011:choice=d[3];//2��ͬ��
                 3'b100:choice=d[4];//1��ͬ��
                 3'b101:choice=d[5];//2��ͬ��
                 3'b110:choice=d[6];//2��ͬ��
                 3'b111:choice=d[7];//3��ͬ��
                 default;
            endcase
        end
endmodule
