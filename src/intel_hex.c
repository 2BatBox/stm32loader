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
#include <ctype.h>
#include "intel_hex.h"

#define RECORD_TYPE_DATA							(uint8_t)0x00
#define RECORD_TYPE_EOF								(uint8_t)0x01
#define RECORD_TYPE_EXTENDED_SEGMENT_ADDRESS		(uint8_t)0x02
#define RECORD_TYPE_START_SEGMENT_ADDRESS			(uint8_t)0x03
#define RECORD_TYPE_EXTENDED_LINEAR_ADDRESS			(uint8_t)0x04
#define RECORD_TYPE_START_LINEAR_ADDRESS			(uint8_t)0x05

static ih_errors_t read_hex(FILE* file, uint8_t bytes, uint8_t* data){

	printf("read_hex(%d)\n", bytes); //TODO: debug

	int readed = 0;

	while(bytes-- > 0){
		if(fscanf(file, "%2x", data) == EOF)
			return IH_ERR_FORMAT;

		printf(">> ");
		hex_trace(data, 1);

		data++;
	}

	return IH_ERR_OK;
}

ih_errors_t ih_read(FILE* file, ih_storage_t* storage) {
	uint8_t buf [255];
	fscanf(file, "%c", buf);
	printf(">> %c \n", buf[0]);
	return read_hex(file, 2, buf);
}

ih_errors_t ih_write(FILE* file, ih_storage_t* storage);

ih_errors_t ih_release(ih_storage_t* storage);

