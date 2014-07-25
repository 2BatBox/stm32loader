/*
	stm32loader Open Source flash loader program for ST STM32 microcontrollers.
	Copyright (C) 2014  Yakov Konovalchukov
	konovalchukov.yakov@gmail.com

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define SHOW(x) printf("%d \n", x)

#include "serial.h"
#include "intel_hex.h"
#include "stm32.h"

stm32_errors_t reset(int fd){

	if (fd < 0)
		return STM32_ERR_INVALID_ARGUMENT;

	if(
		serial_signal(fd, SERIAL_SIGNAL_DTR, SIGNAL_HIGH) != SERIAL_ERR_OK ||
		serial_signal(fd, SERIAL_SIGNAL_DTR, SIGNAL_LOW) != SERIAL_ERR_OK ||
		serial_signal(fd, SERIAL_SIGNAL_DTR, SIGNAL_HIGH) != SERIAL_ERR_OK
		)
		return STM32_ERR_SERIAL;

	return STM32_ERR_OK;
}

stm32_errors_t set_boot_pin(int fd, int status){

	if (fd < 0)
		return STM32_ERR_INVALID_ARGUMENT;

	if(serial_signal(fd, SERIAL_SIGNAL_RTS, status) != SERIAL_ERR_OK)
		return STM32_ERR_SERIAL;

	return STM32_ERR_OK;
}

int check_for_errors(const char *msg, stm32_errors_t error, int fd){
	if(error != STM32_ERR_OK){

		printf("%s function error with code %d\n", msg, error);

		switch(error){
			case STM32_ERR_INVALID_ARGUMENT:
				printf("STM32_ERR_INVALID_ARGUMENT");
				break;
			case STM32_ERR_SERIAL:
				printf("STM32_ERR_SERIAL");
				break;
			case STM32_ERR_PROTOCOL:
				printf("STM32_ERR_PROTOCOL");
				break;
			case STM32_ERR_RDP:
				printf("STM32_ERR_RDP");
				break;
		}
		printf("\n");

		return 1;

//		serial_close(fd);
//		exit(1);
	} else
		return 0;
}

void print_error(stm32_errors_t error) {

	switch (error) {
	case STM32_ERR_INVALID_ARGUMENT:
		printf("STM32_ERR_INVALID_ARGUMENT");
		break;
	case STM32_ERR_SERIAL:
		printf("STM32_ERR_SERIAL");
		break;
	case STM32_ERR_PROTOCOL:
		printf("STM32_ERR_PROTOCOL");
		break;
	case STM32_ERR_RDP:
		printf("STM32_ERR_RDP");
		break;
	}
	printf("\n");
}

void action_info(int fd){

	stm32_errors_t error;

	stm32_bootloader_info_t bootloader_info;
	bootloader_info.commands = malloc(0xFF);

	stm32_rpc_info_t rpc_info;

	stm32_device_info_t device_info;
	device_info.deviceId = malloc(0x100);

	if (
			(error = stm32_get(fd, &bootloader_info)) == STM32_ERR_OK &&
			(error = stm32_get_prs(fd, &rpc_info)) == STM32_ERR_OK &&
			(error = stm32_get_id(fd, &device_info)) == STM32_ERR_OK

	) {
		printf("Bootloader version: \t0x%.2X\n", bootloader_info.version);
		printf("Supported commands: \t");
		hex_trace(bootloader_info.commands, bootloader_info.commandsSize);

		printf("Bootloader version: \t0x%.2X\n", rpc_info.version);
		printf("Read protection disable counter:\t%u\n", rpc_info.rpdc);
		printf("Read protection enable counter: \t%u\n", rpc_info.rpec);

		printf("Device id: \t");
		hex_trace(device_info.deviceId, device_info.deviceIdSize);


	} else {
		print_error(error);
	}

	free(bootloader_info.commands);
	free(device_info.deviceId);
}

int main(int argc, char *argv[]) {

/*	FILE* fd = fopen(argv[1], "r");

	if (fd == NULL){
		printf("opening %s error (%d) \n", argv[1], fd);
		return;
	}

*/

//	ih_storage_t hexStorage;

//	ih_errors_t result = ih_read(fd, &hexStorage);

//	printf("result = %d \n", result);

//	uint8_t buf [255];
//	int result = scanf("%2x", buf);
//	printf(">>res: %d %d \n", result, buf[0]);

//	fclose(fd);

	int fd = serial_open(argv[1]);

	if (fd < 0){
		printf("opening port error (%d) \n", fd);
		return;
	}

	serial_errors_t serial_result = serial_setup(fd, SERIAL_BAUD_57600, SERIAL_BITS_8, SERIAL_PARITY_EVEN, SERIAL_STOP_BITS_1);
	stm32_errors_t result;

	if (serial_result != SERIAL_ERR_OK){
		printf("setup port error \n");
		serial_close(fd);
		return;
	}

	check_for_errors("set_boot_pin", set_boot_pin(fd, SIGNAL_HIGH), fd);
	check_for_errors("reset", reset(fd), fd);
	usleep(200);
	check_for_errors("stm32_init", stm32_init(fd), fd);
	action_info(fd);
//	int i;
//	uint16_t pages [0x0FFD];
////	for (i = 0; i < 0x0FFD; i++) {
////		pages[i] = i;
////	}
////
////	uint8_t pages8 [0x100];
////	for (i = 0; i < 0xFF; i++) {
////		pages8[i] = i;
////	}
////	check_for_errors("stm32_extended_erase", stm32_extended_erase(fd, pages, 0x05), fd);
////	check_for_errors("stm32_extended_erase_special", stm32_extended_erase_special(fd, STM32_ERASE_MASS), fd);
////	check_for_errors("stm32_write_protect", stm32_write_protect(fd, pages8, 0x100), fd);
////	check_for_errors("stm32_write_unprotect", stm32_write_unprotect(fd), fd);
////	check_for_errors("stm32_readout_protect", stm32_readout_protect(fd), fd);
////	check_for_errors("stm32_readout_unprotect", stm32_readout_unprotect(fd), fd);
////	uint32_t adr = 0x08000000;
////	uint32_t size = 0xFF;
////	uint8_t *read_buffer;
////	uint8_t write_buffer[256];
////	for (i = 0; i < 256; i++) {
////		write_buffer[i] = 0x00;
////	}
////	check_for_errors("stm32_read", stm32_read(fd, adr, &read_buffer, size), fd);
////	check_for_errors("stm32_write", stm32_write(fd, adr, write_buffer, size), fd);
////	check_for_errors("stm32_read", stm32_read(fd, adr, &read_buffer, size), fd);
////	hex_trace(read_buffer, size);
////	check_for_errors("stm32_set_boot_pin", stm32_set_boot_pin(fd, 0), fd);
////	check_for_errors("stm32_reset", stm32_reset(fd), fd);
//

	check_for_errors("set_boot_pin", set_boot_pin(fd, SIGNAL_LOW), fd);
	check_for_errors("reset", reset(fd), fd);
	usleep(200);
	serial_close(fd);

	return EXIT_SUCCESS;
}
