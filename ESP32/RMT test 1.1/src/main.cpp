// Example from http://www.buildlog.net/blog/2017/11/esp32-sending-short-pulses-with-the-rmt/

#include <Arduino.h>
#include <driver/rmt.h>

#define Output_Pin  GPIO_NUM_4
 
// Reference https://esp-idf.readthedocs.io/en/v1.0/api/rmt.html

rmt_config_t config;
rmt_item32_t items[960];
rmt_item32_t transmissionEnd[1];
 
uint32_t loopCounter = 0;

const rmt_item32_t SK6812_low {3, 1, 9, 0};
const rmt_item32_t SK6812_high {6, 1, 6, 0};
const rmt_item32_t SK6812_reset {0, 0, 800, 0};
 
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

  for (uint32_t i = 0; i < 960; i++)
  {
    if (i % 2 == 0)
    {
      items[i] = {3, 1, 9, 0};
    }
    else
    {
      items[i] = {6, 1, 6, 0};
    }

  transmissionEnd[0] = SK6812_reset;
  }
}

static void rmt_example_tx_task(void *arg)
{
  rmt_write_items(config.channel, items, 960, 1);
  rmt_write_items(config.channel, transmissionEnd, 1, 1);
  rmt_wait_tx_done(config.channel, portMAX_DELAY);
  vTaskDelete(NULL);
}
 
void loop()
{
  // esp_err_t rmt_write_items(rmt_channel_t channel, rmt_item32_t *rmt_item, int item_num, bool wait_tx_done)
for (size_t i = 0; i < 960; i++)
  {
    items[i] = SK6812_low;
  }

for (size_t i = 0; i < 30; i++)
  {
    for (size_t j = 0; j < 32; j++)
    {
      rmt_item32_t currentItem = SK6812_low;

      if (((i + loopCounter) % 4 == 0) && j < 8)
      {
        currentItem = SK6812_high;
      }
      else if ((i + loopCounter) % 4 == 1 && j >= 8 && j < 16)
      {
        currentItem = SK6812_high;
      }
      else if ((i + loopCounter) % 4 == 2 && j >=16 && j < 24)
      {
        currentItem = SK6812_high;
      }
      else if ((i + loopCounter) % 4 == 3 && j >= 24)
      {
        currentItem = SK6812_high;
      }

      items[i * 32 + j] = currentItem;
    }
  }

  xTaskCreate(rmt_example_tx_task, "rmt_nec_tx_task", 2048, NULL, 1, NULL);
  vTaskDelay(100);

  Serial.print(loopCounter);
  Serial.println("loop");
  loopCounter++;
}