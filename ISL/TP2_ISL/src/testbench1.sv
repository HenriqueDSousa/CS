module LFSR1_test();

    integer fOut;
    reg clk;
    reg [1:9] in;
    wire [1:9] out;

    LFSR1 LFSR(clk, in, out);

    initial 
      begin

        fOut = $fopen("output.out", "w");
        if (fOut) $display("File opened");
        else $display("File not opened");
        clk=1'b0;
		    in = 1;
        
        repeat(500)
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