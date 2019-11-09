// Example from http://www.buildlog.net/blog/2017/11/esp32-sending-short-pulses-with-the-rmt/

#include <Arduino.h>
#include <driver/rmt.h>

#define Output_Pin  GPIO_NUM_4
 
// Reference https://esp-idf.readthedocs.io/en/v1.0/api/rmt.html
 
rmt_config_t config;
rmt_item32_t items[1];
 
 
 
void setup() {
  // put your setup code here, to run once:
  config.rmt_mode = RMT_MODE_TX;
  config.channel = RMT_CHANNEL_0;
  config.gpio_num = Output_Pin;
  config.mem_block_num = 1;
  config.tx_config.loop_en = 0;
  config.tx_config.carrier_en = 0;
  config.tx_config.idle_output_en = 1;
  config.tx_config.idle_level = RMT_IDLE_LEVEL_LOW;
  config.tx_config.carrier_level = RMT_CARRIER_LEVEL_HIGH;
  config.clk_div = 1; // 80MHx / 1 = around 12.5ns per pulse
 
  rmt_config(&config);
  rmt_driver_install(config.channel, 0, 0);  //  rmt_driver_install(rmt_channel_t channel, size_t rx_buf_size, int rmt_intr_num)
   
  items[0].duration0 = 1;
  items[0].level0 = 1;
  items[0].duration1 = 1;
  items[0].level1 = 0;  
 
}
 
void loop() {
  // esp_err_t rmt_write_items(rmt_channel_t channel, rmt_item32_t *rmt_item, int item_num, bool wait_tx_done)
  rmt_write_items(config.channel, items, 1, 0);
}