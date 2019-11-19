// Example from http://www.buildlog.net/blog/2017/11/esp32-sending-short-pulses-with-the-rmt/

#include <Arduino.h>
#include <driver/rmt.h>

#define Output_Pin  GPIO_NUM_4
 
// Reference https://esp-idf.readthedocs.io/en/v1.0/api/rmt.html

rmt_config_t config;
rmt_item32_t items64[64];
rmt_item32_t items64[31];
 
uint32_t loopCounter = 0;

const rmt_item32_t test_a {1, 1, 9, 0};
const rmt_item32_t test_a_inverted {9, 1, 1, 0};
const rmt_item32_t test_b {5, 1, 5, 0};
const rmt_item32_t test_c {1, 0, 9, 1};
 
void setup() 
{
  Serial.begin(115200);
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
  config.clk_div = 8; // 80MHx / 1 = around 12.5ns per pulse
 
  rmt_config(&config);
  rmt_driver_install(config.channel, 0, 0);  //  rmt_driver_install(rmt_channel_t channel, size_t rx_buf_size, int rmt_intr_num)

  for (uint32_t i = 0; i < 63; i++)
  {
    items64[i] = test_a;
  }
  items64[63] = test_a_inverted;

  for (uint32_t i = 0; i < 31; i++)
  {
    items64[i] = test_b;
  }
  items64[31] = test_c;
}

static void rmt_example_tx_task(void *arg)
{
  // rmt_write_items(config.channel, items, 960, 1);
  // rmt_write_items(config.channel, transmissionEnd, 1, 1);
  // rmt_wait_tx_done(config.channel, portMAX_DELAY);
  vTaskDelete(NULL);
}
 
void loop()
{
  // esp_err_t rmt_write_items(rmt_channel_t channel, rmt_item32_t *rmt_item, int item_num, bool wait_tx_done)


  xTaskCreate(rmt_example_tx_task, "rmt_nec_tx_task", 2048, NULL, 1, NULL);
  vTaskDelay(100);

  Serial.print(loopCounter++);
  Serial.println("loop");
}