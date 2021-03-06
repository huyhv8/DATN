/*----------------------------------------------------------------------------
 * Name:    demo.h
 * Purpose: USB HID Demo Definitions
 * Version: V1.20
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/
 
#ifndef __DEMO_H
#define __DEMO_H

 
#include "type.h"
#include <stdio.h>
#include <string.h>
#include "type.h"
#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"

/* Push Button Definitions */
#define PB_INT0         0x00000400  /* P2.10 */

/* LED Definitions */
#define LED_MSK         0x000000FF  /* P2.0..7 */

/* HID Demo Variables */
extern U8 InReport;
extern U8 OutReport;

/* HID Demo Functions */
extern void GetInReport  (void);
extern void SetOutReport (void);

extern BYTE 	volatile WReady;
extern BYTE 	volatile RReady;

#define  MAX_DEVICE_STRING_LENGTH 1024
#define  MAX_PACKET_SIZE		  	58
#define  MAX_NUMBER_SIGNATURES		31
#define  MAX_SIGNATURE_SIZE			0x4000
#define	 BLOCK_SIZE					256	
#define	 BLOCK_COUNT				512
#define  PAYLOAD_SIZE				252	

typedef  unsigned short USHORT	 ;

enum USB_CMD
{
	USB_CMD_READ = 0x01,
	USB_CMD_WRITE,
	USB_CMD_INFO,
	USB_CMD_AUTHENTICATE,
	USB_CMD_ADD,
	USB_CMD_SETPASSWORD,
	USB_CMD_ACK,
	USB_CMD_FAIL
};



//Define device states

#define USB_STATE_UNAUTHENTICATED	0x00
#define USB_STATE_AUTHENTICATED		0x01
#define USB_STATE_BIOSIGNREAD		0x02
//#define PASSWORD_SIZE 0xF

typedef struct _DATA_PACKET
{
	BYTE   iCmd;	
	BYTE   iIndex;  //Index of signature to process, ignore for 2,3,4 command
	USHORT iLen; 
	USHORT iOffset;//Length and offset of data	
	BYTE   SignData[MAX_PACKET_SIZE];
} DATA_PACKET;

#define USERNAME_SIZE 30
#define PASSWORD_SIZE 33
typedef struct _AUTHENTICATE_PACKET   //??? need more consideration
{
	BYTE	Username[USERNAME_SIZE];
	BYTE	Password[PASSWORD_SIZE];
} AUTHENTICATE_PACKET;

typedef struct _INFO_PACKET
{
	//Number of signature stored in device
	BYTE   iCmd; 	
	BYTE   iCount;	
	USHORT aSignSizes[MAX_NUMBER_SIGNATURES];
} INFO_PACKET;

typedef struct _USBPKI_PACKET
{
	BYTE iCmd;		//1: read a signature
					//2: write a signature
					//3: inquire number of signatures
					//4: authenticate
					//5: add new signature
					//etc	...
	BYTE aData[63];

} USBPKI_PACKET;

typedef struct _BIO_SIGNATURE  //Need more consideration
{
	USHORT iSize;
	BYTE   aData[MAX_SIGNATURE_SIZE];	
}BIO_SIGNATURE;

typedef struct _EEPROM_HEADER
{
	BYTE    Password[10];
	USHORT 	iCount;
	BYTE	aMap[64];
	USHORT  aSignSizes[45];
	USHORT	aSignAddrs[45];
} EEPROM_HEADER;

typedef struct _EEPROM_BLOCK
{
	short	NextBlockOffset;
	USHORT  Flags;
	BYTE	Data[252];
}EEPROM_BLOCK;

/*******************************
Function prototype
*******************************/
USHORT Checksum16(USHORT * pData, USHORT iLength);
BOOL AuthenticatePIN(AUTHENTICATE_PACKET aAuthenticatePacket);
BOOL GetInfo();
BOOL SetPassword();
BOOL WriteRequest();
BOOL ReadRequest();

extern USBPKI_PACKET aPacket;

#endif
