// Example from http://www.buildlog.net/blog/2017/11/esp32-sending-short-pulses-with-the-rmt/

#include <Arduino.h>
#include <driver/rmt.h>

#define Output_Pin  GPIO_NUM_4
 
// Reference https://esp-idf.readthedocs.io/en/v1.0/api/rmt.html

rmt_config_t config;
rmt_item32_t items64[64];
rmt_item32_t items32[32];
rmt_item32_t items32b[32];
 
uint32_t loopCounter = 0;
uint32_t interruptCounter = 0;

const rmt_item32_t test_a {1, 1, 9, 0};
const rmt_item32_t test_b {5, 1, 5, 0};
const rmt_item32_t test_endx2 {30, 1, 30, 0};

static intr_handle_t rmt_intr_handle = nullptr;

void EndTransmission()
{
      RMT.apb_conf.mem_tx_wrap_en  = 0;
}

void IRAM_ATTR handleRMTinterrupt(void *arg)
{
  // if the set threshold of transmitted items is reached
  if (RMT.int_st.ch0_tx_thr_event) 
  {
    interruptCounter++;

    if (interruptCounter == 1)
    {
    rmt_fill_tx_items(RMT_CHANNEL_0, items32, 32, 0);
    }
    else if (interruptCounter == 2)
    {
      rmt_fill_tx_items(RMT_CHANNEL_0, items32, 32, 32);
    }
    else if (interruptCounter == 4)
    {
      // !!! The last item to be transmitted is missing, reasons unknown (maybe the interrupt is triggered exactly before the actual transmission?)
      EndTransmission();
    }

    RMT.int_clr.ch0_tx_thr_event = 1;
  }
  // if the end of buffer is reached
  // else if(RMT.int_st.ch0_tx_end)
  // {
  //   RMT.int_clr.ch0_tx_end = 1;
  // }

  return;
}

void InitialFillBuffers()
{
  for (uint32_t i = 0; i < 64; i++)
  {
    items64[i] = test_a;
  }

  for (uint32_t i = 0; i < 32; i++)
  {
    items32[i] = test_b;
  }
  items32[31] = test_endx2;
}

void setup() 
{
  Serial.begin(115200);

  config.rmt_mode = RMT_MODE_TX;
  config.channel = RMT_CHANNEL_0;
  config.gpio_num = Output_Pin;
  config.mem_block_num = 1;
  // loop enabled does not seem to make a difference when RMT.apb_conf.mem_tx_wrap_en  = true;
  config.tx_config.loop_en = 1;
  config.tx_config.carrier_en = 0;
  config.tx_config.idle_output_en = 1;
  config.tx_config.idle_level = RMT_IDLE_LEVEL_LOW;
  config.tx_config.carrier_level = RMT_CARRIER_LEVEL_LOW;
  config.clk_div = 8; // 80MHx / 1 = around 12.5ns per pulse
 
  rmt_config(&config);

  // Specifies the number of transmit items at which the interrupt is triggered
  rmt_set_tx_thr_intr_en(static_cast<rmt_channel_t>(RMT_CHANNEL_0), true, 32);
  RMT.int_ena.ch0_tx_thr_event = 1;
  // RMT.int_clr.ch0_tx_end = 1;
  esp_intr_alloc(ETS_RMT_INTR_SOURCE, 0, handleRMTinterrupt, nullptr, &rmt_intr_handle);
  rmt_driver_install(config.channel, 0, 0);  //  rmt_driver_install(rmt_channel_t channel, size_t rx_buf_size, int rmt_intr_num)

  InitialFillBuffers();

  // Sets wrap around - when the buffer is full it starts from the beginning. This is for all channels, for single channel RMT_REG_TX_CONTI_MODE should be possibly used instead of  RMT_MEM_TX_WRAP_EN
  RMT.apb_conf.mem_tx_wrap_en  = true;

  // if the buffer is filled with less than 64 items, transmission stops, even if RMT.apb_conf.mem_tx_wrap_en  = true;
  rmt_fill_tx_items(RMT_CHANNEL_0, items64, 64, 0);
  rmt_tx_start(RMT_CHANNEL_0, 1);
}

static void rmt_example_tx_task(void *arg)
{
  // Stops continous mode
  RMT.apb_conf.mem_tx_wrap_en  = 0;

  // rmt_write_items(config.channel, items, 960, 1);
  // rmt_write_items(config.channel, transmissionEnd, 1, 1);
  // rmt_wait_tx_done(config.channel, portMAX_DELAY);
  vTaskDelete(NULL);
}
 
void loop()
{
  // esp_err_t rmt_write_items(rmt_channel_t channel, rmt_item32_t *rmt_item, int item_num, bool wait_tx_done)

  vTaskDelay(1000);

  xTaskCreate(rmt_example_tx_task, "rmt_nec_tx_task", 2048, NULL, 1, NULL);
  vTaskDelay(100);

  Serial.print(loopCounter++);
  Serial.println("loop");
}