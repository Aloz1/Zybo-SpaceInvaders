--============================================================================
-- Creates a Read/Write memory from block RAM
--============================================================================

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

ENTITY VideoMemory IS
   Generic ( 
       -- Video port parameters
       dataWidth          : integer       := 32;
       addressWidth       : integer       := 12;
                          
       -- BRAM parameters 
       C_MEMSIZE          : integer       := 65536; -- = (4 * 2**addressWidth);
       C_PORT_DWIDTH      : integer       := 32;
       C_PORT_AWIDTH      : integer       := 32;
       C_NUM_WE           : integer       := 4
      );
	port (
      -- BRAM Signals
      -- NOTE: Data direction from POV of controller
      BRAM_Clk_A     : in  std_logic;
      BRAM_Rst_A     : in  std_logic;
      BRAM_EN_A      : in  std_logic;
      BRAM_WEN_A     : in  std_logic_vector(C_NUM_WE-1      downto 0);
      BRAM_Addr_A    : in  std_logic_vector(C_PORT_AWIDTH-1 downto 0);
      BRAM_Dout_A    : out std_logic_vector(C_PORT_DWIDTH-1 downto 0);
      BRAM_Din_A     : in  std_logic_vector(C_PORT_DWIDTH-1 downto 0);
   
      -- VGA interface
      clock          : IN  std_logic;
      en             : IN  std_logic;
      addr           : IN  std_logic_vector(addressWidth-1 downto 0);
      dout           : OUT std_logic_vector(dataWidth-1    downto 0)
   );
END VideoMemory;

ARCHITECTURE RTL OF VideoMemory IS

 type MemBankType is array ((2**addressWidth)-1 downto 0) of std_logic_vector(7 downto 0);

 -- 4 Memory banks for the 4 byte lanes on AXI bus
 signal mem0 : MemBankType := (others =>x"FF");
 signal mem1 : MemBankType := (others =>x"00");
 signal mem2 : MemBankType := (others =>x"55");
 signal mem3 : MemBankType := (others =>x"AA");

 -- Make sure block RAM
 attribute ram_style : string;
 attribute ram_style of mem0 : signal is "block";
 attribute ram_style of mem1 : signal is "block";
 attribute ram_style of mem2 : signal is "block";
 attribute ram_style of mem3 : signal is "block";

 signal RADDR_REGA : std_logic_vector(addressWidth-1 downto 0);
 signal RADDR_REGB : std_logic_vector(addressWidth-1 downto 0);
 
 signal BRAM_Addr_A_reduced : integer;
 
begin
   
   -- Discard 2 LSBs as 32-bit aligned (A[1..0] select bytes within a long word)
   BRAM_Addr_A_reduced <= conv_integer(BRAM_Addr_A((addressWidth-1)+2 downto 2));

   process (BRAM_Clk_A)
   begin
      if rising_edge(BRAM_Clk_A) then
         if (BRAM_EN_A = '1') then
            if (BRAM_WEN_A(0) = '1') then
               mem0(BRAM_Addr_A_reduced) <= BRAM_Din_A(7 downto 0);
            end if;
            if (BRAM_WEN_A(1) = '1') then
               mem1(BRAM_Addr_A_reduced) <= BRAM_Din_A(15 downto 8);
            end if;
            if (BRAM_WEN_A(2) = '1') then
               mem2(BRAM_Addr_A_reduced) <= BRAM_Din_A(23 downto 16);
            end if;
            if (BRAM_WEN_A(3) = '1') then
               mem3(BRAM_Addr_A_reduced) <= BRAM_Din_A(31 downto 24);
            end if;
            BRAM_Dout_A( 7 downto  0)  <= mem0(BRAM_Addr_A_reduced);
            BRAM_Dout_A(15 downto  8)  <= mem1(BRAM_Addr_A_reduced);
            BRAM_Dout_A(23 downto 16)  <= mem2(BRAM_Addr_A_reduced);
            BRAM_Dout_A(31 downto 24)  <= mem3(BRAM_Addr_A_reduced);
         end if;
      end if;
   end process;

   process (clock)
   begin
      if rising_edge(clock) then
         if (en = '1') then
            dout( 7 downto  0) <= mem3(conv_integer(addr));
            dout(15 downto  8) <= mem2(conv_integer(addr));
            dout(23 downto 16) <= mem1(conv_integer(addr));
            dout(31 downto 24) <= mem0(conv_integer(addr));
         end if;
      end if;
   end process;

end architecture RTL;
