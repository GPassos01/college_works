-- ==========================================
-- Módulo: extersor de sinal
-- Descrição: breve descrição da funcionalidade
-- Autor: Seu Nome
-- Data: dd/mm/yyyy
-- ==========================================

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity sign_extend is
    port (
        A       : in  std_logic_vector(15 downto 0);
        B       : out  std_logic_vector(31 downto 0)
    );
end sign_extend;

architecture Behavioral of sign_extend is

begin
    process(A)
    begin
        B <= (31 downto 16 => A(15)) & A; -- & é concatenação
    end process;
end Behavioral;
