library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- ============================================================================
-- Módulo: sll2_j
-- Descrição:
--   Realiza um deslocamento à esquerda de 2 bits.
-- ============================================================================
entity sll2_j is
    Port (
        A     : in  STD_LOGIC_VECTOR(25 downto 0);  -- Entrada A de 26 bits                   
        C     : out STD_LOGIC_VECTOR(27 downto 0)   -- Saída de 28 bits com o resultado do deslocamento
    ); 
end sll2_j;

architecture rtl of sll2_j is
begin
    process(A)
    begin
        -- Deslocamento à esquerda de 2 bits (shifting left)
        C <= A(25 downto 0) & "00";  -- A(25 downto 0) pega os 26 bits mais à esquerda de A e concatena com "00"
    end process;
end rtl;
