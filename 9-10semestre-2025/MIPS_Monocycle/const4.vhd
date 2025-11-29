library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL; -- Para conversões e operações com vetores binários

entity const4 is 
    Port(
        B : out STD_LOGIC_VECTOR(31 downto 0) -- Dado de saída: instrução de 32 bits
    );
end const4;

architecture Behavioral of const4 is
begin
    -- Atribuição de um valor de 32 bits (4 em binário é 00000000000000000000000000000100)
    B <= std_logic_vector(to_unsigned(4, 32));
end Behavioral;

