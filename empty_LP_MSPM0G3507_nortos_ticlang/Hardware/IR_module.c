#include "ti_msp_dl_config.h"
#include "IR_module.h"

void IR_Module_Read(void)
{
    ir_dh4_state = !!DL_GPIO_readPins(IR_DH_PORT, IR_DH_PIN_3_PIN);
    ir_dh3_state = !!DL_GPIO_readPins(IR_DH_PORT, IR_DH_PIN_2_PIN);
    ir_dh2_state = !!DL_GPIO_readPins(IR_DH_PORT, IR_DH_PIN_1_PIN);
    ir_dh1_state = !!DL_GPIO_readPins(IR_DH_PORT, IR_DH_PIN_0_PIN);
}
