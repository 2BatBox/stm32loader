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


#ifndef STM32_H_
#define STM32_H_

#include <stdint.h>

typedef enum stm32_errors {
	STM32_ERR_OK,
	STM32_ERR_SERIAL,
	STM32_ERR_PROTOCOL,
	STM32_ERR_INVALID_ARGUMENT,
	STM32_ERR_RDP,
} stm32_errors_t ;

typedef enum stm32_erase_type {
	STM32_ERASE_MASS,
	STM32_ERASE_BANK1,
	STM32_ERASE_BANK2
} stm32_erase_type_t ;

typedef struct stm32_bootloader_info {
	uint8_t version;
	uint8_t commandsSize;
	uint8_t* commands;
} stm32_bootloader_info_t ;

typedef struct stm32_rpc_info {
	uint8_t version;
	uint8_t rpdc;	// read protection disable counter
	uint8_t rpec;	// read protection enable counter
} stm32_rpc_info_t ;

typedef struct stm32_device_info {
	uint8_t* deviceId;
	uint8_t deviceIdSize;
} stm32_device_info_t ;

stm32_errors_t stm32_init(int fd);
stm32_errors_t stm32_get(int fd, stm32_bootloader_info_t* info);
stm32_errors_t stm32_get_prs(int fd, stm32_rpc_info_t* info);
stm32_errors_t stm32_get_id(int fd, stm32_device_info_t* info);
stm32_errors_t stm32_read(int fd, uint32_t start_address, uint8_t **data, uint16_t data_size);
stm32_errors_t stm32_write(int fd, uint32_t start_address, const uint8_t *data, uint16_t data_size);
stm32_errors_t stm32_extended_erase(int fd, const uint16_t *pages, uint16_t pages_size);
stm32_errors_t stm32_extended_erase_special(int fd, stm32_erase_type_t erase_type);
stm32_errors_t stm32_write_protect(int fd, const uint8_t *pages, uint16_t pages_size);
stm32_errors_t stm32_write_unprotect(int fd);
stm32_errors_t stm32_readout_protect(int fd);
stm32_errors_t stm32_readout_unprotect(int fd);

#endif /* STM32_H_ */
