library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_arith.ALL;

entity dpt_alu_1b is
port( A, B     : in  STD_LOGIC;
	  Cin, Less: in STD_LOGIC;
	  Binv     : in STD_LOGIC;
	  Op       : in  STD_LOGIC_VECTOR( 1 DOWNTO 0);
	  Res, Cout: out STD_LOGIC;
	  Set      : out STD_LOGIC;
	  Vdd, Vss : in  STD_LOGIC);
end dpt_alu_1b;

architecture behave of dpt_alu_1b is

	signal res_and, res_or:  STD_LOGIC;
	signal res_add, bb:  STD_LOGIC;

begin
	bb <= B WHEN Binv = "0" ELSE NOT B;
	
	res_and <= A AND bb;
	res_or  <= A OR bb;
	res_add <= ( (NOT Cin) AND (A XOR bb) ) OR ( Cin AND NOT (A XOR bb) );
	
	with Op select
		Res <= res_and WHEN "00",
			   res_or  WHEN "01",
			   res_add WHEN "10",
			   Less    WHEN "11";
	
	Cout <= (A AND bb) OR (Cin AND (A XOR bb));
	Set <= res_add;
	
end;