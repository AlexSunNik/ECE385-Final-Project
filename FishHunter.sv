module FishHunter( input CLOCK_50,
				input        [3:0]  KEY,
				input			[17:0] SW,
             //output logic [6:0]  HEX0, HEX1,
				 output logic [17:0] LEDR,
				 output logic [7:0] LEDG,
             // VGA Interface 
             output logic [7:0]  VGA_R,        //VGA Red
                                 VGA_G,        //VGA Green
                                 VGA_B,        //VGA Blue
             output logic        VGA_CLK,      //VGA Clock
                                 VGA_SYNC_N,   //VGA Sync signal
                                 VGA_BLANK_N,  //VGA Blank signal
                                 VGA_VS,       //VGA virtical sync signal
                                 VGA_HS,       //VGA horizontal sync signal
				
				// CY7C67200 Interface
             inout  wire  [15:0] OTG_DATA,     //CY7C67200 Data bus 16 Bits
             output logic [1:0]  OTG_ADDR,     //CY7C67200 Address 2 Bits
             output logic        OTG_CS_N,     //CY7C67200 Chip Select
                                 OTG_RD_N,     //CY7C67200 Write
                                 OTG_WR_N,     //CY7C67200 Read
                                 OTG_RST_N,    //CY7C67200 Reset
             input               OTG_INT,      //CY7C67200 Interrupt
				
				inout I2C_SDAT, I2C_SCLK,
				output logic AUD_XCK,AUD_BCLK,
				output logic AUD_DACLRCK, AUD_DACDAT,
				input [7:0] FL_DQ,
				output logic [22:0] FL_ADDR,
				output logic FL_CE_N, FL_OE_N, FL_WE_N, FL_RST_N, FL_WP_N,
				
				output logic SRAM_CE_N, SRAM_UB_N, SRAM_LB_N, SRAM_OE_N, SRAM_WE_N,
            output logic [19:0] SRAM_ADDR,
            inout wire [15:0] SRAM_DQ,
				output logic [12:0] DRAM_ADDR,
				output logic [1:0]  DRAM_BA,
				output logic        DRAM_CAS_N,
				output logic        DRAM_CKE,
				output logic        DRAM_CS_N,
				inout  logic [31:0] DRAM_DQ,
				output logic [3:0]  DRAM_DQM,
				output logic        DRAM_RAS_N,
				output logic        DRAM_WE_N,
				output logic        DRAM_CLK);
				
					
				assign LEDR = {18{1'b0}};
				
				logic Reset_h;
				always_ff @ (posedge Clk) begin
					Reset_h <= ~(KEY[0]);        // The push buttons are active low
					//Draw_Start <= ~(KEY[1]);
				end
				logic Clk;
				assign Clk = CLOCK_50;
				
				/***SRAM Related**/
				logic [15:0] Data_Write;
				assign SRAM_CE_N = 1'b0;
				assign SRAM_UB_N = 1'b0;
				assign SRAM_LB_N = 1'b0;
				assign SRAM_OE_N = 1'b0;
				assign SRAM_WE_N = 1'b1;
				logic [15:0] Data_Read;
				logic [10:0] DrawX,DrawY;
				//logic is_Fish;
				//logic [9:0] Fish_X_Pos_Out, Fish_Y_Pos_Out;
				//assign ColorIdx = Data_Read;
				
				/***Frame Buffer Related**/
				logic We;
				logic [10:0]AddrX, AddrY;
				logic [10:0] Read_AddrX, Read_AddrY;
				logic [7:0] ColorIdxIn;
				logic [7:0] ColorIdxOut;
				logic [15:0] ColorIdx;
				/***Blitter Related**/
				logic Draw_Start;
				logic [10:0] AddrX_Start, AddrY_Start, AddrX_Stop, AddrY_Stop;
				logic [10:0] SRAM_ADDR_X_Start, SRAM_ADDR_Y_Start;
					
				logic Draw_Done;
				logic Frame_Done;
				//assign ColorIdx = 16'h0001;
				//assign LEDG[0] = Frame_Done;
				logic [7:0] power;
				assign LEDG = power;
				
				assign Read_AddrX = DrawX;
				assign Read_AddrY = DrawY;
				assign ColorIdx = {{8{1'b0}},ColorIdxOut};
				//For test
				/*
				assign AddrX_Start = 0;
				assign AddrY_Start = 0;
				assign AddrX_Stop = 10'd640;
				assign AddrY_Stop = 10'd480;
				assign SRAM_ADDR_X_Start  = 0;
				assign SRAM_ADDR_Y_Start = 0;
				*/
				
				logic [7:0] Color_Filter;
				assign Color_Filter = 8'h01;
				
				logic [1:0] hpi_addr;
				 logic [15:0] hpi_data_in, hpi_data_out;
				 logic hpi_r, hpi_w, hpi_cs, hpi_reset;
				 
				 logic [7:0] keycode;
				
					hpi_io_intf hpi_io_inst(
                            .Clk(Clk),
                            .Reset(Reset_h),
                            // signals connected to NIOS II
                            .from_sw_address(hpi_addr),
                            .from_sw_data_in(hpi_data_in),
                            .from_sw_data_out(hpi_data_out),
                            .from_sw_r(hpi_r),
                            .from_sw_w(hpi_w),
                            .from_sw_cs(hpi_cs),
                            .from_sw_reset(hpi_reset),
                            // signals connected to EZ-OTG chip
                            .OTG_DATA(OTG_DATA),    
                            .OTG_ADDR(OTG_ADDR),    
                            .OTG_RD_N(OTG_RD_N),    
                            .OTG_WR_N(OTG_WR_N),    
                            .OTG_CS_N(OTG_CS_N),
                            .OTG_RST_N(OTG_RST_N)
    );
				
				
				lab7_soc lab7_qsystem(
				.clk_clk(CLOCK_50),								// Clock input
				.reset_reset_n(KEY[0]),							// Reset key
				.sdram_wire_addr(DRAM_ADDR),					// sdram_wire.addr
				.sdram_wire_ba(DRAM_BA),						// sdram_wire.ba
				.sdram_wire_cas_n(DRAM_CAS_N),				// sdram_wire.cas_n
				.sdram_wire_cke(DRAM_CKE),						// sdram_wire.cke
				.sdram_wire_cs_n(DRAM_CS_N),					// sdram.cs_n
				.sdram_wire_dq(DRAM_DQ),						// sdram.dq
				.sdram_wire_dqm(DRAM_DQM),						// sdram.dqm
				.sdram_wire_ras_n(DRAM_RAS_N),				// sdram.ras_n
				.sdram_wire_we_n(DRAM_WE_N),					// sdram.we_n
				.sdram_clk_clk(DRAM_CLK),
				.blitter_drawing_core_0_export_data_data_read(Data_Read),  // blitter_drawing_core_0_export_data.data_read
				.blitter_drawing_core_0_export_data_addrx(AddrX),      //                                   .addrx
				.blitter_drawing_core_0_export_data_addry(AddrY),      //                                   .addry
				.blitter_drawing_core_0_export_data_sram_addr(SRAM_ADDR),  //                                   .sram_addr
				.blitter_drawing_core_0_export_data_coloridxin(ColorIdxIn), //                                   .coloridxin
				.blitter_drawing_core_0_export_data_we(We),
				.blitter_drawing_core_0_export_data_frame_done(Frame_Done),
				.keycode_export(keycode),
				.power_wire_export(power), 		
			  .otg_hpi_address_export(hpi_addr),
			  .otg_hpi_data_in_port(hpi_data_in),
			  .otg_hpi_data_out_port(hpi_data_out),
			  .otg_hpi_cs_export(hpi_cs),
			  .otg_hpi_r_export(hpi_r),
			  .otg_hpi_w_export(hpi_w),
			  .otg_hpi_reset_export(hpi_reset)
				//.blitter_drawing_core_0_export_data_color_filter(Color_Filter) 				
				);
				
				
				audioController ac0(.*, .clk(CLOCK_50),.reset(~Reset_h),.SW0(SW[17]),.SDIN(I2C_SDAT),.SCLK(I2C_SCLK),.USB_clk(AUD_XCK),
				.BCLK(AUD_BCLK),.DAC_LR_CLK(AUD_DACLRCK),.DAC_DATA(AUD_DACDAT));
				
				vga_clk vga_clk_instance(.inclk0(Clk), .c0(VGA_CLK));
				VGA_controller vga_controller_instance(.*,.Reset(Reset_h));
				//FrameBuffer fb0(.*);
				FrameBufferController fbc0(.*);
				//blitter blitter0(.*);
				//fish fish0(.*,.frame_clk(VGA_VS));
				//AddressConverter AC0(.*);
				SRAM_Controller SC0(.*);
				color_palette cp0(.*,.ColorIdx(ColorIdxOut));
				
				//HexDriver hex_inst_0 (keycode[3:0], HEX0);
				//HexDriver hex_inst_1 (keycode[7:4], HEX1);

endmodule
