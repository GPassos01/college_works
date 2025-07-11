library ieee;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- ============================================================================
-- Entity: data_memory
-- Descrição:
--   Módulo de memória de dados do processador MIPS monociclo.
--   - Suporta escrita síncrona (em borda de subida do clock).
--   - Suporta leitura assíncrona (dado disponível imediatamente).
--   - A memória é indexada por palavras (32 bits), alinhadas a 4 bytes.
-- ============================================================================
entity data_memory is
    port (
        clk  : in  std_logic;                              -- Clock do sistema
        A    : in  std_logic_vector(31 downto 0);          -- Endereço de acesso à memória
        WE   : in  std_logic;                              -- Sinal de escrita ('1' para escrita, '0' para leitura)
        WD   : in  std_logic_vector(31 downto 0);          -- Dado a ser escrito na memória
        RD   : out std_logic_vector(31 downto 0)           -- Dado lido da memória
    );
end data_memory;

architecture Behavioral of data_memory is

    -- Definição do tipo de memória: 256 palavras de 32 bits
    type mem_array is array (0 to 255) of std_logic_vector(31 downto 0);

    -- Instância da memória (inicialmente zerada)
    signal mem : mem_array := (others => (others => '0'));

    -- Índice de acesso à memória (derivado dos bits relevantes do endereço)
    signal addr_index : integer range 0 to 255 := 0;

begin

    -- Processo de escrita na memória (síncrono com clock)
    process(clk)
    begin
        if rising_edge(clk) then
            -- Converte os bits [9:2] do endereço para um índice (palavras alinhadas a 4 bytes)
            addr_index <= to_integer(unsigned(A(9 downto 2)));

            -- Se habilitado, realiza a escrita na memória
            if WE = '1' then
                mem(to_integer(unsigned(A(9 downto 2)))) <= WD;
            end if;
        end if;
    end process;

    -- Leitura assíncrona (o dado lido está sempre disponível com base no último índice acessado)
    RD <= mem(addr_index);

end Behavioral;
