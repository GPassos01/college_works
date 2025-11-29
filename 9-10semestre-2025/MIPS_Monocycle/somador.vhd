library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-------------------------------------------------------------------------------
-- Entidade: ULA_MIPS
--
-- Descrição:
--   Implementa a Unidade Lógica e Aritmética (ULA) de 32 bits para um processador MIPS.
--   Realiza operações aritméticas e lógicas selecionadas com base no sinal de controle ALUCtrl.
--   Gera um sinal "Zero" que indica se o resultado da operação é igual a zero.
--
-- Interface:
--   Entradas:
--     A        : Operando A (32 bits).
--     B        : Operando B (32 bits).

--   Saídas:
--     Resultado: Saída da ULA (32 bits).

-------------------------------------------------------------------------------
entity somador is
    Port (
        A         : in  STD_LOGIC_VECTOR(31 downto 0);  -- Operando A de 32 bits
        B         : in  STD_LOGIC_VECTOR(31 downto 0);  -- Operando B de 32 bits
        R         : out STD_LOGIC_VECTOR(31 downto 0)  -- Resultado da operação
    );
end somador;

architecture Behavioral of somador is
    -- Sinais internos do tipo SIGNED (permitindo operações aritméticas com sinal)
    signal A_int, B_int, Resultado_int : SIGNED(31 downto 0);
    begin

    ----------------------------------------------------------------------------
    -- Processo principal da ULA
    -- Este processo é sensível às entradas A, B e ALUCtrl. Nele são realizadas:
    --   1. Conversão das entradas de STD_LOGIC_VECTOR para SIGNED.
    --   2. Seleção da operação com base no sinal ALUCtrl, utilizando uma estrutura
    --      CASE.
    --   3. Cálculo do resultado, armazenado em Resultado_int (interno).
    --   4. Geração do sinal Zero, verificando se o resultado é igual a zero.
    ----------------------------------------------------------------------------
    process(A, B)
    begin
        -- Conversão das entradas para o tipo SIGNED, para uso em operações aritméticas
        A_int <= SIGNED(A);
        B_int <= SIGNED(B);

        -- Operação de soma: A_int + B_int
        Resultado_int <= A_int + B_int;
    end process;
    -- Conversão da saída interna (tipo SIGNED) para STD_LOGIC_VECTOR para a interface externa
    R <= STD_LOGIC_VECTOR(Resultado_int);

end Behavioral;
