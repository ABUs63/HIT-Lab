`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/17 11:07:56
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
    wire sum,cout;
    reg a,b,c;
    initial
        begin a=0;b=0;c=0;
     end
    always #1 {a,b,c}={a,b,c}+1;
    fulladd my(a,b,c,sum,cout);
endmodule
