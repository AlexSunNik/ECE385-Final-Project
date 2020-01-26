module testBlitter();


timeunit 10ns;	// Half clock cycle at 50 MHz
			// This is the amount of time represented by #1 
timeprecision 1ns;
				
// A counter to count the instances where simulation results
// do no match with expected results
//integer ErrorCnt = 0;


logic Clk, Reset_h, Draw_Start;
logic [15:0] Data_Read;			//Data read from SRAM
logic [9:0] AddrX_Start, AddrY_Start, AddrX_Stop, AddrY_Stop;
logic [9:0] SRAM_ADDR_X_Start, SRAM_ADDR_Y_Start;
logic [7:0] Color_Filter;
	
logic [9:0] AddrX, AddrY;	//Location on the buffer
logic [19:0] SRAM_ADDR;	//Location on the SRAM
logic [15:0] ColorIdxIn; ////Data input to the Frame Buffer
logic We;
logic Draw_Done;

// Instantiating the DUT
// Make sure the module and signal names match with those in your design
blitter blitter0(.*);	

// Toggle the clock
// #1 means wait for a delay of 1 timeunit
always begin : CLOCK_GENERATION
#1 Clk = ~Clk;
end

initial begin: CLOCK_INITIALIZATION
    Clk = 0;
end 

// Testing begins here
// The initial block is not synthesizable
// Everything happens sequentially inside an initial block
// as in a software program
initial begin: TEST_VECTORS
Reset_h = 1;		// Toggle Rest
AddrX_Start = 0;
AddrY_Start = 0;
AddrX_Stop = 10'd20;
AddrY_Stop = 10'd10;
SRAM_ADDR_X_Start = 10'd300;
SRAM_ADDR_Y_Start = 10'd400;
#2 Reset_h = 0;
#2 Draw_Start = 1;


// Aval and Bval are expected to swap
/*#100 if ({Aval,Bval} != ans)
	 ErrorCnt++;*/

/*
if (ErrorCnt == 0)
	$display("Success!");  // Command line output in ModelSim
else
	$display("%d error(s) detected. Try again!", ErrorCnt);*/
	
end
endmodule
