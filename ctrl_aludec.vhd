library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity ctrl_aludec is
port( 
	  funct			: in STD_LOGIC_VECTOR(5 downto 0);
	  aluop			: in STD_LOGIC_VECTOR(1 downto 0);
	  alucontrol	: out STD_LOGIC_VECTOR(2 downto 0);
	  vdd, vss		: in STD_LOGIC);
end ctrl_aludec;

architecture behave of ctrl_aludec is

begin
	process(funct, aluop) begin
		if aluop = "00" then
			alucontrol <= "010";
			
		elsif aluop = "01" then
			alucontrol <= "110";
			
		else
			case funct is
				when "100000" => alucontrol <= "010";
				when "100010" => alucontrol <= "110";
				when "100100" => alucontrol <= "000";
				when "100101" => alucontrol <= "001";
				when "101010" => alucontrol <= "111";
				when others   => alucontrol <= "X";
			end case;
		end if;
	end process;

end;
