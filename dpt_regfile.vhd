library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_arith.ALL;
use IEEE.STD_LOGIC_UNSIGNED.all;

entity dpt_regfile is
port( clk, we3      : in STD_LOGIC;
	  a1, a2, a3    : in STD_LOGIC_VECTOR(4 downto 0);
	  wd3           : in STD_LOGIC_VECTOR(31 downto 0);
	  rd1, rd2      : out STD_LOGIC_VECTOR(31 downto 0);
	  vdd, vss		: in STD_LOGIC);
end dpt_regfile;

architecture behave of dpt_regfile is
	type ramtype is array (31 downto 0) of STD_LOGIC_VECTOR (31 downto 0);
	signal mem: ramtype;

begin
	process(a1, a2, mem) begin

		if (conv_integer(a1) = 0) then
			rd1 <= X"00000000"; 
		else
			rd1 <= mem(conv_integer(a1));
		end if;

		if (conv_integer(a2) = 0) then
			rd2 <= X"00000000";
		else
			rd2 <= mem(conv_integer(a2));
		end if;
	end process;

	process(clk) begin
		if rising_edge(clk) and we3 = '1' then
			mem(CONV_INTEGER(a3)) <= wd3;
		end if;
	end process;
end;
