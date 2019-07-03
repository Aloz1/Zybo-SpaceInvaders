----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 23.04.2018 10:33:12
-- Design Name: 
-- Module Name: PSX_Decode - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity PSX_Decode is
    generic (
        C_CLOCK_PERIOD_TICKS : integer := 400;
        C_ACK_WAIT_TICKS     : integer := 6000
    );
    port (
        -- AXI signals
        s_axi_clock   : in std_logic;
        s_axi_reset   : in std_logic;
        
        -- PS control signals
        s_done_strb : out std_logic;
        s_busy      : out std_logic;
        s_wait_ack  : out std_logic;
        s_err       : out std_logic;
        s_data      : out std_logic_vector(7 downto 0);
        s_ctrl_atn       : in  std_logic_vector(1 downto 0);
        s_start_strb     : in  std_logic;
        s_ctrl_cmd       : in  std_logic_vector(7 downto 0);
        
        -- PSX control signals
        s_pin_clock   : out std_logic;
        s_pin_atn     : out std_logic_vector(1 downto 0);
        s_ack         : in  std_logic;
        
        -- PSX Command/Data signals
        s_pin_cmd   : out std_logic;
        s_data_in   : in  std_logic
    );
end PSX_Decode;

architecture Behavioral of PSX_Decode is
	 constant HALF_CLOCK_TICKS : integer := C_CLOCK_PERIOD_TICKS / 2;

    type PSX_comms_state is (IDLE, SEND_RECV, WAIT_ACK);

    -- Counters
    signal period_count : unsigned(16 downto 0);
    signal bit_count    : unsigned(3 downto 0);
    
    -- Clock stuff
    signal clk_gen         : std_logic;
    
    -- State stuff
    signal state       : PSX_comms_state;
    
    -- Signals/registers
    signal cmd_sr      : std_logic_vector(7 downto 0);
    signal data_sr     : std_logic_vector(7 downto 0);
    signal curr_atn    : std_logic_vector(1 downto 0);
    signal running_sig : std_logic;
    signal prev_ack    : std_logic;
    
begin
    
    -- Change state and synchronous logic process.
    process(s_axi_clock)
    begin
        if (rising_edge(s_axi_clock)) then
            if (s_axi_reset = '0') then
                -- Reset state
                state <= IDLE;
                
                -- Reset signals and strobes
                clk_gen      <= '1';
                s_err        <= '0';
                s_done_strb  <= '0';
                prev_ack     <= '1';
                running_sig  <= '0';
                
                -- Reset registers
                period_count <= (others => '0');
                bit_count    <= (others => '0');
                data_sr      <= (others => '0');
                curr_atn     <= (others => '0');
                cmd_sr       <= (others => '1');
            else
                
                -- Period counter, decrements by 1 each clock cycle until the count is 0
                if (period_count /= 0) then
                    period_count <= unsigned(period_count) - 1;
                end if;
                
                -- Synchronous state machine stuff.
                case state is
                    when IDLE =>
                        s_done_strb <= '0';
                        bit_count <= (others => '0');
                        cmd_sr    <= (others => '1');
                        
                        -- The user has told us to start. Set HW to busy, and clear any outstanding
                        -- errors.
                        if (s_start_strb = '1') then
                            running_sig <= '1';
                            s_err <= '0';
                        end if;
                        
                        if (period_count = 0) then
                            -- The CPU has changed ATN. We must change it in memory, and wait at least 1 period
                            -- before doing anything, and clear any outstanding errors.
                            if (curr_atn /= s_ctrl_atn) then
                                curr_atn     <= s_ctrl_atn;
                                period_count <= to_unsigned(C_CLOCK_PERIOD_TICKS, period_count'length);
                                s_err   <= '0';
                            end if;
                            
                            -- We have been given the start signal, and ATN hasn't changed. Lets
                            -- start. We will copy the command into its shift register for later use.
                            if (curr_atn = s_ctrl_atn and running_sig = '1') then
                                state  <= SEND_RECV;
                            end if;
                        end if;
                    
                    when SEND_RECV =>
                        -- Only do things when period counter is 0.
                        if (period_count = "0") then
                            -- Set the period counter and toggle clock
                            period_count <= to_unsigned(C_CLOCK_PERIOD_TICKS / 2, period_count'length);
                            clk_gen <= not clk_gen;
                            
                            if (clk_gen = '1') then
                                if (bit_count = 0) then
                                    -- We've only just entered the state. Time to initialize the command shift reg to
                                    -- whatever the CPU gave to us.
                                    cmd_sr <= s_ctrl_cmd;
                                else
                                    -- Shift to the left (filling with 1's will leave a 1 in the LSB of the SR after
                                    -- all bits have been transmitted)
                                    cmd_sr <= '1' & cmd_sr(7 downto 1);
                                end if;
                                
                                -- We always count up for bits transmitted.
                                bit_count <= bit_count + 1;
                            end if;
                            
                            -- Rising edge - Shift in the next bit of DATA
                            if (clk_gen = '0') then
                                data_sr <= s_data_in & data_sr(7 downto 1);
                            end if;
                            
                            -- Time to exit this state. 
                            if (clk_gen = '1' and bit_count = 8) then
                                state <= WAIT_ACK;
                                
                                -- Preload counter for next state, and make sure the clock is '1' on exit.
                                period_count <= to_unsigned(C_CLOCK_PERIOD_TICKS + C_ACK_WAIT_TICKS, period_count'length);
                                clk_gen <= '1';
                            end if;
                        end if;
                        
                    when WAIT_ACK =>
                        prev_ack <= s_ack;
                        
                        if (period_count = 0) then
                            -- Waited too long for ACK. The PSX is most likely not connected. So lets set the error flag.
                            state <= IDLE;
                            s_done_strb <= '1';
                            running_sig <= '0';
                            s_err <= '1';
                        end if;
                        
                        if (prev_ack = '0' and s_ack = '1') then
                            -- Looks like the PSX has responded with an ACK (YAY :D :D :D).
                            state <= IDLE;
                            period_count <= (others => '0');
                            s_done_strb <= '1';
                            running_sig <= '0';
                        end if;
                end case;
            end if;
        end if;
    end process;
    
    -- Outgoing pin signals
    s_wait_ack <= '1' when state = WAIT_ACK else
                       '0';
                       
    -- Signals that will go out to physical pins
    s_pin_clock <= clk_gen;
    s_pin_atn   <= curr_atn;
    s_pin_cmd   <= cmd_sr(0);
    
    -- Signals that will go to the CPU
    s_data      <= data_sr;
    s_busy      <= running_sig;

end Behavioral;
