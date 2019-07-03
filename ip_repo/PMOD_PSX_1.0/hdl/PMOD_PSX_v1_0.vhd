library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity PMOD_PSX_v1_0 is
	generic (
		-- Users to add parameters here
        C_CLOCK_PERIOD_TICKS : integer := 400;
        C_ACK_WAIT_TICKS     : integer := 6000;
		-- User parameters ends
		
		-- Do not modify the parameters beyond this line
		-- Parameters of Axi Slave Bus Interface S_AXI
		C_S_AXI_DATA_WIDTH	: integer	:= 32;
		C_S_AXI_ADDR_WIDTH	: integer	:= 4;

		-- Parameters of Axi Slave Bus Interface S_AXI_INTR
		C_S_AXI_INTR_DATA_WIDTH	: integer	:= 32;
		C_S_AXI_INTR_ADDR_WIDTH	: integer	:= 5;
		C_IRQ_SENSITIVITY	: integer	:= 1;
		C_IRQ_ACTIVE_STATE	: integer	:= 1
	);
	port (
		-- Users to add ports here
        -- Control signals
        s_pin_clk   : out std_logic;
        s_pin_atn1  : out std_logic;
        s_pin_atn2  : out std_logic;
        s_pin_ack   : in  std_logic;
        
        -- Command/Data signals
        s_pin_cmd   : out std_logic;
        s_pin_data  : in  std_logic;
		-- User ports ends
		
		-- Do not modify the ports beyond this line
		-- Ports of Axi Slave Bus Interface S_AXI
		s_axi_aclk	: in std_logic;
		s_axi_aresetn	: in std_logic;
		s_axi_awaddr	: in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
		s_axi_awprot	: in std_logic_vector(2 downto 0);
		s_axi_awvalid	: in std_logic;
		s_axi_awready	: out std_logic;
		s_axi_wdata	: in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
		s_axi_wstrb	: in std_logic_vector((C_S_AXI_DATA_WIDTH/8)-1 downto 0);
		s_axi_wvalid	: in std_logic;
		s_axi_wready	: out std_logic;
		s_axi_bresp	: out std_logic_vector(1 downto 0);
		s_axi_bvalid	: out std_logic;
		s_axi_bready	: in std_logic;
		s_axi_araddr	: in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
		s_axi_arprot	: in std_logic_vector(2 downto 0);
		s_axi_arvalid	: in std_logic;
		s_axi_arready	: out std_logic;
		s_axi_rdata	: out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
		s_axi_rresp	: out std_logic_vector(1 downto 0);
		s_axi_rvalid	: out std_logic;
		s_axi_rready	: in std_logic;

		-- Ports of Axi Slave Bus Interface S_AXI_INTR
		s_axi_intr_aclk	: in std_logic;
		s_axi_intr_aresetn	: in std_logic;
		s_axi_intr_awaddr	: in std_logic_vector(C_S_AXI_INTR_ADDR_WIDTH-1 downto 0);
		s_axi_intr_awprot	: in std_logic_vector(2 downto 0);
		s_axi_intr_awvalid	: in std_logic;
		s_axi_intr_awready	: out std_logic;
		s_axi_intr_wdata	: in std_logic_vector(C_S_AXI_INTR_DATA_WIDTH-1 downto 0);
		s_axi_intr_wstrb	: in std_logic_vector((C_S_AXI_INTR_DATA_WIDTH/8)-1 downto 0);
		s_axi_intr_wvalid	: in std_logic;
		s_axi_intr_wready	: out std_logic;
		s_axi_intr_bresp	: out std_logic_vector(1 downto 0);
		s_axi_intr_bvalid	: out std_logic;
		s_axi_intr_bready	: in std_logic;
		s_axi_intr_araddr	: in std_logic_vector(C_S_AXI_INTR_ADDR_WIDTH-1 downto 0);
		s_axi_intr_arprot	: in std_logic_vector(2 downto 0);
		s_axi_intr_arvalid	: in std_logic;
		s_axi_intr_arready	: out std_logic;
		s_axi_intr_rdata	: out std_logic_vector(C_S_AXI_INTR_DATA_WIDTH-1 downto 0);
		s_axi_intr_rresp	: out std_logic_vector(1 downto 0);
		s_axi_intr_rvalid	: out std_logic;
		s_axi_intr_rready	: in std_logic;
		irq	: out std_logic
	);
end PMOD_PSX_v1_0;

architecture arch_imp of PMOD_PSX_v1_0 is
    signal s_ack_sync   : std_logic_vector(1 downto 0);
    signal s_data_sync  : std_logic_vector(1 downto 0);
    
    signal s_start_strb : std_logic;
    signal s_done_strb  : std_logic;
    signal s_busy       : std_logic;
    signal s_wait_ack   : std_logic;
    signal s_err        : std_logic;
    signal s_data       : std_logic_vector(7 downto 0);
    
    signal s_ctrl_atn   : std_logic_vector(1 downto 0);
    signal s_ctrl_cmd   : std_logic_vector(7 downto 0);
    
    signal s_atn        : std_logic_vector(1 downto 0);
