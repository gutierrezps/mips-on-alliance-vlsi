library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity dpt_mux4 is
port( d0, d1 : in  STD_LOGIC_VECTOR(31 DOWNTO 0);
	  d2, d3 : in  STD_LOGIC_VECTOR(31 DOWNTO 0);
	  s      : in  STD_LOGIC_VECTOR( 1 DOWNTO 0);
	  y      : out STD_LOGIC_VECTOR(31 DOWNTO 0);
  	  vdd, vss : in  STD_LOGIC);
end dpt_mux4;

architecture behave of dpt_mux4 is

begin
    with s select
        y <= d0 when "00",
             d1 when "01",
             d2 when "10",
             d3 when "11",
             d0 when others;
end;
