library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_arith.ALL;

entity dpt_alu32_zero is
port( Res      : in  STD_LOGIC_VECTOR(31 DOWNTO 0);
	  Zero	   : out STD_LOGIC;
	  Vdd, Vss : in  STD_LOGIC);
end dpt_alu32_zero;

architecture behave of dpt_alu32_zero is

begin
	Zero <= (Res = 0);
end;