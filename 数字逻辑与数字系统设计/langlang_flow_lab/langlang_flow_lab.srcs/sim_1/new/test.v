`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/24 09:54:41
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
    reg clk;//ʱ���ź�
    wire [7:0]ledtemp;//���ź�
    flow_lab my(
    .ledtemp(ledtemp),
    .clk(clk));//Ԫ������
        initial begin
               clk=0;
               forever #5 clk=~clk;//ʱ���ź�������ȡ��
        end
endmodule
