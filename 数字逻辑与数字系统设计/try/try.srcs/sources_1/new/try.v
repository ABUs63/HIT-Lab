`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/20 13:17:31
// Design Name: 
// Module Name: car_light
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


module try(
    clk,//ʱ��
    close,//0δ�غ�,1�غ�
    speed,//�Ƿ�����ٶ�
    direction,//�������(������ʻ����ת�䡢��ת�䡢��ʱɲ����������
    double_flash,//����˫��
    shift,//Ư��ģʽ
    light_r,//��β��
    light_l,//��β��
    signal_1,//״̬����
    signal_5,//�ٶ�״̬
    control_1,//λ��1
    control_2//λ��2
    );
    input clk,close,speed,double_flash,shift;
    input [4:0] direction;
    output [2:0] light_r;
    output [2:0] light_l;
    output [7:0] signal_1;//��λΪa����λΪh
    output [7:0] signal_5;
    output reg [3:0] control_1;
    output reg [3:0] control_2=4'b0001;
    reg divclk=0;//��Ƶʱ��
    reg [1:0]count;//����
    reg [31:0] div_cnt=0;//��Ƶ
    reg [2:0]light_rtmp;assign light_r=light_rtmp;
    reg [2:0]light_ltmp;assign light_l=light_ltmp;
    reg [7:0]tmp;assign signal_1=tmp;
    reg [7:0]signal_5tmp;assign signal_5=signal_5tmp;
    always@(close||speed||double_flash||shift)//��������ܲ���
    begin
    if(close==1)//�Źغ�
        begin
        if(speed==0)
            signal_5tmp=8'b00011100;//������ʾL
        if(speed==1)
            signal_5tmp=8'b01101110;//������ʾH
        if(direction[0]==1)//����ǰ��,��ת����ת
            begin
                if(direction[1]==1)//��ת,��ʾ01
                    case(count)
                        2'b00:tmp=8'b01100000;
                        2'b01:tmp=8'b11111100;
                        2'b10:tmp=8'b00000000;
                        2'b11:tmp=8'b00000000;
                        default:tmp=8'b00000000;
                    endcase
                if(direction[2]==1)//��ת,��ʾ10
                    case(count)
                        2'b00:tmp=8'b11111100;//���0
                        2'b01:tmp=8'b01100000;//���1
                        2'b10:tmp=8'b00000000;
                        2'b11:tmp=8'b00000000;
                        default:tmp=8'b00000000;
                    endcase
                if(direction[1]==0&&direction[2]==0)//����ǰ��
                    case(count)
                        2'b00:tmp=8'b01100000;//���1
                        2'b01:tmp=8'b01100000;
                        2'b10:tmp=8'b10011110;//���E
                        2'b11:tmp=8'b10011110;
                        default:tmp=8'b00000000;
                    endcase
             end
        if(direction[0]==0&&direction[3]==1)//��ʱɲ��,��ʾPP
            case(count)
                 2'b00:tmp=8'b00000000;
                 2'b01:tmp=8'b00000000;
                 2'b10:tmp=8'b11001110;//��ʾP
                 2'b11:tmp=8'b11001110;
                 default:tmp=8'b00000000;
            endcase
        if(direction[0]==0&&direction[4]==1)//����ģʽ,��ʾ00
            case(count)
                 2'b00:tmp=8'b11111100;
                 2'b01:tmp=8'b11111100;
                 2'b10:tmp=8'b00000000;
                 2'b11:tmp=8'b00000000;
                 default:tmp=8'b00000000;
            endcase
        end
    if(close==0)//��û�غã���ʾEE
        case(count)
             2'b00:tmp=8'b00000000;
             2'b01:tmp=8'b00000000;
             2'b10:tmp=8'b10011110;
             2'b11:tmp=8'b10011110;
             default:tmp=8'b00000000;
        endcase
        begin
            light_ltmp=3'b111;//��β��
            light_rtmp=3'b111;//��β��
        end
    if(double_flash==1)//����,˫��
        begin
            light_rtmp[0]=~light_rtmp[0];
            light_rtmp[1]=~light_rtmp[1];
            light_rtmp[2]=~light_rtmp[2];
            light_rtmp[0]=light_rtmp[2];
            light_rtmp[1]=light_rtmp[1];
            light_rtmp[2]=light_rtmp[1];
        end   
    end
 always@(posedge clk)//λ�����
    begin
        if(control_1[3]==1)
            begin
                control_1=4'b0001;
            end
        if(control_1[3]==0)
            control_1=control_1<<1;
        if(div_cnt==12500000)
            begin
                divclk=~divclk;
                div_cnt=0;
            end
        count=count+1;
    end
endmodule
