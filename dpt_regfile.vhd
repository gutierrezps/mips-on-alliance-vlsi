library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_UNSIGNED.all;

entity dpt_regfile is
port( CLK, WE3      : in STD_LOGIC;
	  RA1, RA2, WA3 : in STD_LOGIC_VECTOR(4 downto 0);
	  WD3           : in STD_LOGIC_VECTOR(31 downto 0);
	  RD1, RD2      : out STD_LOGIC_VECTOR(31 downto 0);
	  Vdd, Vss		: in STD_LOGIC);
end dpt_regfile;

architecture behave of dpt_regfile is
	type ramtype is array (31 downto 0) of STD_LOGIC_VECTOR (31 downto 0);
	signal mem: ramtype;

begin
	process( CLK ) begin
		if rising_edge(CLK) and WE3 = '1' then
            mem( CONV_INTEGER(WA3) ) <= WD3;
        end if;
    end process;
    
    process( RA1, RA2, mem ) begin
        if( CONV_INTEGER(RA1) = 0 ) then
            RD1 <= X"00000000"; 
        else
            RD1 <= mem( CONV_INTEGER(RA1) );
        end if;

        if( CONV_INTEGER(RA2) = 0 ) then
            RD2 <= X"00000000";
        else
            RD2 <= mem( CONV_INTEGER(RA2) );
        end if;
	end process;
end;
