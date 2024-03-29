library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity myvga_v1_0 is
   generic (
      -- Users to add parameters here
                
      -- BRAM parameters
      C_MEMSIZE            : integer := 16384;
      C_PORT_DWIDTH        : integer := 32;
      C_PORT_AWIDTH        : integer := 14;
      C_NUM_WE             : integer := 32/8;
                   
      -- User parameters ends
      -- Do not modify the parameters beyond this line

      -- Parameters of Axi Slave Bus Interface S00_AXI
      C_S00_AXI_DATA_WIDTH : integer := 32;
      C_S00_AXI_ADDR_WIDTH : integer := 4;
      C_S00_AXI_FREQ_HZ    : integer := 100_000_000
      
   );
   port (
      -- Users to add ports here
      
      -- VGA
      red              : out std_logic;
      green            : out std_logic;
      blue             : out std_logic;
      hsync            : out std_logic;
      vsync            : out std_logic;
--      clk              : out std_logic;
--      de               : out std_logic;

      -- Block RAM
      BRAM_Rst_A       : in   std_logic;
      BRAM_Clk_A       : in   std_logic;
      BRAM_Din_A       : in   std_logic_vector(C_PORT_DWIDTH-1 downto 0);
      BRAM_EN_A        : in   std_logic;
      BRAM_WEN_A       : in   std_logic_vector(C_NUM_WE-1      downto 0);
      BRAM_Addr_A      : in   std_logic_vector(C_PORT_AWIDTH-1 downto 0);
      BRAM_Dout_A      : out  std_logic_vector(C_PORT_DWIDTH-1 downto 0);

      -- User ports ends
      -- Do not modify the ports beyond this line

      -- Ports of Axi Slave Bus Interface S00_AXI
      s00_axi_aclk      : in  std_logic;
      s00_axi_aresetn   : in  std_logic;
      s00_axi_awaddr    : in  std_logic_vector(C_S00_AXI_ADDR_WIDTH-1 downto 0);
      s00_axi_awprot    : in  std_logic_vector(2 downto 0);
      s00_axi_awvalid   : in  std_logic;
      s00_axi_awready   : out std_logic;
      s00_axi_wdata     : in  std_logic_vector(C_S00_AXI_DATA_WIDTH-1 downto 0);
      s00_axi_wstrb     : in  std_logic_vector((C_S00_AXI_DATA_WIDTH/8)-1 downto 0);
      s00_axi_wvalid    : in  std_logic;
      s00_axi_wready    : out std_logic;
      s00_axi_bresp     : out std_logic_vector(1 downto 0);
      s00_axi_bvalid    : out std_logic;
      s00_axi_bready    : in  std_logic;
      s00_axi_araddr    : in  std_logic_vector(C_S00_AXI_ADDR_WIDTH-1 downto 0);
      s00_axi_arprot    : in  std_logic_vector(2 downto 0);
      s00_axi_arvalid   : in  std_logic;
      s00_axi_arready   : out std_logic;
      s00_axi_rdata     : out std_logic_vector(C_S00_AXI_DATA_WIDTH-1 downto 0);
      s00_axi_rresp     : out std_logic_vector(1 downto 0);
      s00_axi_rvalid    : out std_logic;
      s00_axi_rready    : in  std_logic
   );
end myvga_v1_0;

architecture arch_imp of myvga_v1_0 is

begin

-- Instantiation of Axi Bus Interface S00_AXI
myvga_v1_0_S00_AXI_inst : entity work.myvga_v1_0_S00_AXI
   generic map (
         -- BRAM parameters
      C_MEMSIZE            => C_MEMSIZE,
      C_PORT_DWIDTH        => C_PORT_DWIDTH,
      C_PORT_AWIDTH        => C_PORT_AWIDTH,
      C_NUM_WE             => C_NUM_WE,
    
      C_S_AXI_DATA_WIDTH   => C_S00_AXI_DATA_WIDTH,
      C_S_AXI_ADDR_WIDTH   => C_S00_AXI_ADDR_WIDTH,
      C_S_AXI_FREQ_HZ      => C_S00_AXI_FREQ_HZ
   )
   port map (
      -- VGA
      red    => red,
      green  => green,   
      blue   => blue,   
      hsync  => hsync,   
      vsync  => vsync,   
--      clk    => clk,   
--      de     => de,     

      -- Block RAM
      BRAM_Clk_A     => BRAM_Clk_A,  
      BRAM_Rst_A     => BRAM_Rst_A, 
      BRAM_EN_A      => BRAM_EN_A,  
      BRAM_WEN_A     => BRAM_WEN_A,  
      BRAM_Addr_A    => BRAM_Addr_A, 
      BRAM_Din_A     => BRAM_Din_A, 
      BRAM_Dout_A    => BRAM_Dout_A, 

      S_AXI_ACLK     => s00_axi_aclk,
      S_AXI_ARESETN  => s00_axi_aresetn,
      S_AXI_AWADDR   => s00_axi_awaddr,
      S_AXI_AWPROT   => s00_axi_awprot,
      S_AXI_AWVALID  => s00_axi_awvalid,
      S_AXI_AWREADY  => s00_axi_awready,
      S_AXI_WDATA    => s00_axi_wdata,
      S_AXI_WSTRB    => s00_axi_wstrb,
      S_AXI_WVALID   => s00_axi_wvalid,
      S_AXI_WREADY   => s00_axi_wready,
      S_AXI_BRESP    => s00_axi_bresp,
      S_AXI_BVALID   => s00_axi_bvalid,
      S_AXI_BREADY   => s00_axi_bready,
      S_AXI_ARADDR   => s00_axi_araddr,
      S_AXI_ARPROT   => s00_axi_arprot,
      S_AXI_ARVALID  => s00_axi_arvalid,
      S_AXI_ARREADY  => s00_axi_arready,
      S_AXI_RDATA    => s00_axi_rdata,
      S_AXI_RRESP    => s00_axi_rresp,
      S_AXI_RVALID   => s00_axi_rvalid,
      S_AXI_RREADY   => s00_axi_rready
   );

   -- Add user logic here

   -- User logic ends

end arch_imp;
