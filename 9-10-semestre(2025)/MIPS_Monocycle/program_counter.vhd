-- ==========================================
-- Módulo: Program Counter (Contador de Programa)
-- Descrição: 
--   - Registro de 32 bits que armazena o endereço da instrução atual.
--   - Atualiza o valor de saída (PC) com a entrada (PC_in) no flanco de subida do clock.
--   - Pode ser resetado com o sinal de reset ativo em '1'.
--
-- Interface:
--   - Entradas:
--       clk    : clock do sistema.
--       reset  : reset síncrono (ativa PC = 0).
--       PC_in  : endereço da próxima instrução (32 bits).
--   - Saídas:
--       PC     : endereço da instrução atual (32 bits).
-- ==========================================

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity program_counter is
    port (
        clk    : in  std_logic;
        PC_in  : in  std_logic_vector(31 downto 0);
        PC     : out std_logic_vector(31 downto 0)
    );
end program_counter;

architecture Behavioral of program_counter is
    signal PC_reg : std_logic_vector(31 downto 0) := (others => '0');
begin

    process(clk)
    begin
        if rising_edge(clk) then
            PC_reg <= PC_in;           -- Atualiza PC com próxima instrução
        end if;
    end process;

    PC <= PC_reg;

end Behavioral;
