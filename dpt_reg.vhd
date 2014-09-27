library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity dpt_reg is
port( clk, rst:	in STD_LOGIC;
	  en: 		in STD_LOGIC;
	  d:		in STD_LOGIC_VECTOR(31 downto 0);
	  q:		out STD_LOGIC_VECTOR(31 downto 0);
  	  vdd, vss:	in STD_LOGIC
	);
end dpt_reg;

architecture sync of dpt_reg is

begin
	process(clk) begin
		if rising_edge(clk) then
			if rst = '1' then
				q <= X"00000000";
			elsif en = '1' then
					q <= d;
			end if;
		end if;
	end process;
end;
