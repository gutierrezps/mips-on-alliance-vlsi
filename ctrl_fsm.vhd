library IEEE;
use IEEE.Std_Logic_1164.ALL;
use IEEE.Std_Logic_arith.ALL;
use IEEE.Std_Logic_unsigned.ALL;

entity ctrl_fsm is
	port (
		CLK			: in Std_Logic;
		Reset		: in Std_Logic;

		Opcode		: in Std_Logic_Vector(5 downto 0);

		IorD		: out Std_Logic;
		IRWrite		: out Std_Logic;
		RegDst		: out Std_Logic;
		MemtoReg	: out Std_Logic;
		RegWrite	: out Std_Logic;
		ALUSrcA		: out Std_Logic;
		ALUSrcB		: out Std_Logic_Vector(1 downto 0);
		ALUOp		: out Std_Logic_Vector(1 downto 0);

		PCSrc		: out Std_Logic_Vector(1 downto 0);
		PCWrite		: out Std_Logic;
		Branch		: out Std_Logic;
		
		MemWrite	: out Std_Logic;

		State		: out Std_Logic_Vector(3 downto 0);
		
		Vdd			: in Std_Logic;
		Vss			: in Std_Logic
	);
end ctrl_fsm;

architecture behave of ctrl_fsm is
	signal nextState: 	Std_Logic_Vector(3 downto 0);
	
	begin

	process(CLK, Reset) begin
	
		if Reset = '1' then
		
			State <= "0";
			nextState <= "0";
            
			IorD <= '0';
			ALUSrcA <= '0';
			ALUSrcB <= "01";
			ALUOp <= "00";
			PCSrc <= "00";
			IRWrite	<= '1';
			PCWrite <= '1';
			RegWrite <= '0';
			MemWrite <= '0';
			Branch <= '0';
			

		elsif rising_edge(CLK) then
		
		State <= nextState;
		
		case nextState is 


		-- Fetch
		when "0000" =>
			
			nextState <= "0001";
			
			IorD <= '0';
			ALUSrcA <= '0';
			ALUSrcB <= "01";
			ALUOp <= "00";
			PCSrc <= "00";
			IRWrite	<= '1';
			PCWrite <= '1';
			RegWrite <= '0';
			MemWrite <= '0';
			Branch <= '0';

		-- Decode
		when "0001" =>
			PCWrite <= '0';
			IRWrite	<= '0';
			
			ALUSrcA <= '0';
			ALUSrcB <= "11";
			ALUOp <= "00";
		
			
			if((OpCode = 35 ) OR (OpCode = 43)) then	-- LW or SW
				nextState <= "0010";
			elsif(OpCode = 0) then		-- R-type
				nextState <= "0110";
			elsif(OpCode = 4) then 		-- Branch
				nextState <= "1000";
			elsif(OpCode = 8) then		-- Addi
				nextState <= "1001";
			elsif(OpCode = 2) then		-- Jump
				nextState <= "1011";
			end if;

	
		--MemAdr
		when "0010" =>
			ALUSrcA <= '1';
			ALUSrcB <= "10";
			ALUOp <= "00";
			
			if(OpCode = 35 ) then
				nextState <= "0011";
			elsif(OpCode = 43) then
				nextState <= "0101";
			end if;		
		
		--MemRead	
		when "0011" =>
			nextState <= "0100";
		
			IorD <= '1';
			
		--Mem WriteBack
		when "0100" =>
			nextState <= "0000";
			
			RegDst <= '0';
	        MemtoReg <= '1';
	        RegWrite <= '1';
			
		--Mem Write				
		when "0101" =>
			nextState <= "0000";
						
			IorD <= '1';
	        MemWrite <= '1';
			
		--Execute	
		when "0110" =>				
			nextState <= "0111";
			
			ALUSrcA <= '1';
			ALUSrcB <= "00";
			ALUOp <= "10";

		-- ALU Writeback
		when "0111" =>
			nextState <= "0000";
		
			RegDst <= '1';
	        MemtoReg <= '0';
	        RegWrite <= '1';

		-- Branch
		when "1000" =>
			nextState <= "0000";
		
			ALUSrcA <= '1';
			ALUSrcB <= "00";
			ALUOp <= "01";
			PCSrc <= "01";
			Branch <= '1';

		-- ADDI Execute
		when "1001" =>
			nextState <= "1010";
		
			ALUSrcA <= '1';
			ALUSrcB <= "10";
			ALUOp <= "00";

		-- ADDI Writeback
		when "1010" =>
			nextState <= "0000";
		
			RegDst <= '0';
	        MemtoReg <= '0';
	        RegWrite <= '1';

		when "1011" =>
			PCSrc <= "10";
			PCWrite <= '1';
			
			nextState <= "0000";
			
		when others =>
			nextState <= "0000";
	 
		end case;
		
--		elsif falling_edge(CLK) then State <= nextState;
		end if;
		
	end process;
	
end behave;
