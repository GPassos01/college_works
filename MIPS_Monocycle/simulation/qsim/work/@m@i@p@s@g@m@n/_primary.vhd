library verilog;
use verilog.vl_types.all;
entity MIPSGMN is
    port(
        finalMux        : out    vl_logic_vector(31 downto 0);
        clk             : in     vl_logic;
        regdata2        : out    vl_logic_vector(31 downto 0);
        saidaULA        : out    vl_logic_vector(31 downto 0)
    );
end MIPSGMN;
