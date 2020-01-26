//Blitter_Interface IP Core
//Copyright: Alex Sun, Churan He

module avalon_blitter_interface(input logic CLK,
	
	// Avalon Reset Input
	input logic RESET,
	//input  logic [1:0] AVL_ADDR,			// Avalon-MM Address
	input  logic [31:0] DrawEnable,	// Avalon-MM Write Data
	output logic [31:0] X,	// Avalon-MM Read Data
	output logic [31:0] Y,
	output logic [31:0] PatternIdx,
);

//Register 0: X
//Register 1: Y
//Register 2: PatternIdx
//Register 4: Blank

register X_reg();
register Y_reg();
register PatternIdx_reg();
register DrawEnable();


endmodule

/*
always_ff @(posedge CLK)
begin
	if(RESET)
		begin
			
		end
	else if(AVL_WRITE && AVL_CS)
			reg_file[AVL_ADDR] <= AVL_WRITEDATA;
end
assign AVL_READDATA = (AVL_CS && AVL_READ) ? reg_file[AVL_ADDR] : 32'b0;*/