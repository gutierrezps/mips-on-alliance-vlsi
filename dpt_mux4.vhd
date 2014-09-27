library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_arith.ALL;

entity dpt_mux4 is
port( d0, d1 : in  STD_LOGIC_VECTOR(31 DOWNTO 0);
	  d2, d3 : in  STD_LOGIC_VECTOR(31 DOWNTO 0);
	  s      : in  STD_LOGIC_VECTOR( 1 DOWNTO 0);
	  y      : out STD_LOGIC_VECTOR(31 DOWNTO 0);
  	  vdd, vss : in  STD_LOGIC);
end dpt_mux4;

architecture behave of dpt_mux4 is

begin

	process(d0, d1, d2, d3, s) begin

		case s is
			when "00" => y <= d0;
			when "01" => y <= d1;
			when "10" => y <= d2;
			when "11" => y <= d3;
		end case;
		
	end process;
end;
