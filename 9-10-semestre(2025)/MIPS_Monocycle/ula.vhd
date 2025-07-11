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
--     ALUCtrl  : Sinal de 4 bits que determina qual operação executar:
--                "0010" -> ADD (Soma)
--                "0110" -> SUB (Subtração)
--                "0000" -> AND (E lógico)
--                "0001" -> OR (OU lógico)
--                "0111" -> SLT (Set on Less Than);
--                         Se A < B, o resultado é 1 (no bit menos significativo),
--                         caso contrário, 0.
--
--   Saídas:
--     Resultado: Saída da ULA (32 bits).
--     Zero     : Sinal que indica se o Resultado é igual a zero ('1' se for zero,
--                caso contrário, '0').
-------------------------------------------------------------------------------
entity ULA is
    Port (
        A         : in  STD_LOGIC_VECTOR(31 downto 0);  	-- Operando A de 32 bits
        B         : in  STD_LOGIC_VECTOR(31 downto 0);  	-- Operando B de 32 bits
        ALUCtrl   : in  STD_LOGIC_VECTOR(2 downto 0);   	-- Sinal de controle de 3 bits
        Resultado : out STD_LOGIC_VECTOR(31 downto 0);  	-- Resultado da operação
        Zero      : out STD_LOGIC                     	-- Sinal indicador de resultado zero
    );
end ULA;

architecture rtl of ULA is
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
    process(A, B, ALUCtrl)
    begin
        -- Conversão das entradas para o tipo SIGNED, para uso em operações aritméticas
        A_int <= SIGNED(A);
        B_int <= SIGNED(B);

        -- Seleção da operação baseada no sinal de controle ALUCtrl
        case ALUCtrl is
            -- Operação de soma: A_int + B_int
            when "010" =>
                Resultado_int <= A_int + B_int;

            -- Operação de subtração: A_int - B_int
            when "110" =>
                Resultado_int <= A_int - B_int;

            -- Operação lógica AND: bit a bit entre A_int e B_int
            when "000" =>
                Resultado_int <= A_int and B_int;

            -- Operação lógica OR: bit a bit entre A_int e B_int
            when "001" =>
                Resultado_int <= A_int or B_int;
            
            when "100" => 
                Resultado_int <= A_int and (not B_int);
               
            when "101" =>
                Resultado_int <= A_int or (not B_int);
            
            -- Operação SLT (Set on Less Than):
            -- Se A_int < B_int, o resultado é 1 (apenas o bit 0 é 1)
            -- Caso contrário, o resultado é 0 (todos os bits em 0).
            when "111" =>
                if A_int < B_int then
                    -- Zera todos os bits e define o bit menos significativo como '1'
                    Resultado_int <= (others => '0');
                    Resultado_int(0) <= '1';
                else
                    Resultado_int <= (others => '0');
                end if;

            -- Caso padrão: se ALUCtrl não corresponder a nenhuma operação conhecida,
            -- zera o resultado.
            when others =>
                Resultado_int <= (others => '0');
        end case;

        ----------------------------------------------------------------------------
        -- Geração do sinal Zero:
        -- Se o valor de Resultado_int for igual a zero, o sinal Zero é definido como '1',
        -- senão, é definido como '0'.
        ----------------------------------------------------------------------------
        if Resultado_int = 0 then
            Zero <= '1';
        else
            Zero <= '0';
        end if;
    end process;

    -- Conversão da saída interna (tipo SIGNED) para STD_LOGIC_VECTOR para a interface externa
    Resultado <= STD_LOGIC_VECTOR(Resultado_int);

end rtl;
