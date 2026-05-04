#include "dvc_remote.h"

extern UART_HandleTypeDef huart3;

uint8_t Rx_buf[64] = {0};		//接收缓冲区

uint16_t sbus_channels[16];

void Remote_callback(uint8_t *data, uint16_t size)
{
	if (Rx_buf[0] == 0x0f && Rx_buf[24] == 0x00)
	{
		sbus_channels[0] = (uint16_t)((Rx_buf[1] | Rx_buf[2] << 8) & 0x07FF);
		sbus_channels[1] = (uint16_t)((Rx_buf[2] >> 3 | Rx_buf[3] << 5) & 0x07FF);
		sbus_channels[2] = (uint16_t)((Rx_buf[3] >> 6 | Rx_buf[4] << 2 | Rx_buf[5] << 10) & 0x07FF);
		sbus_channels[3] = (uint16_t)((Rx_buf[5] >> 1 | Rx_buf[6] << 7) & 0x07FF);
		sbus_channels[4] = (uint16_t)((Rx_buf[6] >> 4 | Rx_buf[7] << 4) & 0x07FF);
		sbus_channels[5] = (uint16_t)((Rx_buf[7] >> 7 | Rx_buf[8] << 1 | Rx_buf[9] << 9) & 0x07FF);
		sbus_channels[6] = (uint16_t)((Rx_buf[9] >> 2 | Rx_buf[10] << 6) & 0x07FF);
		sbus_channels[7] = (uint16_t)((Rx_buf[10] >> 5 | Rx_buf[11] << 3) & 0x07FF);
		sbus_channels[8] = (uint16_t)((Rx_buf[12] | Rx_buf[13] << 8) & 0x07FF);
		sbus_channels[9] = (uint16_t)((Rx_buf[13] >> 3 | Rx_buf[14] << 5) & 0x07FF);
		sbus_channels[10] = (uint16_t)((Rx_buf[14] >> 6 | Rx_buf[15] << 2 | Rx_buf[16] << 10) & 0x07FF);
		sbus_channels[11] = (uint16_t)((Rx_buf[16] >> 1 | Rx_buf[17] << 7) & 0x07FF);
		sbus_channels[12] = (uint16_t)((Rx_buf[17] >> 4 | Rx_buf[18] << 4) & 0x07FF);
		sbus_channels[13] = (uint16_t)((Rx_buf[18] >> 7 | Rx_buf[19] << 1 | Rx_buf[20] << 9) & 0x07FF);
		sbus_channels[14] = (uint16_t)((Rx_buf[20] >> 2 | Rx_buf[21] << 6) & 0x07FF);
		sbus_channels[15] = (uint16_t)((Rx_buf[21] >> 5 | Rx_buf[22] << 3) & 0x07FF);
		UART_Print("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n",sbus_channels[0],sbus_channels[1],sbus_channels[2],sbus_channels[3],sbus_channels[4],sbus_channels[5],sbus_channels[6],sbus_channels[7],sbus_channels[8],sbus_channels[9]);
	}
	HAL_UARTEx_ReceiveToIdle_DMA(&huart3,Rx_buf,64);
}