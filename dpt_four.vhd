library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity dpt_four is
port( y : out STD_LOGIC_VECTOR(31 DOWNTO 0);
	  vdd, vss: in STD_LOGIC);
end dpt_four;

architecture behave of dpt_four is

begin
	y <= X"00000004";
end;
