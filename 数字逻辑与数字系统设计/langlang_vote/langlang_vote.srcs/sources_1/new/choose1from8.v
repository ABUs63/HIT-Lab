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
    output reg choice,//8选1数据选择器选择结果
    input [2:0]f,//选择器选择控制端
    input [7:0]d//选择器数据输入端
    );
    always@*
        begin
            case (f)//根据选择控制端信号选相应结果
                 3'b000:choice=d[0];//0人同意
                 3'b001:choice=d[1];//1人同意
                 3'b010:choice=d[2];//1人同意
                 3'b011:choice=d[3];//2人同意
                 3'b100:choice=d[4];//1人同意
                 3'b101:choice=d[5];//2人同意
                 3'b110:choice=d[6];//2人同意
                 3'b111:choice=d[7];//3人同意
                 default;
            endcase
        end
endmodule
