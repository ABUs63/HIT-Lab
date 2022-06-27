`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/29 12:26:40
// Design Name: 
// Module Name: test_light
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


module test_light();
    reg clk;//ʱ������
    reg [3:0]dire;//�������,��������
    reg double_flash;//����˫��
    reg close;//�Ƿ�����
    reg speed;//�Ƿ����
    reg back;//����״̬
    reg shift;//Ư��ģʽ
    reg door1;//�ж����Ƿ�غ�
    reg change;//�������Ƶ�ʱ��
    wire [7:0]dm1;//����1
    wire [3:0]wm1;//λ��1
    wire [7:0]dm2;//����2
    wire [3:0]wm2;//λ��2
    wire [2:0]left;//���β��
    wire [2:0]right;//�Ҳ�β��
    wire [7:0]xklsd;//�ſ���ˮ��
    
    car_light car_test(clk,dire,double_flash,close,speed,shift,door1,change,back,dm1,wm1,dm2,wm2,left,right,xklsd);
    
    initial 
    begin //��ʼ״̬,����δ�������Źغ�
        clk = 0;dire = 4'b0000;close = 0;double_flash = 0;speed = 0;back = 0;shift = 0;door1 = 1;change = 0;
        #50 door1 = 0;//δ��������δ�غã�����ģʽ
        #50 close = 1;//��������δ�غ�
        #50 door1=0;close=0;//δ��������û�غ�
        #50 door1=1;close=1;//�������Źغ�
        #50 dire = 4'b0001;//����������ʻ
        #100 dire = 4'b0011;//������ת
        #100 dire = 4'b0101;//������ת
        #100 dire = 4'b1000;//����ɲ��
        #100 dire = 4'b0000;speed = 1;//����ģʽ
        #100 dire = 4'b0001;//����������ʻ
        #100 dire = 4'b0011;//������ת
        #100 dire = 4'b0101;//������ת
        #100 dire = 4'b1000;//����ɲ��
        #100 dire = 4'b0000;shift = 1;//Ư��ģʽ
        #100 dire = 4'b0001;
        #100 dire = 4'b0011;//��Ư��
        #100 dire = 4'b0101;//��Ư��
        #100 dire = 4'b1000;
        #100 dire = 4'b0000;shift = 0;double_flash = 1;//����ģʽ
        #100 double_flash = 0;
        #100 dire = 4'b0000;back = 1;//����ģʽ
        #100 back = 0;
    end
    always #1 clk = ~clk;
    
endmodule
