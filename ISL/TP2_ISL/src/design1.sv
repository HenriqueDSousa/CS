module LFSR1 (clk, D, Q);
    
    input clk;
    input [1:9] D;
    output reg [1:9] Q;

    always @(D)
      begin
        Q = D;
      end

    always @(posedge clk) 
       begin
         	  Q[1] <= (Q[9] ^ Q[5]);
            Q[2] <= Q[1];
            Q[3] <= Q[2];
            Q[4] <= Q[3];
            Q[5] <= Q[4];
            Q[6] <= Q[5];
            Q[7] <= Q[6];
            Q[8] <= Q[7];
            Q[9] <= Q[8];
       end

endmodule