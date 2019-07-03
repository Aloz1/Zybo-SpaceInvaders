----------------------------------------------------------------------------------
-- Company:
-- Engineer:
--
-- Create Date:    16:51:25 04/14/2006
-- Design Name:
-- Module Name:    Video - Behavioral
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

Library UNISIM;
use UNISIM.vcomponents.all;

entity video_timing is
    Generic (
         C_VID_Clk_FREQ_HZ  : integer := 25_000_000
         );
    Port (
         ResetN         : in   std_logic;
         PixelClk_25MHz : in   std_logic;
         vidHSync       : out  std_logic;
         vidVSync       : out  std_logic;
         vidBlank       : out  std_logic;
         ramAddress     : out  std_logic_vector(11 downto 0);
         ramLoad        : out  std_logic;
         srShift        : out  std_logic
         );
end video_timing;

architecture Behavioral of video_timing is

   signal horizontalCounter : std_logic_vector(10 downto 0) := (others => '0');
   signal verticalCounter   : std_logic_vector(10 downto 0) := (others => '0');

   -- Control entries in ROM
   type arrayElement is
   record
      hVideo  : integer range 0 to 1280;
      hFPorch : integer range 0 to 1280;
      hSyncW  : integer range 0 to 1280;
      hBPorch : integer range 0 to 1280;

      vVideo  : integer range 0 to 1280;
      vFPorch : integer range 0 to 1280;
      vSyncW  : integer range 0 to 1280;
      vBPorch : integer range 0 to 1280;
   end record;

                                       -- hVideo  hFPorch  hSyncW  hBPorch   vVideo  vFPorch  vSyncW, vBPorch
   constant settings : arrayElement := ( 640-128,  16+64,     96,   48+64,     480,      10,      2,      29  );  -- 512x480 @ 60Hz 25MHz pixel clock
--   constant settings : arrayElement := (  640,      16,     96,      48,     480,      10,      2,      29  );  -- 640x480 @ 60Hz 25MHz pixel clock

   constant hVideo  : integer := settings.hVideo;
   constant hFPorch : integer := settings.hFPorch;
   constant hSyncW  : integer := settings.hSyncW;
   constant hBPorch : integer := settings.hBPorch;

   constant vVideo  : integer := settings.vVideo;
   constant vFPorch : integer := settings.vFPorch;
   constant vSyncW  : integer := settings.vSyncW;
   constant vBPorch : integer := settings.vBPorch;

   signal   reset : std_logic := '0';

begin

   reset <= not ResetN;
   
   counters:
   process (PixelClk_25MHz)
   begin
      if rising_edge(PixelClk_25MHz) then
         if (reset = '1') then
            horizontalCounter <= (others => '0');
            verticalCounter   <= (others => '0');
         else
            if horizontalCounter >= (hVideo+hFPorch+hSyncW+hBPorch-1) then
               horizontalCounter <= (others => '0');
               if verticalCounter >= (vVideo+vFPorch+vSyncW+vBPorch-1) then
                  verticalCounter <= (others => '0');
               else
                  verticalCounter  <= verticalCounter+1;
               end if;
            else
               horizontalCounter <= horizontalCounter+1;
            end if;
         end if;
      end if;
   end process;

   process (PixelClk_25MHz)
   variable blankdelay : std_logic;
   variable blankdelay2 : std_logic;
   
   begin
      if rising_edge(PixelClk_25MHz) then
         if (reset = '1') then
            vidBlank    <= '0';
            blankdelay  := '0';
            blankdelay2 := '0';
         else
            vidBlank    <= blankdelay2;
            blankdelay2 := blankdelay;
            if (horizontalCounter >= hVideo) or (verticalCounter >= vVideo) then
               blankdelay := '0';
            else
               blankdelay := '1';
            end if;
         end if;
      end if;
   end process;
   
   hSync:
   vidHSync <= '0' when (horizontalCounter >= (hVideo+hFPorch)) and
                        (horizontalCounter <  (hVideo+hFPorch+hSyncW)) else
               '1';

   vSync:
   vidVSync <= '0' when (verticalCounter >= (vVideo+vFPorch)) and
                        (verticalCounter <  (vVideo+vFPorch+vSyncW)) else
               '1';

   vAddress:
   ramAddress  <= verticalCounter(8 downto 1) & horizontalCounter(8 downto 5);
   ramLoad     <= '1' when (horizontalCounter(4 downto 0) = "00010") else '0';
   srShift     <= '1' when (horizontalCounter(0 downto 0) = "0")     else '0';
   
   -- Memory is 16Kbytes = 4K x 4bytes = 4K x 16 pixel/word = 256 pixels x 256 pixels
   --     ROW Counter     |   Column Counter
   -- 9 8 7 6 5 4 3 2 1 0 | 9 8 7 6 5 4 3 2 1 0
   -- X r r r r r r r r X | X c c c c p p p p X 
   --      256 rows       | 256 pixels = 16 words X 16 pixels/word
   --   256 rows X 16 words X 4 bytes = 2**8 x 2**4 x 2**2 = 2**14 bytes = 2**4 Kbytes = 16 KBytes
end Behavioral;

