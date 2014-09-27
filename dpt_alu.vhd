library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_arith.ALL;

entity dpt_alu is
port( a, b     : in  STD_LOGIC_VECTOR(31 DOWNTO 0);
	  ctrl     : in  STD_LOGIC_VECTOR( 2 DOWNTO 0);
	  res      : out STD_LOGIC_VECTOR(31 DOWNTO 0);
	  zero     : out STD_LOGIC;
	  vdd, vss : in  STD_LOGIC);
end dpt_alu;

architecture behave of dpt_alu is

	signal res_add, res_sub: STD_LOGIC_VECTOR(31 DOWNTO 0);
	signal res_and, res_or:  STD_LOGIC_VECTOR(31 DOWNTO 0);

begin
	res_add <= a + b;
	res_sub <= a - b;
	res_and <= a AND b;
	res_or  <= a OR  b;
	
	with ctrl select
		res <= res_and when "000",
			   res_or  when "001",
			   res_add when "010",
			   res_sub when "110",
			   "0" OR res_sub(31) when "111";
	
	zero <= '1' when res = X"00000000" else '0';

end;
