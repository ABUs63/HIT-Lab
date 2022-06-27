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


module car_light(clk,dire,double_flash,close,speed,shift,door1,change,back,dm1,wm1,dm2,wm2,left,right,xklsd);
    input clk;//ʱ������
    input [3:0]dire;//�������,��������
    input double_flash;//����˫��
    input close;//�Ƿ�����
    input speed;//�Ƿ����
    input back;//����״̬
    input shift;//Ư��ģʽ
    input door1;//�ж����Ƿ�غ�
    input change;//�������Ƶ�ʱ��
    output [7:0]dm1;//����1
    output [3:0]wm1;//λ��1
    output [7:0]dm2;//����2
    output [3:0]wm2;//λ��2
    output [2:0]left;//���β��
    output [2:0]right;//�Ҳ�β��
    output [7:0]xklsd;//�ſ���ˮ��
    
    reg [7:0]dm1=0;
    reg [7:0]dm2=0;
    reg [7:0]sw1=0;
    reg [7:0]sw2=0;
    reg [3:0]wm1=4'b0001;
    reg [3:0]wm2=4'b0001;
    reg [14:0]div_cnt=0;//��Ƶ����
    reg divclk=0;//��Ƶʱ��1
    reg [3:0]disp_dat=0;
    reg [1:0]disp_bit=0;
    reg [2:0]left = 0;
    reg [2:0]right = 0;
    reg [31:0]count=0;//ʱ�����
    reg count_time;//ʱ���Ƿ�
    reg [31:0]time1 = 0; //��¼����ʱ��
    reg divclk2 = 0;//��Ƶ�� 
    reg [7:0]xklsd;//
    
    
    always@(posedge clk)
    begin
        if((door1==1&&close==1)||(door1==0&&close==0))//ʱ�������ʼ��
        begin divclk2=0;time1=0;end
        if(door1==0&&close==1)//ʱ�������Ӧģʽ
        begin
            if(change == 0)//δ�ı��ʱ��ԼΪ5��
            begin
                if(time1 == 500000000)
                    begin divclk2 =1; end
                else
                    begin time1 = time1 + 1'b1; end
            end
            else if(change == 1)//�ı��ʱ��ԼΪ10��
            begin
                if(time1 == 1000000000)
                     begin divclk2 =1; end
                else
                     begin time1 = time1 + 1'b1; end
            end
        end
        if(div_cnt==15'b111111111111111)//ʱ�ӷ�Ƶʵ��
            begin divclk=~divclk;div_cnt=0;end
        else
            begin div_cnt=div_cnt+1'b1;end
        if(count==32'b11111111111111111111111111111111)//��Ƶʵ��2
        begin count=0;end
        else
        begin count=count+1'b1;end
    end
   
    
    always@(posedge divclk)//��Ƶʱ��
    begin            
          if(disp_bit>=3) 
              disp_bit=0; 
          else
              disp_bit=disp_bit+1;    
          case (disp_bit)
             2'b00:
                   begin disp_dat=sw1;wm1=4'b0001;end
             2'b01:
                   begin disp_dat=sw2;wm1=4'b0010;end
             2'b10:
                   begin disp_dat=sw1;wm1=4'b0001;end
             2'b11:
                   begin disp_dat=sw2;wm1=4'b0010;end
             default:
                   begin disp_dat=0;wm1=4'b0000;end
           endcase
       end
       
       always @(dire||close||door1||speed||back||double_flash||count[26]||count[25])
       begin
            if(close==1)//����������
                begin xklsd=8'b000000000;end
            if(close==1 && door1 == 1)//�غ���
                begin
                if(back==0)//���ڵ���״̬
                    begin//��ͬ���������Ӧ����
                        case (dire)
                            4'b0001:begin sw1=4'b0001;sw2=4'b0001;end
                            4'b0011:begin sw1=4'b0001;sw2=4'b0000;end
                            4'b0101:begin sw1=4'b0000;sw2=4'b0001;end
                            4'b1000:begin sw1=4'b1010;sw2=4'b1010;end
                            default:begin sw1=4'b1111;sw2=4'b1111;end
                        endcase
                    end
                else if(back==1)//����״̬,��ʾbb
                    begin sw1=4'b1100;sw2=4'b1100;end
                if(speed==1)//�ٶȵ���ʾ
                    begin dm2=8'b01101110;wm2=4'b0001;end//��ʾH,���������ʻ
                else if(speed==0)
                    begin dm2=8'b00011100;wm2=4'b0010;end//��ʾL,���������ʻ
                if(shift==1)//Ư��ģʽ
                    begin
                        wm2=4'b0000;
                        if(dire[1]==1&&dire[0]==1)//��Ư����ʾ����CC
                            begin dm2=8'b11110000;wm2=4'b1100;end
                        else if(dire[2]==1&&dire[0]==1)//��Ư����ʾ����CC
                            begin dm2=8'b10011100;wm2=4'b1100;end
                    end
                end
            else if(door1 == 0 && close == 1)//���������ҳ���δ�غ�
            begin             
                if(divclk2 == 0)
                begin
                    left = 3'b111;right = 3'b111;
                    sw1=4'b1011;sw2=4'b1011;wm2=4'b0000;
                end
                if(divclk2 == 1)
                begin 
                    sw1=4'b1011;sw2=4'b1011;wm2=4'b0000;
                    left = 3'b000;right = 3'b000;
                end
            end  
            else if(door1==0&&close==0)//����δ�����ҳ���δ�غã�����ģʽ
            begin 
                sw1=4'b1111;sw2=4'b1111;left=3'b000;right=3'b000;//β��Ϩ�𣬾�������˸
                if(count[26]==0&&count[25]==0)
                    begin xklsd=8'b10000001;end
                else if(count[26]==0&&count[25]==1)
                    begin xklsd=8'b01000010;end
                else if(count[26]==1&&count[25]==0)
                    begin xklsd=8'b00100100;end
                else
                    begin xklsd=8'b00011000;end
            end
            else if(door1==1&&close==0)//����δ���������Źغ�
            begin xklsd=8'b00000000;wm2=4'b0000;left=3'b000;right=3'b000;sw1=4'b1111;sw2=4'b1111;end
            
            /*ָʾ�����岿��*/
            if(double_flash==0)//�������޹���
            begin
                if(close==1 && door1 == 1)//���������ҳ��Źغ�
                begin
                    if(back==0)
                    begin
                    if(dire==4'b0000||dire==4'b0001)//ǰ�л��߲����з���,β�Ʋ���
                        begin left=3'b000;right=3'b000;end
                    else
                    begin
                        if(dire[1]==1)//��ѭ��������β��
                        begin 
                            if(count[26]==0&&count[25]==0)
                            begin left=3'b001;right=3'b000; end
                            else if(count[26]==0&&count[25]==1)
                            begin left=3'b010;right=3'b000; end
                            else if(count[26]==1&&count[25]==0)
                            begin left=3'b100;right=3'b000; end
                            else if(count[26]==1&&count[25]==1)
                            begin left=3'b000;right=3'b000; end
                        end
                        else if(dire[2]==1)//��ѭ��������β��
                        begin 
                            if(count[26]==0&&count[25]==0)
                            begin right=3'b100;left=3'b000; end
                            else if(count[26]==0&&count[25]==1)
                            begin right=3'b010;left=3'b000; end
                            else if(count[26]==1&&count[25]==0)
                            begin right=3'b001;left=3'b000; end
                            else if(count[26]==1&&count[25]==1)
                            begin right=3'b000;left=3'b000; end
                        end
                        else if(dire[3]==1)//ɲ��ģʽ,����β����˸
                        begin 
                            if(count[25]==0)
                            begin left=3'b000;right=3'b000;end
                            else
                            begin left=3'b110;right=3'b011;end
                        end
                    end
                    end
                    else if(back==1)//����ģʽ
                    begin //����countʵ����β����ѭ������β����ѭ��
                        if(count[26]==0&&count[25]==0)
                            begin right=3'b001;left=3'b100; end
                        else if(count[26]==0&&count[25]==1)
                            begin right=3'b010;left=3'b010; end
                        else if(count[26]==1&&count[25]==0)
                            begin right=3'b100;left=3'b001; end
                        else if(count[26]==1&&count[25]==1)
                            begin right=3'b000;left=3'b000; end
                    end
                end      
            end
            else//����˫��ģʽ
            begin
                if(count[25]==1)//����count��Ƶ
                    begin left=3'b000;right=3'b000;end//ָʾ��ȫ��
                else if(count[25]==0)
                    begin left=3'b111;right=3'b111;end//ָʾ��ȫ��
            end
       end    
       always @(disp_dat)
       begin            
         case (disp_dat)//��Ӧ״̬��ʾ����
            4'b0000:dm1=8'b11111100;//0
            4'b0001:dm1=8'b01100000;//1
            4'b0010:dm1=8'b11001010;//2
            4'b0011:dm1=8'b11110010;//3
            4'b0100:dm1=8'b01100110;//4
            4'b0101:dm1=8'b10110110;//5
            4'b0110:dm1=8'b10111110;//6
            4'b0111:dm1=8'b11100000;//7
            4'b1000:dm1=8'b11111110;//8
            4'b1001:dm1=8'b11110110;//9
            4'b1010:dm1=8'b11001110;//P
            4'b1011:dm1=8'b10011110;//E
            4'b1100:dm1=8'b00111110;//b
            default:dm1=8'b00000000;//����
        endcase
      end   
endmodule
