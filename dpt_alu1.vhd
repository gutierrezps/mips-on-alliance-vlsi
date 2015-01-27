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

architecture behave of dpt_alu1 is

	signal res_and, res_or:  STD_LOGIC;
	signal res_add, bb:  STD_LOGIC;

begin
	bb <= B WHEN Binv = "0" ELSE NOT B;
	
	res_and <= A AND bb;
	res_or  <= A OR bb;
	--res_add <= ( (NOT Cin) AND (A XOR bb) ) OR ( Cin AND NOT (A XOR bb) );
	res_add <= A XOR B XOR Cin;
	
	with Op select
		Res <= res_and WHEN "00",
			   res_or  WHEN "01",
			   res_add WHEN "10",
			   Less    WHEN "11";
	
	Cout <= (A AND bb) OR (Cin AND (A XOR bb));
	Set <= res_add;
	
end;