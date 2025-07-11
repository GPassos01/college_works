library verilog;
use verilog.vl_types.all;
entity MIPSGMN_vlg_check_tst is
    port(
        finalMux        : in     vl_logic_vector(31 downto 0);
        regdata2        : in     vl_logic_vector(31 downto 0);
        saidaULA        : in     vl_logic_vector(31 downto 0);
        sampler_rx      : in     vl_logic
    );
end MIPSGMN_vlg_check_tst;
