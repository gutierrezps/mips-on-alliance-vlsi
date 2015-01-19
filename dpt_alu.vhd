library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_arith.ALL;

entity dpt_alu is
port( A, B     : in  STD_LOGIC_VECTOR(31 DOWNTO 0);
	  F        : in  STD_LOGIC_VECTOR( 2 DOWNTO 0);
	  Y        : out STD_LOGIC_VECTOR(31 DOWNTO 0);
	  Zero     : out STD_LOGIC;
	  Vdd, Vss : in  STD_LOGIC);
end dpt_alu;

architecture behave of dpt_alu is

	signal y_add, y_sub: STD_LOGIC_VECTOR(31 DOWNTO 0);
	signal y_and, y_or:  STD_LOGIC_VECTOR(31 DOWNTO 0);
	signal y_andnot, y_ornot:  STD_LOGIC_VECTOR(31 DOWNTO 0);

begin
	y_add <= A + B;
	y_sub <= A - B;
	y_and <= A AND B;
	y_or  <= A OR  B;
	y_andnot <= A AND NOT B;
	y_ornot  <= A OR NOT B;
	
	with F select
		Y <= y_and when "000",
			y_or  when "001",
			y_add when "010",
			y_andnot when "100",
			y_ornot  when "101",
			y_sub when "110",
			"0" OR y_sub(31) when "111";
	
	Zero <= '1' when Y = X"00000000" else '0';

end;