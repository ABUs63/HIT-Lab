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
    clk,//时钟
    close,//0未关好,1关好
    speed,//是否加速速度
    direction,//方向控制(正常行驶、右转弯、左转弯、临时刹车、倒车）
    double_flash,//故障双闪
    shift,//漂移模式
    light_r,//右尾灯
    light_l,//左尾灯
    signal_1,//状态字形
    signal_5,//速度状态
    control_1,//位码1
    control_2//位码2
    );
    input clk,close,speed,double_flash,shift;
    input [4:0] direction;
    output [2:0] light_r;
    output [2:0] light_l;
    output [7:0] signal_1;//高位为a，低位为h
    output [7:0] signal_5;
    output reg [3:0] control_1;
    output reg [3:0] control_2=4'b0001;
    reg divclk=0;//分频时钟
    reg [1:0]count;//计数
    reg [31:0] div_cnt=0;//分频
    reg [2:0]light_rtmp;assign light_r=light_rtmp;
    reg [2:0]light_ltmp;assign light_l=light_ltmp;
    reg [7:0]tmp;assign signal_1=tmp;
    reg [7:0]signal_5tmp;assign signal_5=signal_5tmp;
    always@(close||speed||double_flash||shift)//方向数码管部分
    begin
    if(close==1)//门关好
        begin
        if(speed==0)
            signal_5tmp=8'b00011100;//低速显示L
        if(speed==1)
            signal_5tmp=8'b01101110;//高速显示H
        if(direction[0]==1)//正常前进,左转或右转
            begin
                if(direction[1]==1)//左转,显示01
                    case(count)
                        2'b00:tmp=8'b01100000;
                        2'b01:tmp=8'b11111100;
                        2'b10:tmp=8'b00000000;
                        2'b11:tmp=8'b00000000;
                        default:tmp=8'b00000000;
                    endcase
                if(direction[2]==1)//右转,显示10
                    case(count)
                        2'b00:tmp=8'b11111100;//输出0
                        2'b01:tmp=8'b01100000;//输出1
                        2'b10:tmp=8'b00000000;
                        2'b11:tmp=8'b00000000;
                        default:tmp=8'b00000000;
                    endcase
                if(direction[1]==0&&direction[2]==0)//正常前进
                    case(count)
                        2'b00:tmp=8'b01100000;//输出1
                        2'b01:tmp=8'b01100000;
                        2'b10:tmp=8'b10011110;//输出E
                        2'b11:tmp=8'b10011110;
                        default:tmp=8'b00000000;
                    endcase
             end
        if(direction[0]==0&&direction[3]==1)//临时刹车,显示PP
            case(count)
                 2'b00:tmp=8'b00000000;
                 2'b01:tmp=8'b00000000;
                 2'b10:tmp=8'b11001110;//显示P
                 2'b11:tmp=8'b11001110;
                 default:tmp=8'b00000000;
            endcase
        if(direction[0]==0&&direction[4]==1)//倒车模式,显示00
            case(count)
                 2'b00:tmp=8'b11111100;
                 2'b01:tmp=8'b11111100;
                 2'b10:tmp=8'b00000000;
                 2'b11:tmp=8'b00000000;
                 default:tmp=8'b00000000;
            endcase
        end
    if(close==0)//门没关好，显示EE
        case(count)
             2'b00:tmp=8'b00000000;
             2'b01:tmp=8'b00000000;
             2'b10:tmp=8'b10011110;
             2'b11:tmp=8'b10011110;
             default:tmp=8'b00000000;
        endcase
        begin
            light_ltmp=3'b111;//左尾灯
            light_rtmp=3'b111;//右尾灯
        end
    if(double_flash==1)//故障,双闪
        begin
            light_rtmp[0]=~light_rtmp[0];
            light_rtmp[1]=~light_rtmp[1];
            light_rtmp[2]=~light_rtmp[2];
            light_rtmp[0]=light_rtmp[2];
            light_rtmp[1]=light_rtmp[1];
            light_rtmp[2]=light_rtmp[1];
        end   
    end
 always@(posedge clk)//位码控制
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
