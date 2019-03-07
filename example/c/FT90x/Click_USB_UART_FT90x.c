/*
Example for USB_UART Click

    Date          : Dec 2017.
    Author        : MikroE Team

Test configuration FT90x :
    
    MCU                : FT900
    Dev. Board         : EasyFT90x v7 
    FT90x Compiler ver : v2.2.1.0

---

Description :

The application is composed of three sections :

- System Initialization - Intializes UART module
- Application Initialization - Driver intialization
- Application Task - (code snippet) - Checks if new data byte have received in rx buffer (ready for reading),
  and if ready than reads one byte from rx buffer. In second case aplication task writes
  message data via UART.


*/

#include "Click_USB_UART_types.h"
#include "Click_USB_UART_config.h"

const uint8_t MESSAGE_DATA[9] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

void systemInit()
{
    mikrobus_uartInit( _MIKROBUS1, &_USB_UART_UART_CFG[0] );
    mikrobus_logInit( _MIKROBUS1, 9600 );

    Delay_ms( 100 );
}

void applicationInit()
{
    usb_uart_uartDriverInit( (T_USB_UART_P)&_MIKROBUS1_GPIO, (T_USB_UART_P)&_MIKROBUS1_UART );
    mikrobus_logWrite( "Initialized", _LOG_LINE );
    Delay_ms( 100 );
}

void applicationTask()
{
    uint8_t tmp;
	char rec;
    uint8_t rdyFlag;

// RECEIVER - UART polling

rdyFlag = usb_uart_byteReady();

    if (1 == rdyFlag)
    {
        rec = usb_uart_readByte();
        mikrobus_logWrite( &rec, _LOG_BYTE );
    }

// TRANSMITER - TX each 2 sec
/*for (tmp = 0; tmp < 9; tmp++)
    {
        usb_uart_writeByte( MESSAGE_DATA[tmp] );
    }
    mikrobus_logWrite( "MESSAGE SENT", _LOG_LINE );
    Delay_ms(2000);*/
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}