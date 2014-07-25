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


#ifndef INTEL_HEX_H_
#define INTEL_HEX_H_

#include <stdint.h>

typedef enum ih_errors {
	IH_ERR_OK,
	IH_ERR_FILE_IO,
	IH_ERR_FORMAT
} ih_errors_t ;

typedef struct ih_record {
	uint32_t address;
	uint8_t* data;
	uint8_t size;
} ih_record_t ;

typedef struct ih_storage {
	ih_record_t* first;
	uint32_t size;
} ih_storage_t ;


ih_errors_t ih_read(FILE* file, ih_storage_t* storage);
ih_errors_t ih_write(FILE* file, ih_storage_t* storage);

ih_errors_t ih_release(ih_storage_t* storage);

#endif /* INTEL_HEX_H_ */
