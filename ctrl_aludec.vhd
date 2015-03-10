LIBRARY IEEE; USE IEEE.STD_LOGIC_1164.ALL;

ENTITY ctrl_aludec IS
PORT( 
	  Funct			: IN  STD_LOGIC_VECTOR(5 DOWNTO 0);
	  ALUOp			: IN  STD_LOGIC_VECTOR(1 DOWNTO 0);
	  ALUControl	: OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
	  Vdd, Vss		: IN  STD_LOGIC);
END ctrl_aludec;

ARCHITECTURE behave OF ctrl_aludec IS
BEGIN
	PROCESS(Funct, ALUOp) BEGIN
		IF ALUOp = "00" THEN
			ALUControl <= "010";
			
		ELSIF ALUOp = "01" THEN
			ALUControl <= "110";
		
		ELSIF ALUOp = "10" THEN
			CASE Funct IS
				WHEN "100000" => ALUControl <= "010";
				WHEN "100010" => ALUControl <= "110";
				WHEN "100100" => ALUControl <= "000";
				WHEN "100101" => ALUControl <= "001";
				WHEN "101010" => ALUControl <= "111";
				WHEN OTHERS   => ALUControl <= "X";
			END CASE;
		
		ELSE
			ALUControl <= "X";
		END IF;
	END PROCESS;
END;
