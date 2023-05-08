module LFSR3 (clk, D, Q);
    
    input clk;
    input [1:17] D;
    output reg [1:17] Q;

    always @(D)
      begin
        Q = D;
      end

    always @(posedge clk) 
       begin
         	  Q[1] <= (Q[14] ^ Q[17]);
            Q[2] <= Q[1];
            Q[3] <= Q[2];
            Q[4] <= Q[3];
            Q[5] <= Q[4];
            Q[6] <= Q[5];
            Q[7] <= Q[6];
            Q[8] <= Q[7];
            Q[9] <= Q[8];
            Q[10] <= Q[9];
            Q[11] <= Q[10];
            Q[12] <= Q[11];
            Q[13] <= Q[12];
            Q[14] <= Q[13];
            Q[15] <= Q[14];
            Q[16] <= Q[15];
            Q[17] <= Q[16];
       end

endmodule