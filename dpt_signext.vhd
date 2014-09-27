library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity dpt_signext is
port( a : in  STD_LOGIC_VECTOR(15 DOWNTO 0);
	  y : out STD_LOGIC_VECTOR(31 DOWNTO 0);
	  vdd, vss: in STD_LOGIC);
end dpt_signext;

architecture behave of dpt_signext is

begin
	y(31 downto 16) <= X"FFFF" WHEN a(15) = '1' ELSE X"0000";
	y(15 downto 0) <= a;
end;
