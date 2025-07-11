-- concat_4_28.vhd
library ieee;
use ieee.std_logic_1164.all;

entity concat_4_28 is
    port (
        high4  : in  std_logic_vector(3 downto 0);
        low28  : in  std_logic_vector(27 downto 0);
        result : out std_logic_vector(31 downto 0)
    );
end entity;

architecture rtl of concat_4_28 is
begin
    result <= high4 & low28;
end architecture;
