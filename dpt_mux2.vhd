library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity dpt_mux2 is
port( d0, d1 : in  STD_LOGIC_VECTOR(31 DOWNTO 0);
	  s      : in  STD_LOGIC;
	  y      : out STD_LOGIC_VECTOR(31 DOWNTO 0);
  	  vdd, vss : in  STD_LOGIC);
end dpt_mux2;

architecture behave of dpt_mux2 is

begin
	y <= d0 when s = '0' else d1;
end;
