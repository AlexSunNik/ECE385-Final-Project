//-------------------------------------------------------------------------
//      Mem2IO.vhd                                                       --
//      Stephen Kempf                                                    --
//                                                                       --
//      Revised 03-15-2006                                               --
//              03-22-2007                                               --
//              07-26-2013                                               --
//              03-04-2014                                               --
//              02-13-2017                                               --
//                                                                       --
//      For use with ECE 385 Experiment 6                                --
//      UIUC ECE Department                                              --
//-------------------------------------------------------------------------


module  SRAM_Controller ( 	input logic Clk, Reset,
					input logic [19:0]  ADDR,
					input logic [15:0] Data_Write,
					input logic CE, UB, LB, OE, WE,
					output logic [15:0] Data_Read,
					inout[15:0] Data_SDRAM);

	// Always read data from the bus
	logic[15:0] Data_read_buffer, Data_write_buffer;
	always_ff @ (posedge Clk)
    begin 
		Data_read_buffer <= Data_SDRAM;
		Data_write_buffer <= Data_Write;
    end


// Drive (write to) Data bus only when tristate_output_enable is active.
assign Data_SDRAM = (WE && ~OE) ? Data_write_buffer : {N{1'bZ}};

assign Data_Read = Data_read_buffer;


endmodule