begin

    -- Instantiation of Axi Bus Interface S_AXI
    PMOD_PSX_v1_0_S_AXI_inst : entity work.PMOD_PSX_v1_0_S_AXI
	generic map (
		C_S_AXI_DATA_WIDTH	=> C_S_AXI_DATA_WIDTH,
		C_S_AXI_ADDR_WIDTH	=> C_S_AXI_ADDR_WIDTH
	)
	port map (
        s_ctrl_cmd      => s_ctrl_cmd,
        s_start_strb    => s_start_strb,
        s_ctrl_atn      => s_ctrl_atn,
        s_ctrl_data     => s_data,
        s_ctrl_err      => s_err,
        s_ctrl_wait_ack => s_wait_ack,
        s_ctrl_busy     => s_busy,
        
		S_AXI_ACLK	=> s_axi_aclk,
		S_AXI_ARESETN	=> s_axi_aresetn,
		S_AXI_AWADDR	=> s_axi_awaddr,
		S_AXI_AWPROT	=> s_axi_awprot,
		S_AXI_AWVALID	=> s_axi_awvalid,
		S_AXI_AWREADY	=> s_axi_awready,
		S_AXI_WDATA	=> s_axi_wdata,
		S_AXI_WSTRB	=> s_axi_wstrb,
		S_AXI_WVALID	=> s_axi_wvalid,
		S_AXI_WREADY	=> s_axi_wready,
		S_AXI_BRESP	=> s_axi_bresp,
		S_AXI_BVALID	=> s_axi_bvalid,
		S_AXI_BREADY	=> s_axi_bready,
		S_AXI_ARADDR	=> s_axi_araddr,
		S_AXI_ARPROT	=> s_axi_arprot,
		S_AXI_ARVALID	=> s_axi_arvalid,
		S_AXI_ARREADY	=> s_axi_arready,
		S_AXI_RDATA	=> s_axi_rdata,
		S_AXI_RRESP	=> s_axi_rresp,
		S_AXI_RVALID	=> s_axi_rvalid,
		S_AXI_RREADY	=> s_axi_rready
	);

    -- Instantiation of Axi Bus Interface S_AXI_INTR
    PMOD_PSX_v1_0_S_AXI_INTR_inst : entity work.PMOD_PSX_v1_0_S_AXI_INTR
	generic map (
		C_S_AXI_DATA_WIDTH	=> C_S_AXI_INTR_DATA_WIDTH,
		C_S_AXI_ADDR_WIDTH	=> C_S_AXI_INTR_ADDR_WIDTH,
		C_NUM_OF_INTR	    =>  1,
		C_INTR_SENSITIVITY	=> x"00000000",
		C_INTR_ACTIVE_STATE	=> x"FFFFFFFF",
		C_IRQ_SENSITIVITY	=> C_IRQ_SENSITIVITY,
		C_IRQ_ACTIVE_STATE	=> C_IRQ_ACTIVE_STATE
	)
	port map (
	    s_done_strb => s_done_strb,
	    
		S_AXI_ACLK	=> s_axi_intr_aclk,
		S_AXI_ARESETN	=> s_axi_intr_aresetn,
		S_AXI_AWADDR	=> s_axi_intr_awaddr,
		S_AXI_AWPROT	=> s_axi_intr_awprot,
		S_AXI_AWVALID	=> s_axi_intr_awvalid,
		S_AXI_AWREADY	=> s_axi_intr_awready,
		S_AXI_WDATA	=> s_axi_intr_wdata,
		S_AXI_WSTRB	=> s_axi_intr_wstrb,
		S_AXI_WVALID	=> s_axi_intr_wvalid,
		S_AXI_WREADY	=> s_axi_intr_wready,
		S_AXI_BRESP	=> s_axi_intr_bresp,
		S_AXI_BVALID	=> s_axi_intr_bvalid,
		S_AXI_BREADY	=> s_axi_intr_bready,
		S_AXI_ARADDR	=> s_axi_intr_araddr,
		S_AXI_ARPROT	=> s_axi_intr_arprot,
		S_AXI_ARVALID	=> s_axi_intr_arvalid,
		S_AXI_ARREADY	=> s_axi_intr_arready,
		S_AXI_RDATA	=> s_axi_intr_rdata,
		S_AXI_RRESP	=> s_axi_intr_rresp,
		S_AXI_RVALID	=> s_axi_intr_rvalid,
		S_AXI_RREADY	=> s_axi_intr_rready,
		irq	=> irq
	);
	
	
    -- Instantiation of PSX decoder
    PSX_Decode_inst : entity work.PSX_Decode
    generic map (
        C_CLOCK_PERIOD_TICKS => C_CLOCK_PERIOD_TICKS,
        C_ACK_WAIT_TICKS     => C_ACK_WAIT_TICKS
    )
    port map (
        s_axi_clock => s_axi_aclk,
        s_axi_reset => s_axi_aresetn,
        
        -- Control signals for CPU
        s_done_strb     => s_done_strb,
        s_busy          => s_busy,
        s_wait_ack      => s_wait_ack,
        s_err           => s_err,
        s_data          => s_data,
        s_ctrl_atn      => s_ctrl_atn,
        s_start_strb    => s_start_strb,
        s_ctrl_cmd      => s_ctrl_cmd,
        
        -- Control signals for PSX
        s_pin_clock => s_pin_clk,
        s_pin_atn   => s_atn,
        s_ack   => s_ack_sync(1),
        
        -- Command/Data signals
        s_pin_cmd   => s_pin_cmd,
        s_data_in   => s_data_sync(1)
    );
    
    -- Line synchronisation for ACK and DATA to prevent
    -- metastability.
    process(s_axi_aclk)
    begin
        if (rising_edge(s_axi_aclk)) then
            if (s_axi_aresetn = '0') then
                s_ack_sync  <= (others => '0');
                s_data_sync <= (others => '0');
            else
                s_ack_sync  <= s_ack_sync(0) & s_pin_ack;
                s_data_sync <= s_data_sync(0) & s_pin_data;
            end if;
        end if;
    end process;
    
    -- Output to pins from ATN buffer. Buffer is handled by decoder to ensure
    -- CPU does not try to change ATN within the middle of the decode process.
    s_pin_atn1 <= not s_atn(0);
    s_pin_atn2 <= not s_atn(1);

end arch_imp;
