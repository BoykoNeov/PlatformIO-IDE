// Example from http://www.buildlog.net/blog/2017/11/esp32-sending-short-pulses-with-the-rmt/

#include <Arduino.h>
#include <driver/rmt.h>
#include "soc/rtc_wdt.h"

#define Output_Pin  GPIO_NUM_4

String interruptTriggered = "0";


// static DRAM_ATTR const uint32_t tx_thr_event_offsets [] = {
//   static_cast<uint32_t>(1) << (24 + 0),
//   static_cast<uint32_t>(1) << (24 + 1),
//   static_cast<uint32_t>(1) << (24 + 2),
//   static_cast<uint32_t>(1) << (24 + 3),
//   static_cast<uint32_t>(1) << (24 + 4),
//   static_cast<uint32_t>(1) << (24 + 5),
//   static_cast<uint32_t>(1) << (24 + 6),
//   static_cast<uint32_t>(1) << (24 + 7),
// };
 
// Reference https://esp-idf.readthedocs.io/en/v1.0/api/rmt.html
 
rmt_config_t config;
rmt_item32_t items[32];
const rmt_item32_t SK6812_low {3, 1, 9, 0};
const rmt_item32_t SK6812_high {6, 1, 6, 0};
const rmt_item32_t SK6812_reset {0, 0, 800, 0};

static intr_handle_t rmt_intr_handle = nullptr;

void IRAM_ATTR handleRMTinterrupt(void *arg)
{
  if (RMT.int_st.ch0_tx_thr_event) 
  {
    RMT.int_clr.ch0_tx_thr_event = 1;
    // RMT.int_clr.val |= tx_thr_event_offsets[0];
    interruptTriggered = "1";
    Serial.println("th");
  }
  else if(RMT.int_st.ch0_tx_end)
  {
    Serial.println("en");
    RMT.int_clr.ch0_tx_end = 1;
  }

  return;
}
 
 
void setup() 
{
  // put your setup code here, to run once:
  config.rmt_mode = RMT_MODE_TX;
  config.channel = RMT_CHANNEL_0;
  config.gpio_num = Output_Pin;
  config.mem_block_num = 1;
  config.tx_config.loop_en = 0;
  config.tx_config.carrier_en = 0;
  config.tx_config.idle_output_en = 0;
  config.tx_config.idle_level = RMT_IDLE_LEVEL_LOW;
  config.tx_config.carrier_level = RMT_CARRIER_LEVEL_LOW;
  config.clk_div = 8; // 80MHz / clk_div
  rmt_config(&config);

  rmt_set_tx_intr_en(static_cast<rmt_channel_t>(RMT_CHANNEL_0), true);

  // Specifies the number of transmit items at which the interrupt is triggered
  rmt_set_tx_thr_intr_en(static_cast<rmt_channel_t>(RMT_CHANNEL_0), true, 16);

  RMT.int_ena.ch0_tx_thr_event = 1;
 // RMT.int_clr.val |= tx_thr_event_offsets[0];

  esp_intr_alloc(ETS_RMT_INTR_SOURCE, 0, handleRMTinterrupt, nullptr, &rmt_intr_handle);

  // Interrupt allocations should be placed before driver install
  rmt_driver_install(config.channel, 0, 0);  //  rmt_driver_install(rmt_channel_t channel, size_t rx_buf_size, int rmt_intr_num)
   
Serial.begin(115200);


}
 
// 
// first 8 bits are for green
// second 8 bits are for red
// third 8 bits are for blue
// final 8 bits are for white
// so this is GRBW strip, valid from one brought from BTF-LIGHTING on aliexpress
// with full brightness on all colors and white, 30 leds consume 1.319A or 6.56W or 44ma per led or 218mW per led


void loop() {

  delay(1);
  
  Serial.println("loop" + interruptTriggered);

    uint32_t rmtItemsSize = 32;
    rmt_item32_t rmtItems[rmtItemsSize];
    rmt_item32_t rmtItems2[rmtItemsSize];

    for (size_t i = 0; i < rmtItemsSize; i++)
    {
        rmtItems[i] = SK6812_low;
        rmtItems2[i] = SK6812_high;
    }

        rmt_fill_tx_items(RMT_CHANNEL_0, rmtItems, 16, 0);
        rmt_fill_tx_items(RMT_CHANNEL_0, rmtItems2, 16, 16);
        rmt_tx_start(RMT_CHANNEL_0,1);

        delay(1);
        rmt_tx_stop(RMT_CHANNEL_0);

        // RMT.int_clr.val.chN_event_name
        // RMT.int_clr.ch0_tx_thr_event = 1;

delay(1000);
}