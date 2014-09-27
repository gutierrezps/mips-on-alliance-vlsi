library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity dpt_buffer is
port( a : in STD_LOGIC;
	  y : out STD_LOGIC;
	  vdd, vss: in STD_LOGIC);
end dpt_buffer;

architecture behave of dpt_buffer is

begin
	y <= a;
end;
