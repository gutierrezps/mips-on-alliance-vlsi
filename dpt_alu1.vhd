LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_arith.ALL;

ENTITY dpt_alu1 IS
PORT( A, B     : IN  STD_LOGIC;
	  Cin, Less: IN  STD_LOGIC;
	  Binv     : IN  STD_LOGIC;
	  Op       : IN  STD_LOGIC_VECTOR( 1 DOWNTO 0);
	  Res, Cout: OUT STD_LOGIC;
	  Set      : OUT STD_LOGIC;
	  Vdd, Vss : IN  STD_LOGIC);
END dpt_alu1;

ARCHITECTURE behave OF dpt_alu1 IS

	SIGNAL res_and, res_or:  STD_LOGIC;
	SIGNAL res_add, BB:  STD_LOGIC;

BEGIN
	BB <= B WHEN Binv = "0" ELSE NOT B;
	
	res_and <= A AND BB;
	res_or  <= A OR BB;
	res_add <= A XOR B XOR Cin;
	
	WITH Op SELECT
		Res <= res_and WHEN "00",
			   res_or  WHEN "01",
			   res_add WHEN "10",
			   Less    WHEN "11";
	
	Cout <= (A AND BB) OR (Cin AND (A XOR BB));
	Set <= res_add;
	
END;