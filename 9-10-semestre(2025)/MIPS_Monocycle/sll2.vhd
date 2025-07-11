library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- ============================================================================
-- Módulo: sll2
-- Descrição:
--   Realiza um deslocamento à esquerda de 2 bits.
-- ============================================================================
entity sll2 is
    Port (
        A     : in  STD_LOGIC_VECTOR(31 downto 0);  -- Entrada A de 32 bits                   
        C     : out STD_LOGIC_VECTOR(31 downto 0)   -- Saída de 32 bits com o resultado do deslocamento
    ); 
end sll2;

architecture rtl of sll2 is
begin
    process(A)
    begin
        -- Deslocamento à esquerda de 2 bits (shifting left)
        C <= A(29 downto 0) & "00";  -- A(29 downto 0) pega os 30 bits mais à esquerda de A e concatena com "00"
    end process;
end rtl;
