library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_arith.ALL;

entity dpt_alu_1b is
port( A, B     : in  STD_LOGIC;
	  Cin	   : in STD_LOGIC;
	  F        : in  STD_LOGIC_VECTOR( 1 DOWNTO 0);
	  Y, Cout  : out STD_LOGIC;
	  Vdd, Vss : in  STD_LOGIC);
end dpt_alu_1b;

architecture behave of dpt_alu_1b is

	signal y_and, y_or:  STD_LOGIC;
	signal y_add:  STD_LOGIC;

begin
	y_and <= A AND B;
	y_or  <= A OR  B;
	y_add <= ( (NOT Cin) AND (A XOR B) ) OR ( Cin AND NOT (A XOR B) );
	
	with F select
		Y <= y_and WHEN "00",
			 y_or  WHEN "01",
			 y_add WHEN "10";
	
	Cout <= (A AND B) OR (Cin AND (A XOR B));

end;