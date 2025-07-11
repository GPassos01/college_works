library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- ============================================================================
-- Módulo: ALU_decoder
-- Descrição:
--   Este módulo decodifica a operação da ALU com base no código da operação 
--   (ALUOp) e no código de função (Funct), gerando o controle adequado 
--   para a ALU.
-- ============================================================================
entity ALU_decoder is
    Port (
        Funct       : in  STD_LOGIC_VECTOR(5 downto 0);  -- Função (6 bits) para instruções R-type
        ALUOp       : in  STD_LOGIC_VECTOR(1 downto 0);  -- Operação de ALU de 2 bits
        ALUControl  : out STD_LOGIC_VECTOR(2 downto 0)   -- Controle de ALU de 3 bits
    ); 
end ALU_decoder;

architecture rtl of ALU_decoder is
begin
    process(ALUOp, Funct)
    begin
        -- Valores padrão para ALUControl
        ALUControl <= "000";  -- Inicializa com um valor padrão de controle
        
        case ALUOp is
            -- Operação de soma: ADD (usado por instruções como ADDI ou LW)
            when "00" =>
                ALUControl <= "010";  -- Código para ADD

            -- Operação de subtração: SUB (usado para instruções como BEQ ou SUB)
            when "01" =>
                ALUControl <= "110";  -- Código para SUB

            -- Operações para ALUOp = "10" (1X), indicando R-type e Funct específico
            when "10" =>
                case Funct is
                    -- Operação ADD para instruções R-type
                    when "100000" =>  -- ADD
                        ALUControl <= "010";  -- Código para ADD

                    -- Operação SUB para instruções R-type
                    when "100010" =>  -- SUB
                        ALUControl <= "110";  -- Código para SUB

                    -- Operação AND para instruções R-type
                    when "100100" =>  -- AND
                        ALUControl <= "000";  -- Código para AND

                    -- Operação OR para instruções R-type
                    when "100101" =>  -- OR
                        ALUControl <= "001";  -- Código para OR

                    -- Operação SLT (Set Less Than) para instruções R-type
                    when "101010" =>  -- SLT
                        ALUControl <= "111";  -- Código para SLT (Set Less Than)

                    when others =>
                        ALUControl <= "000";  -- Default (caso desconhecido)
                end case;
					 
            -- Caso em que ALUOp não é reconhecido (ideal para depuração)
            when others =>
                ALUControl <= "000";  -- Definindo um valor padrão para casos desconhecidos
        end case;
    end process;
end rtl;
