LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_arith.ALL;

ENTITY dpt_alu IS
PORT( A, B     : IN  STD_LOGIC_VECTOR(31 DOWNTO 0);
	  Ctrl     : IN  STD_LOGIC_VECTOR( 2 DOWNTO 0);
	  Res      : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
	  Zero     : OUT STD_LOGIC;
	  Vdd, Vss : IN  STD_LOGIC);
END dpt_alu;

ARCHITECTURE behave OF dpt_alu IS

	SIGNAL res_add, res_sub: STD_LOGIC_VECTOR(31 DOWNTO 0);
	SIGNAL res_and, res_or:  STD_LOGIC_VECTOR(31 DOWNTO 0);
	SIGNAL res_andnot, res_ornot:  STD_LOGIC_VECTOR(31 DOWNTO 0);

BEGIN
	res_add <= A + B;
	res_sub <= A - B;
	res_and <= A AND B;
	res_or  <= A OR  B;
	res_andnot <= A AND NOT B;
	res_ornot  <= A OR NOT B;
	
	WITH Ctrl SELECT
		Res <= res_and WHEN "000",
				res_or  WHEN "001",
				res_add WHEN "010",
				res_andnot WHEN "100",
				res_ornot  WHEN "101",
				res_sub WHEN "110",
				"0" OR res_sub(31) WHEN "111";
	
	Zero <= '1' WHEN Res = X"00000000" ELSE '0';

END;