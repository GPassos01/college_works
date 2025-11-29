library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- =============================================================================
-- Entidade: register_file (Banco de Registradores)
-- Descrição:
--   Implementa um banco de registros MIPS composto de 32 registradores de 32 bits.
--   Possui dois portos de leitura assíncronos e um porto de escrita síncrono.
--   A escrita só ocorre no flanco ascendente do clock(=1) e quando a entrada de 
--   enable (reg_write) estiver em '1'. O registrador zero (índice "00000") é 
--   protegido e nunca pode ser modificado.
--
-- Interface:
--   - Entradas:
--       clk         : Clock do sistema.
--       reg_write   : Sinal de enable de escrita (WE3). Quando '1', habilita 
--                     a escrita no registrador especificado.
--       read_reg1   : Endereço de 5 bits (A1) do primeiro registrador a ser lido.
--       read_reg2   : Endereço de 5 bits (A2) do segundo registrador a ser lido.
--       write_reg   : Endereço de 5 bits (A3) do registrador que receberá a escrita.
--       write_data  : Dado de 32 bits (WD) a ser escrito.
--   - Saídas:
--       read_data1  : Valor de 32 bits lido do registrador especificado por read_reg1 (RD1).
--       read_data2  : Valor de 32 bits lido do registrador especificado por read_reg2 (RD2).
-- =============================================================================

entity register_file is
    Port (
        clk         : in  STD_LOGIC;                     -- Clock do sistema
        WE   : in  STD_LOGIC;                         	-- Sinal de escrita (enable)
        A1   : in  STD_LOGIC_VECTOR(4 downto 0);        	-- Endereço do primeiro operando (A1)
        A2   : in  STD_LOGIC_VECTOR(4 downto 0);        	-- Endereço do segundo operando (A2)
        A3   : in  STD_LOGIC_VECTOR(4 downto 0);        	-- Endereço para escrita (A3)
        WD   : in  STD_LOGIC_VECTOR(31 downto 0);       	-- Dado a ser escrito (WD)
        RD1  : out STD_LOGIC_VECTOR(31 downto 0);       	-- Dado lido do primeiro registrador (RD1)
        RD2  : out STD_LOGIC_VECTOR(31 downto 0)        	-- Dado lido do segundo registrador (RD2)
    );
end register_file;

architecture rtl of register_file is

    -- Definição de um array de 32 registros, cada um com 32 bits. (vetor de vetores)
    type reg_array is array (0 to 31) of STD_LOGIC_VECTOR(31 downto 0);
    signal registradores : reg_array := (others => (others => '0'));
    -- Inicializa todos os registros com valor zero.

begin

    -- =========================================================================
    -- Leitura Assíncrona:
    -- As saídas read_data1 e read_data2 são atualizadas imediatamente conforme os
    -- endereços (read_reg1, read_reg2) mudam.
    -- =========================================================================
    RD1 <= registradores(to_integer(unsigned(A1)));
    RD2 <= registradores(to_integer(unsigned(A2)));

    -- =========================================================================
    -- Escrita Síncrona:
    -- A escrita dos dados ocorre no flanco de subida do clock (rising_edge(clk)).
    -- Se reg_write for '1' e o endereço de escrita for diferente de "00000" (registrador zero),
    -- os dados de write_data são escritos no registrador indicado por write_reg.
    -- =========================================================================
    process(clk)
    begin
        if rising_edge(clk) then 			--sincroniza com o clock
            if WE = '1' then 					--verifica permissao de escrita
                -- Impede que o registrador zero seja sobrescrito
                if A3 /= "00000" then
                    registradores(to_integer(unsigned(A3))) <= WD;
                end if;
            end if;
        end if;
    end process;
	 
	 

end rtl;
