library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_arith.ALL;
use IEEE.STD_LOGIC_UNSIGNED.all;

entity dpt_regfile is
port( CLK, WE3      : in STD_LOGIC;
	  A1, A2, A3    : in STD_LOGIC_VECTOR(4 downto 0);
	  WD3           : in STD_LOGIC_VECTOR(31 downto 0);
	  RD1, RD2      : out STD_LOGIC_VECTOR(31 downto 0);
	  Vdd, Vss		: in STD_LOGIC);
end dpt_regfile;

architecture behave of dpt_regfile is
	type ramtype is array (31 downto 0) of STD_LOGIC_VECTOR (31 downto 0);
	signal mem: ramtype;

begin
	process(CLK) begin
		if rising_edge(CLK) then
            if (conv_integer(A1) = 0) then
                RD1 <= X"00000000"; 
            else
                RD1 <= mem(conv_integer(A1));
            end if;

            if (conv_integer(A2) = 0) then
                RD2 <= X"00000000";
            else
                RD2 <= mem(conv_integer(A2));
            end if;

            if WE3 = '1' then
                mem(CONV_INTEGER(A3)) <= WD3;
            end if;
        end if;
	end process;
end;
