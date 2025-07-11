library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- ============================================================================
-- Módulo: main_decoder
-- Descrição:
--   Decodificador de instruções para o processador, gerando sinais de controle
--   de acordo com o opcode
-- ============================================================================
entity main_decoder is
    Port (
		OP     	    	: in    STD_LOGIC_VECTOR(5 downto 0);  	-- Entrada OPcode de 6 bits
        jump            : out   STD_LOGIC;
		MemtoReg		: out	STD_LOGIC;
		MemWrite		: out	STD_LOGIC;
		Branch		    : out	STD_LOGIC;
		ALUSrc	    	: out	STD_LOGIC;
		RegDst  		: out	STD_LOGIC;
		RegWrite		: out	STD_LOGIC;
		ALUOp			: out	STD_LOGIC_VECTOR(1 downto 0) 	-- Definição de 2 bits para ALUOp			
    ); 
end main_decoder;

architecture rtl of main_decoder is
begin
    process(OP)
    begin
        -- Valores padrão (em caso de instrução não reconhecida)
        RegWrite 	<= '0';
        RegDst 		<= '0';
        ALUSrc 		<= '0';
        Branch		<= '0';
        MemWrite 	<= '0';
        MemtoReg	<= '0';
        ALUOp		<= "00";
        jump        <= '0';

        case OP is
            -- R-Type
            when "000000" =>
                RegWrite 	<= '1';
                RegDst 		<= '1';
                ALUSrc 		<= '0';
                Branch		<= '0';
                MemWrite 	<= '0';
                MemtoReg	<= '0';
                ALUOp		<= "10";

            -- lw
            when "100011" =>
                RegWrite 	<= '1';
                RegDst 		<= '0';
                ALUSrc 		<= '1';
                Branch		<= '0';
                MemWrite 	<= '0';
                MemtoReg	<= '1';
                ALUOp		<= "00";

            -- sw
            when "101011" =>
                RegWrite 	<= '0';
                RegDst 		<= '1'; -- X
                ALUSrc 		<= '1';
                Branch		<= '0';
                MemWrite 	<= '1';
                MemtoReg	<= '0'; -- X
                ALUOp		<= "00";

            -- beq
            when "000100" =>
                RegWrite 	<= '0';
                RegDst 		<= '1'; -- X
                ALUSrc 		<= '0';
                Branch		<= '1';
                MemWrite 	<= '0';
                MemtoReg	<= '0'; -- X
                ALUOp		<= "01";
        
            -- addi
            when "001000" => 
                RegWrite 	<= '1';
                RegDst 		<= '0';
                ALUSrc 		<= '1';
                Branch		<= '0';
                MemWrite 	<= '0';
                MemtoReg	<= '0';
                ALUOp		<= "00";
            
            -- jump
            when "000010" => 
                RegWrite 	<= '0';
                RegDst 		<= '0'; -- X
                ALUSrc 		<= '1'; -- X
                Branch		<= '0'; -- X
                MemWrite 	<= '0';
                MemtoReg	<= '0';  -- X
                ALUOp		<= "00"; -- XX
                jump        <= '1';
                
            -- Caso "others" para cobrir instruções não reconhecidas
            when others =>
                -- Valores padrão já definidos no início do processo
                null;
        end case;
    end process;
end rtl;
