/******************************************************************************
* Copyright (C) 2025 Conner Davis
* SPDX-License-Identifier: MIT
*
* This file is part of SoC_Timer_32_IP_Block project, distributed under the MIT license
* see LICENSE file in the project root for full license information.
******************************************************************************/
//timer32.sv


`timescale 1ns / 1ps

module timer32 (
    input logic clk,
    input logic reset,
    input logic [31:0] din,
    output logic [31:0] dout,
    input logic wren,
    input logic rden,
    input logic [1:0] addr
);
    // must have this initial value
    parameter PERIOD = 32'h0000000F;
    parameter ENBIT = 1'b0;
    logic [31:0] timer, TMR_dout, period, PR_dout;
    logic TMR_flag, TMR_en, timer_match, toggle_flag;
    
    always_ff @(posedge clk or posedge reset) begin
        if (reset) begin
            TMR_dout = 0;
            PR_dout = PERIOD;
        end else begin
            if(timer_match) begin
                TMR_dout = 0;
            end else if (wren && addr==0) begin
                TMR_dout = din;
            end else if (TMR_en) begin
                TMR_dout = TMR_dout + 1;
            end
            
            if(wren && addr==1) begin
                PR_dout = din;
            end
            
            timer_match = (PR_dout == TMR_dout) ? 1 : 0;
        end
    end
    
    always_ff @(posedge clk or posedge reset) begin
        if (reset) begin
            TMR_en = ENBIT;
            TMR_flag = 0;
            toggle_flag = 0;
        end else begin
            if (timer_match) begin
                TMR_flag <= 1;
                toggle_flag <= ~toggle_flag;
            end else if (wren && addr==2) begin
                TMR_en <= din[0];
                TMR_flag <= din[1];
                toggle_flag <= din[2];
            end 
            if (rden && addr==2) begin
                TMR_flag <= 0;
            end
        end
    end
    
    always_comb begin
        if (rden) begin
            case (addr)
                2'b00: begin
                    dout = TMR_dout;
                end
                2'b01: begin
                    dout = PR_dout;
                end
                2'b10: begin
                    dout = {29'b0, toggle_flag, TMR_flag, TMR_en};
                end
                default: begin
                    dout = 32'b0;
                end 
            endcase
        end else begin
            dout = 32'b0;
        end
    end     
endmodule
