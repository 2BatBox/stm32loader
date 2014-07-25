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


#ifndef SERIAL_H_
#define SERIAL_H_

typedef enum serial_baud {
	SERIAL_BAUD_1200,
	SERIAL_BAUD_1800,
	SERIAL_BAUD_2400,
	SERIAL_BAUD_4800,
	SERIAL_BAUD_9600,
	SERIAL_BAUD_19200,
	SERIAL_BAUD_38400,
	SERIAL_BAUD_57600,
	SERIAL_BAUD_115200,
} serial_baud_t ;

typedef enum serial_bits {
	SERIAL_BITS_5,
	SERIAL_BITS_6,
	SERIAL_BITS_7,
	SERIAL_BITS_8
} serial_bits_t ;

typedef enum serial_parity {
	SERIAL_PARITY_NONE,
	SERIAL_PARITY_EVEN,
	SERIAL_PARITY_ODD
} serial_parity_t  ;

typedef enum serial_stop_bits {
	SERIAL_STOP_BITS_1,
	SERIAL_STOP_BITS_2
} serial_stop_bits_t ;

typedef enum serial_signals {
	SERIAL_SIGNAL_DTR,
	SERIAL_SIGNAL_RTS,
} serial_signals_t ;

typedef enum serial_errors {
	SERIAL_ERR_OK,
	SERIAL_ERR_INVALIG_ARGUMENT,
	SERIAL_ERR_SYSTEM
} serial_errors_t ;


int serial_open(const char *device);
serial_errors_t serial_flush(int fd);
serial_errors_t serial_close(int fd);
serial_errors_t serial_setup(int fd, serial_baud_t baud, serial_bits_t bits, serial_parity_t parity, serial_stop_bits_t stop_bits);
serial_errors_t serial_read(int fd, const void *buffer, int len);
serial_errors_t serial_write(int fd, const void *buffer, int len);
serial_errors_t serial_signal(int fd, serial_signals_t signal, int status);

#endif /* SERIAL_H_ */
