`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/18 22:34:06
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
    wire choice;
    reg s1,s2,s3;
     initial
        begin
            s1=0;
            s2=0;
            s3=0;
        end
      always #20{s1,s2,s3}={s1,s2,s3}+1;
    vote my(choice,s1,s2,s3);
endmodule
