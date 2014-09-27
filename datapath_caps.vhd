library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_ARITH.all;

-- Concepção Estruturada de Circuitos Integrados 2014.1
-- Aluno: Gabriel Gutierrez P. Soares - 11218012
-- 29/julho/2014

-- MIPS Multicycle Datapath

entity datapath is
	port( CLK, Reset:		in  STD_LOGIC;

		-- external mem pins
		ReadData:			in  STD_LOGIC_VECTOR(31 downto 0);
		WriteData, MemAdr:	out STD_LOGIC_VECTOR(31 downto 0);
		
		-- control pins
		IorD, IRWrite:		in  STD_LOGIC;
		InstrOp, InstrFunc:	out STD_LOGIC_VECTOR(5 downto 0);
		RegDst, MemtoReg:	in  STD_LOGIC;
		RegWrite, ALUSrcA:	in  STD_LOGIC;
		ALUZero:			out STD_LOGIC;
		PCSrc, PCEn:		in  STD_LOGIC;
		ALUControl:			in  STD_LOGIC_VECTOR(2 downto 0);
		ALUSrcB:			in  STD_LOGIC_VECTOR(1 downto 0);
		Vdd, Vss:			in	STD_LOGIC
	);
end datapath;

architecture struct of datapath is

	component dpt_alu
		port( a, b     : in  STD_LOGIC_VECTOR(31 DOWNTO 0);
			  ctrl     : in  STD_LOGIC_VECTOR( 2 DOWNTO 0);
			  res      : out STD_LOGIC_VECTOR(31 DOWNTO 0);
			  zero     : out STD_LOGIC;
			  Vdd, Vss : in  STD_LOGIC);
	end component;
	
	component dpt_mux2
		port( d0, d1 : in  STD_LOGIC_VECTOR(31 DOWNTO 0);
			  s      : in  STD_LOGIC;
			  y      : out STD_LOGIC_VECTOR(31 DOWNTO 0);
		  	  Vdd, Vss : in  STD_LOGIC);
	end component;
	
	component dpt_mux2_5b
		port( d0, d1 : in  STD_LOGIC_VECTOR(4 DOWNTO 0);
			  s      : in  STD_LOGIC;
			  y      : out STD_LOGIC_VECTOR(4 DOWNTO 0);
		  	  Vdd, Vss : in  STD_LOGIC);
	end component;
	
	component dpt_mux4
		port( d0, d1 : in  STD_LOGIC_VECTOR(31 DOWNTO 0);
			  d2, d3 : in  STD_LOGIC_VECTOR(31 DOWNTO 0);
			  s      : in  STD_LOGIC_VECTOR( 1 DOWNTO 0);
			  y      : out STD_LOGIC_VECTOR(31 DOWNTO 0);
		  	  Vdd, Vss : in  STD_LOGIC);
	end component;
	
	component dpt_reg
		port( clk, rst:	in STD_LOGIC;
			  en: 		in STD_LOGIC;
			  d:		in STD_LOGIC_VECTOR(31 downto 0);
			  q:		out STD_LOGIC_VECTOR(31 downto 0);
		  	  Vdd, Vss:	in STD_LOGIC);
	end component;
	
	component dpt_regfile
		port( clk, we3      : in STD_LOGIC;
			  a1, a2, a3    : in STD_LOGIC_VECTOR(4 downto 0);
			  wd3           : in STD_LOGIC_VECTOR(31 downto 0);
			  rd1, rd2      : out STD_LOGIC_VECTOR(31 downto 0);
			  Vdd, Vss		: in STD_LOGIC);
	end component;
	
	component dpt_signext
		port( a : in  STD_LOGIC_VECTOR(15 DOWNTO 0);
			  y : out STD_LOGIC_VECTOR(31 DOWNTO 0);
			  Vdd, Vss: in STD_LOGIC);
	end component;
	
	component dpt_sl2
		port( a : in  STD_LOGIC_VECTOR(31 DOWNTO 0);
			  y : out STD_LOGIC_VECTOR(31 DOWNTO 0);
			  Vdd, Vss: in STD_LOGIC);
	end component;
	
	signal Instr, Data, RFD1, RFD2: STD_LOGIC_VECTOR(31 downto 0);
	signal RFWD, OpA, OpB, SignImm: STD_LOGIC_VECTOR(31 downto 0);
	signal SignImmSh, SrcA, SrcB:	STD_LOGIC_VECTOR(31 downto 0);
	signal ALUResult, ALUOut:		STD_LOGIC_VECTOR(31 downto 0);
	signal PCNext, PC:				STD_LOGIC_VECTOR(31 downto 0);
	signal RFWA: STD_LOGIC_VECTOR(4 downto 0);
	
begin
		
	-- program counter
	pcreg: dpt_reg port map(CLK, Reset, PCEn, PCNext, PC, Vdd, Vss);
	pcmux: dpt_mux2 port map(ALUResult, ALUOut, PCSrc, PCNext, Vdd, Vss);
	memadrmux: dpt_mux2 port map(PC, ALUOut, IorD, MemAdr, Vdd, Vss);
	
	
	-- Instr and Data registers
	instrreg: dpt_reg port map(CLK, Reset, IRWrite, ReadData, Instr, Vdd, Vss);
	datareg: dpt_reg port map(CLK, Reset, Vdd, ReadData, Data, Vdd, Vss);
	
	--reg file
	rfwamux: dpt_mux2_5b port map(Instr(20 downto 16), Instr(15 downto 11), RegDst, RFWA, Vdd, Vss);
	rfwdmux: dpt_mux2 port map(ALUOut, Data, MemtoReg, RFWD, Vdd, Vss);
	rf: dpt_regfile port map(CLK, RegWrite, Instr(25 downto 21), Instr(20 downto 16), RFWA, RFWD, RFD1, RFD2, Vdd, Vss);
	rfrd1reg: dpt_reg port map(CLK, Reset, Vdd, RFD1, OpA, Vdd, Vss);
	rfrd2reg: dpt_reg port map(CLK, Reset, Vdd, RFD2, OpB, Vdd, Vss);
	
	-- alu
	signext: dpt_signext port map(Instr(15 downto 0), SignImm, Vdd, Vss);
	shift2: dpt_sl2 port map(SignImm, SignImmSh, Vdd, Vss);
	srcamux: dpt_mux2 port map(PC, OpA, ALUSrcA, SrcA, Vdd, Vss);
	srcbmux: dpt_mux4 port map(OpB, X"00000004", SignImm, SignImmSh, ALUSrcB, Vdd, Vss);
	alu: dpt_alu port map(SrcA, SrcB, ALUControl, ALUResult, ALUZero, Vdd, Vss);
	alureg: dpt_reg port map(CLK, Reset, Vdd, ALUResult, ALUOut, Vdd, Vss);

	-- out signals
	WriteData <= OpB;
	InstrOp <= Instr(31 downto 26);
	InstrFunc <= Instr(5 downto 0);

end;

