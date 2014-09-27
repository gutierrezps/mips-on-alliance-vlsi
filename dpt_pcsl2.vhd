library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity dpt_pcsl2 is
port( a : in  STD_LOGIC_VECTOR(25 DOWNTO 0);
	  y : out STD_LOGIC_VECTOR(27 DOWNTO 0);
	  vdd, vss: in STD_LOGIC);
end dpt_pcsl2;

architecture behave of dpt_pcsl2 is

begin
	y(27 downto 2) <= a(25 downto 0);
	y(1 downto 0) <= "00";
end;
