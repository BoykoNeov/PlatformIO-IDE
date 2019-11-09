// Example from http://www.buildlog.net/blog/2017/11/esp32-sending-short-pulses-with-the-rmt/

#include <Arduino.h>
#include <driver/rmt.h>

#define Output_Pin  GPIO_NUM_4
 
// Reference https://esp-idf.readthedocs.io/en/v1.0/api/rmt.html
 
rmt_config_t config;
rmt_item32_t items[32];
const rmt_item32_t SK6812_low {3, 1, 9, 0};
const rmt_item32_t SK6812_high {6, 1, 6, 0};
const rmt_item32_t SK6812_reset {0, 0, 800, 0};
 
 
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
  config.clk_div = 8; // 80MHz / clk_div
 
  rmt_config(&config);
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
  uint8_t randomValues[32];

  for (size_t i = 0; i < 24; i++)
  {
    randomValues[i] = (uint8_t)(esp_random() % 2);
  }

rmt_item32_t leds[30 * 32 ];

  for (size_t j = 0; j < sizeof(leds); j++)
  {
      if (randomValues[j % 32] % 32 == 1)
      {
          leds[j] = SK6812_high;
      }
      else
      {
          leds[j] = SK6812_low;
      }   
    }

  uint32_t start;
  uint32_t end;
  
  start = micros();
  for (size_t i = 0; i < sizeof(leds); i++)
  {
    // esp_err_t rmt_write_items(rmt_channel_t channel, rmt_item32_t *rmt_item, int item_num, bool wait_tx_done)
    rmt_write_items(config.channel, leds, sizeof(leds), 0);
  }
  end = micros();

 Serial.println(start - end);

  delay(4000);
}