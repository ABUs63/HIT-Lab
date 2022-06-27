`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/17 10:17:48
// Design Name: 
// Module Name: testadd
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

module testadd;
    reg a,b,cin;
    wire sum,cout;

    initial
      begin
          a=0;b=0;cin=0;
      end
    always #20 {a,b,cin}={a,b,cin}+1;
   fulladd my(a,b,cin,sum,cout);
   
endmodule
