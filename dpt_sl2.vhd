library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity dpt_sl2 is
port( a : in  STD_LOGIC_VECTOR(31 DOWNTO 0);
	  y : out STD_LOGIC_VECTOR(31 DOWNTO 0);
	  vdd, vss: in STD_LOGIC);
end dpt_sl2;

architecture behave of dpt_sl2 is

begin
	y(31 downto 2) <= a(29 downto 0);
	y(1 downto 0) <= "00";
end;
