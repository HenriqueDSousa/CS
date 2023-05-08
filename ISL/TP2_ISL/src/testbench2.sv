module LFSR2_test();

    integer fOut;
    reg clk;
    reg [1:11] in;
    wire [1:11] out;

    LFSR2 LFSR(clk, in, out);

    initial 
      begin

        fOut = $fopen("output.out", "w");
        if (fOut) $display("File opened");
        else $display("File not opened");
        clk=1'b0;
		    in = 1;
        
        repeat(800)
          begin
            #1 clk = ~clk;

            if (clk == 1)
              begin
                  $fwrite(fOut, "%d ", out);
              end
            
          end
        
        $fclose(fOut);
      end

endmodule