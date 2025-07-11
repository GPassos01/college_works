library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL; -- Para conversões e operações com vetores binários
-- =============================================================================
-- Entidade: instruction_memory (Memoria de Instruções)
-- Descrição:
--   A memória de instrução tem uma única porta de leitura. Recebe uma entrada de endereço de
--   instruções de 32-bits, A, e lê os dados de 32 bits (ou seja, de instrução) a partir desse
--   endereço para a saída de dados de leitura, RD.
--
-- Interface:
--   - Entradas:
--       A          : Endereco da instrucao.

--   - Saídas:
--       RD         : Dado da saida lido no endereco vindo de A, instrucao de 32 bits.
-- =============================================================================

entity instruction_memory is 
	Port(
		A	: in 	STD_LOGIC_VECTOR(31 downto 0); -- Endereço da instrução (normalmente vindo do PC)
		RD	: out	STD_LOGIC_VECTOR(31 downto 0) -- Dado de saída: instrução de 32 bits
	);
end instruction_memory;

architecture rtl of instruction_memory is
    -- Define um tipo de vetor que representa a memória com 256 posições de 32 bits
    type memory_array is array (0 to 255) of std_logic_vector(31 downto 0);
	
	 -- Sinal interno que armazena as instruções
    signal mem : memory_array := ( --others => (others => '0'));  -- Inicializa tudo com 0, sem exemplos
    -- exemplos:
        -- Inicialização com algumas instruções de exemplo codificadas em binário
        0 => x"20080005",  -- addi $t0, $zero, 5
        1 => x"2009000A",  -- addi $t1, $zero, 10
        --2 => x"01095020",  -- add  $t2, $t0, $t1
        --3 => x"AC0A0000",  -- sw   $t2, 0($zero)
        others => (others => '0')  -- Inicializa o restante com zeros
    );
    --fim exemplos
    begin
	 	-- Leitura síncrona por posição (endereçamento por palavra)
        process(A)
            variable index : integer range 0 to 255;
            begin
			-- Converte os bits de A(9 downto 2) para um índice inteiro, ignorando os dois últimos bits
			-- Isso porque cada instrução ocupa 4 bytes e os endereços são sempre múltiplos de 4
			-- Usa 8 bytes para representar os 256 bits
            -- Endereço em bytes → index da mem (dividido por 4)
            index := to_integer(unsigned(A(9 downto 2))); -- converte binario para inteiro
            RD <= mem(index);
        end process;
	 
end rtl;
