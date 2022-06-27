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
    output result,//���˱��������ߵ�ƽΪͬ�⣬�͵�ƽΪ�ܾ�
    input s1,//1�ű��������ߵ�ƽͬ�⣬�͵�ƽ�ܾ�
    input s2,//2�ű��������ߵ�ƽͬ�⣬�͵�ƽ�ܾ�
    input s3//3�ű��������ߵ�ƽͬ�⣬�͵�ƽ�ܾ�
    );
    wire [2:0]f;//�洢���˸��Ա�����
    wire [7:0]d;//�洢8ѡ1�����ı��ѡ�����
    assign d[0]=0,d[1]=0,d[2]=0,d[3]=1;
    assign d[4]=0,d[5]=1,d[6]=1,d[7]=1;
    getBinary u1(f,s1,s2,s3);//���Ա���洢��f������
    choose1from8 u2(result,f,d);//����8ѡ1����������������
endmodule
