/**
 * @file    CSP_Config.h
 * @author  Deadline039
 * @brief   The CSP configuration of STM32F1xx.
 * @version 1.0
 * @date    2024-10-22
 * @note    Reference the CMSIS RTE Devices.
 */

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef __CSP_CONFIG_H
#define __CSP_CONFIG_H

// <e> USART1 (Universal synchronous asynchronous receiver transmitter)
#define USART1_ENABLE     1

//   <o> USART1 IO Remap
//        <0=>No remap (TX/PA9, RX/PA10, CTS/PA11, RTS/PA12)
//        <1=>Remap    (TX/PB6, RX/PB7,  CTS/PA11, RTS/PA12)
#define USART1_IO_REMAP   0

//   <q> Enable USART1 TX
#define USART1_TX_ENABLE  1
//   <q> Enable USART1 RX
#define USART1_RX_ENABLE  1
//   <q> Enable USART1 CTS
#define USART1_CTS_ENABLE 0
//   <q> Enable USART1 RTS
#define USART1_RTS_ENABLE 0

#if (USART1_IO_REMAP == 0)
#define USART1_AFIO_REMAP() __HAL_AFIO_REMAP_USART1_DISABLE()
#if USART1_TX_ENABLE
#define USART1_TX_PORT A
#define USART1_TX_PIN  GPIO_PIN_9
#endif
#if USART1_RX_ENABLE
#define USART1_RX_PORT A
#define USART1_RX_PIN  GPIO_PIN_10
#endif
#if USART1_CTS_ENABLE
#define USART1_CTS_PORT A
#define USART1_CTS_PIN  GPIO_PIN_11
#endif
#if USART1_RTS_ENABLE
#define USART1_RTS_PORT A
#define USART1_RTS_PIN  GPIO_PIN_12
#endif
#elif (USART1_IO_REMAP == 1)
#define USART1_AFIO_REMAP() __HAL_AFIO_REMAP_USART1_ENABLE()
#if USART1_TX_ENABLE
#define USART1_TX_PORT B
#define USART1_TX_PIN  GPIO_PIN_6
#endif
#if USART1_RX_ENABLE
#define USART1_RX_PORT B
#define USART1_RX_PIN  GPIO_PIN_7
#endif
#if USART1_CTS_ENABLE
#define USART1_CTS_PORT A
#define USART1_CTS_PIN  GPIO_PIN_11
#endif
#if USART1_RTS_ENABLE
#define USART1_RTS_PORT A
#define USART1_RTS_PIN  GPIO_PIN_12
#endif
#else
#error "Invalid USART1 IO Remap Configuration! "
#endif

//   <o> USART1 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of USART1
#define USART1_IT_PRIORITY        2
//   <o> USART1 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of USART1
#define USART1_IT_SUB             3

//   <e> DMA Rx
//     <o1> Number <2=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <4=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o4> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o5> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//     <o6> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//     <o7> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//   </e>
#define USART1_RX_DMA             1
#define USART1_RX_DMA_NUMBER      2
#define USART1_RX_DMA_CHANNEL     4
#define USART1_RX_DMA_PRIORITY    1
#define USART1_RX_DMA_IT_PRIORITY 2
#define USART1_RX_DMA_IT_SUB      2
#define USART1_RX_DMA_BUF_SIZE    256
#define USART1_RX_DMA_FIFO_SIZE   256

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very high
//     <i>  Set DMA Channel priority
//     <o4> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o5> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//     <o6> The size of Send buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
//   </e>
#define USART1_TX_DMA             1
#define USART1_TX_DMA_NUMBER      1
#define USART1_TX_DMA_CHANNEL     4
#define USART1_TX_DMA_PRIORITY    0
#define USART1_TX_DMA_IT_PRIORITY 1
#define USART1_TX_DMA_IT_SUB      4
#define USART1_TX_DMA_BUF_SIZE    256

// </e>

// <e> USART2 (Universal synchronous asynchronous receiver transmitter)
#define USART2_ENABLE             0

//   <o> USART2 IO Remap
//        <0=>No remap (TX/PA2, RX/PA3, CTS/PA0, RTS/PA1)
//        <1=>Remap    (TX/PD5, RX/PD6, CTS/PD3, RTS/PD4)
#define USART2_IO_REMAP           0

//   <q> Enable USART2 TX
#define USART2_TX_ENABLE          0
//   <q> Enable USART2 RX
#define USART2_RX_ENABLE          0
//   <q> Enable USART2 CTS
#define USART2_CTS_ENABLE         0
//   <q> Enable USART2 RTS
#define USART2_RTS_ENABLE         0

#if (USART2_IO_REMAP == 0)
#define USART2_AFIO_REMAP() __HAL_AFIO_REMAP_USART2_DISABLE()
#if USART2_TX_ENABLE
#define USART2_TX_PORT A
#define USART2_TX_PIN  GPIO_PIN_2
#endif
#if USART2_RX_ENABLE
#define USART2_RX_PORT A
#define USART2_RX_PIN  GPIO_PIN_3
#if USART2_CTS_ENABLE
#define USART2_CTS_PORT A
#define USART2_CTS_PIN  GPIO_PIN_0
#endif
#if USART2_RTS_ENABLE
#define USART2_RTS_PORT A
#define USART2_RTS_PIN  GPIO_PIN_1
#endif
#endif
#elif (USART2_IO_REMAP == 1)
#define USART2_AFIO_REMAP() __HAL_AFIO_REMAP_USART2_ENABLE()
#if USART2_TX_ENABLE
#define USART2_TX_PORT D
#define USART2_TX_PIN  GPIO_PIN_5
#endif
#if USART2_RX_ENABLE
#define USART2_RX_PORT D
#define USART2_RX_PIN  GPIO_PIN_6
#endif
#if USART2_CTS_ENABLE
#define USART2_CTS_PORT D
#define USART2_CTS_PIN  GPIO_PIN_3
#endif
#if USART2_RTS_ENABLE
#define USART2_RTS_PORT D
#define USART2_RTS_PIN  GPIO_PIN_4
#endif
#else
#error "Invalid USART2 IO Remap Configuration! "
#endif

//   <o> USART2 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of USART2
#define USART2_IT_PRIORITY        2
//   <o> USART2 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of USART2
#define USART2_IT_SUB             3

//   <e> DMA Rx
//     <o1> Number <2=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <6=>6
//     <i>  Selects DMA Channel (only Channel 6 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o4> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o5> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//     <o6> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//     <o7> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//   </e>
#define USART2_RX_DMA             0
#define USART2_RX_DMA_NUMBER      2
#define USART2_RX_DMA_CHANNEL     6
#define USART2_RX_DMA_PRIORITY    1
#define USART2_RX_DMA_IT_PRIORITY 2
#define USART2_RX_DMA_IT_SUB      2
#define USART2_RX_DMA_BUF_SIZE    256
#define USART2_RX_DMA_FIFO_SIZE   256

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <7=>7
//     <i>  Selects DMA Channel (only Channel 7 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very high
//     <i>  Set DMA Channel priority
//     <o4> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o5> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//     <o6> The size of Send buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
//   </e>
#define USART2_TX_DMA             0
#define USART2_TX_DMA_NUMBER      1
#define USART2_TX_DMA_CHANNEL     7
#define USART2_TX_DMA_PRIORITY    0
#define USART2_TX_DMA_IT_PRIORITY 1
#define USART2_TX_DMA_IT_SUB      4
#define USART2_TX_DMA_BUF_SIZE    256

// </e>

// <e> USART3 (Universal synchronous asynchronous receiver transmitter)
#define USART3_ENABLE             0

//   <o> USART3 IO Remap
//        <0=>No remap        (TX/PB10, RX/PB11, CTS/PB13, RTS/PB14)
//        <1=>Partial Remap   (TX/PC10, RX/PC11, CTS/PB13, RTS/PB14)
//        <2=>Full Remap      (TX/PD8,  RX/PD9,  CTS/PD11, RTS/PD12)
#define USART3_IO_REMAP           1

//   <q> Enable USART3 TX
#define USART3_TX_ENABLE          0
//   <q> Enable USART3 RX
#define USART3_RX_ENABLE          0
//   <q> Enable USART3 CTS
#define USART3_CTS_ENABLE         0
//   <q> Enable USART3 RTS
#define USART3_RTS_ENABLE         0

#if (USART3_IO_REMAP == 0)
#define USART3_AFIO_REMAP() __HAL_AFIO_REMAP_USART3_DISABLE()
#if USART3_TX_ENABLE
#define USART3_TX_PORT C
#define USART3_TX_PIN  GPIO_PIN_10
#endif
#if USART3_RX_ENABLE
#define USART3_RX_PORT C
#define USART3_RX_PIN  GPIO_PIN_11
#endif
#if USART3_CTS_ENABLE
#define USART3_CTS_PORT B
#define USART3_CTS_PIN  GPIO_PIN_13
#endif
#if USART3_RTS_ENABLE
#define USART3_RTS_PORT B
#define USART3_RTS_PIN  GPIO_PIN_14
#endif
#elif (USART3_IO_REMAP == 1)
#define USART3_AFIO_REMAP() __HAL_AFIO_REMAP_USART3_PARTIAL()
#if USART3_TX_ENABLE
#define USART3_TX_PORT C
#define USART3_TX_PIN  GPIO_PIN_10
#endif
#if USART3_RX_ENABLE
#define USART3_RX_PORT C
#define USART3_RX_PIN  GPIO_PIN_11
#endif
#if USART3_CTS_ENABLE
#define USART3_CTS_PORT B
#define USART3_CTS_PIN  GPIO_PIN_13
#endif
#if USART3_RTS_ENABLE
#define USART3_RTS_PORT B
#define USART3_RTS_PIN  GPIO_PIN_14
#endif
#elif (USART3_IO_REMAP == 2)
#define USART3_AFIO_REMAP() __HAL_AFIO_REMAP_USART3_ENABLE()
#if USART3_TX_ENABLE
#define USART3_TX_PORT D
#define USART3_TX_PIN  GPIO_PIN_8
#endif
#if USART3_RX_ENABLE
#define USART3_RX_PORT D
#define USART3_RX_PIN  GPIO_PIN_9
#endif
#if USART3_CTS_ENABLE
#define USART3_CTS_PORT D
#define USART3_CTS_PIN  GPIO_PIN_11
#endif
#if USART3_RTS_ENABLE
#define USART3_RTS_PORT D
#define USART3_RTS_PIN  GPIO_PIN_12
#endif
#else
#error "Invalid USART3 IO Remap Configuration! "
#endif

//   <o> USART3 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of USART3
#define USART3_IT_PRIORITY        2
//   <o> USART3 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of USART3
#define USART3_IT_SUB             3

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <3=>3
//     <i>  Selects DMA Channel (only Channel 3 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very high
//     <i>  Sets DMA Channel priority
//     <o4> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o5> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//     <o6> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//     <o7> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//   </e>
#define USART3_RX_DMA             0
#define USART3_RX_DMA_NUMBER      1
#define USART3_RX_DMA_CHANNEL     3
#define USART3_RX_DMA_PRIORITY    0
#define USART3_RX_DMA_IT_PRIORITY 2
#define USART3_RX_DMA_IT_SUB      2
#define USART3_RX_DMA_BUF_SIZE    256
#define USART3_RX_DMA_FIFO_SIZE   256

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <2=>2
//     <i>  Selects DMA Channel (only Channel 2 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very high
//     <i>  Sets DMA Channel priority
//     <o4> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o5> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//     <o6> The size of Send buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
//   </e>
#define USART3_TX_DMA             0
#define USART3_TX_DMA_NUMBER      1
#define USART3_TX_DMA_CHANNEL     2
#define USART3_TX_DMA_PRIORITY    0
#define USART3_TX_DMA_IT_PRIORITY 1
#define USART3_TX_DMA_IT_SUB      4
#define USART3_TX_DMA_BUF_SIZE    256

// </e>

// <e> UART4 (Universal asynchronous receiver transmitter)
#define UART4_ENABLE              0

//   <q> Enable UART4 TX (PC10)
#define UART4_TX_ENABLE           0
//   <q> Enable UART4 RX (PC11)
#define UART4_RX_ENABLE           0

#if UART4_TX_ENABLE
#define UART4_TX_PORT C
#define UART4_TX_PIN  GPIO_PIN_10
#endif
#if UART4_RX_ENABLE
#define UART4_RX_PORT C
#define UART4_RX_PIN  GPIO_PIN_11
#endif

//   <o> UART4 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of UART4
#define UART4_IT_PRIORITY        2
//   <o> UART4 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of UART4
#define UART4_IT_SUB             3

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Channel <3=>3
//     <i>  Selects DMA Channel (only Channel 3 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very high
//     <i>  Sets DMA Channel priority
//     <o4> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o5> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//     <o6> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//     <o7> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//   </e>
#define UART4_RX_DMA             0
#define UART4_RX_DMA_NUMBER      2
#define UART4_RX_DMA_CHANNEL     3
#define UART4_RX_DMA_PRIORITY    0
#define UART4_RX_DMA_IT_PRIORITY 2
#define UART4_RX_DMA_IT_SUB      2
#define UART4_RX_DMA_BUF_SIZE    256
#define UART4_RX_DMA_FIFO_SIZE   256

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very high
//     <i>  Sets DMA Channel priority
//     <o4> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o5> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//     <o6> The size of Send buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
//   </e>
#define UART4_TX_DMA             0
#define UART4_TX_DMA_NUMBER      2
#define UART4_TX_DMA_CHANNEL     5
#define UART4_TX_DMA_PRIORITY    0
#define UART4_TX_DMA_IT_PRIORITY 1
#define UART4_TX_DMA_IT_SUB      4
#define UART4_TX_DMA_BUF_SIZE    256

// </e>

// <e> UART5 (Universal synchronous asynchronous receiver transmitter)
#define UART5_ENABLE             0

//   <q> Enable UART5 TX (PC12)
#define UART5_TX_ENABLE          0
//   <q> Enable UART5 RX (PD2)
#define UART5_RX_ENABLE          0

#if UART5_TX_ENABLE
#define UART5_TX_PORT C
#define UART5_TX_PIN  GPIO_PIN_12
#endif
#if UART5_RX_ENABLE
#define UART5_RX_PORT D
#define UART5_RX_PIN  GPIO_PIN_2
#endif

//   <o> UART5 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of UART5
#define UART5_IT_PRIORITY 2
//   <o> UART5 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of UART5
#define UART5_IT_SUB      3

// </e>

// <e> I2C1 (Inter-integrated Circuit Interface 1)
#define I2C1_ENABLE       0

//   <o> I2C1 IO Remap
//        <0=>No remap   (SCL/PB6, SDA/PB7)
//        <1=>Remap      (SCL/PB8, SDA/PB9)
#define I2C1_IO_REMAP     0

#if (I2C1_IO_REMAP == 0)
#define I2C1_AFIO_REMAP() __HAL_AFIO_REMAP_I2C1_DISABLE()
#define I2C1_SCL_PORT     B
#define I2C1_SCL_PIN      GPIO_PIN_6
#define I2C1_SDA_PORT     B
#define I2C1_SDA_PIN      GPIO_PIN_7
#elif (I2C1_IO_REMAP == 1)
#define I2C1_SCL_PORT B
#define I2C1_SCL_PIN  GPIO_PIN_8
#define I2C1_SDA_PORT B
#define I2C1_SDA_PIN  GPIO_PIN_9
#else
#error "Invalid I2C1 IO Remap Configuration! "
#endif

//   <e> I2C1 Interrupt
//   <i> Must be enabled when using DMA.
#define I2C1_IT_ENABLE          0
//      <o> I2C1 Interrupt Priority <0-15>
//      <i> The Interrupt Priority of I2C1
#define I2C1_IT_PRIORITY        2
//      <o> I2C1 Interrupt SubPriority <0-15>
//      <i> The Interrupt SubPriority of I2C1
#define I2C1_IT_SUB             3
//   </e>

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <7=>7
//     <i>  Selects DMA Channel (only Channel 7 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o4> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o5> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//   </e>
#define I2C1_RX_DMA             0
#define I2C1_RX_DMA_NUMBER      1
#define I2C1_RX_DMA_CHANNEL     7
#define I2C1_RX_DMA_PRIORITY    0
#define I2C1_RX_DMA_IT_PRIORITY 2
#define I2C1_RX_DMA_IT_SUB      2

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <6=>6
//     <i>  Selects DMA Channel (only Channel 6 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o4> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o5> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//   </e>
#define I2C1_TX_DMA             0
#define I2C1_TX_DMA_NUMBER      1
#define I2C1_TX_DMA_CHANNEL     6
#define I2C1_TX_DMA_PRIORITY    0
#define I2C1_TX_DMA_IT_PRIORITY 1
#define I2C1_TX_DMA_IT_SUB      4

// </e>

// <e> I2C2 (Inter-integrated Circuit Interface 2)
// <i> SCL/PB10, SDA/PB11
#define I2C2_ENABLE             0

//   <e> I2C2 Interrupt
//   <i> Must be enabled when using DMA.
#define I2C2_IT_ENABLE          0
//      <o> I2C2 Interrupt Priority <0-15>
//      <i> The Interrupt Priority of I2C2
#define I2C2_IT_PRIORITY        2
//      <o> I2C2 Interrupt SubPriority <0-15>
//      <i> The Interrupt SubPriority of I2C2
#define I2C2_IT_SUB             3
//   </e>

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o4> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o5> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//   </e>
#define I2C2_RX_DMA             1
#define I2C2_RX_DMA_NUMBER      1
#define I2C2_RX_DMA_CHANNEL     5
#define I2C2_RX_DMA_PRIORITY    0
#define I2C2_RX_DMA_IT_PRIORITY 2
#define I2C2_RX_DMA_IT_SUB      2

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o4> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o5> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//   </e>
#define I2C2_TX_DMA             1
#define I2C2_TX_DMA_NUMBER      1
#define I2C2_TX_DMA_CHANNEL     4
#define I2C2_TX_DMA_PRIORITY    0
#define I2C2_TX_DMA_IT_PRIORITY 1
#define I2C2_TX_DMA_IT_SUB      4

// </e>

// <e> SPI1 (Serial Peripheral Interface 1)
#define SPI1_ENABLE             0

//   <o> SPI1 IO Remap
//        <0=>No remap   (NSS/PA4,  SCK/PA5, MISO/PA6, MOSI/PA7)
//        <1=>Remap      (NSS/PA15, SCK/PB3, MISO/PB4, MOSI/PB5)
#define SPI1_IO_REMAP           0

//   <q> Enable SPI1 NSS
#define SPI1_NSS_ENABLE         0
//   <q> Enable SPI1 MISO
#define SPI1_MISO_ENABLE        0
//   <q> Enable SPI1 MOSI
#define SPI1_MOSI_ENABLE        0

#if (SPI1_IO_REMAP == 0)
#define SPI1_AFIO_REMAP() __HAL_AFIO_REMAP_SPI1_DISABLE()
#define SPI1_SCK_PORT     A
#define SPI1_SCK_PIN      5
#if SPI1_NSS_ENABLE
#define SPI1_NSS_PORT A
#define SPI1_NSS_PIN  4
#endif
#if SPI1_MISO_ENABLE
#define SPI1_MISO_PORT A
#define SPI1_MISO_PIN  6
#endif
#if SPI1_MOSI_ENABLE
#define SPI1_MOSI_PORT A
#define SPI1_MOSI_PIN  7
#endif
#elif (SPI1_IO_REMAP == 1)
#define SPI1_AFIO_REMAP() __HAL_AFIO_REMAP_SPI1_ENABLE()
#define SPI1_SCK_PORT     B
#define SPI1_SCK_PIN      3
#if SPI1_NSS_ENABLE
#define SPI1_NSS_PORT A
#define SPI1_NSS_PIN  15
#endif
#if SPI1_MISO_ENABLE
#define SPI1_MISO_PORT B
#define SPI1_MISO_PIN  4
#endif
#if SPI1_MOSI_ENABLE
#define SPI1_MOSI_PORT B
#define SPI1_MOSI_PIN  5
#endif
#else
#error "Invalid SPI1 IO Remap Configuration! "
#endif

//   <e> SPI1 Interrupt
//   <i> Must be enabled when using DMA.
#define SPI1_IT_ENABLE          0
//      <o> SPI1 Interrupt Priority <0-15>
//      <i> The Interrupt Priority of SPI1
#define SPI1_IT_PRIORITY        2
//      <o> SPI1 Interrupt SubPriority <0-15>
//      <i> The Interrupt SubPriority of SPI1
#define SPI1_IT_SUB             3
//   </e>

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <2=>2
//     <i>  Selects DMA Channel (only Channel 2 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o4> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o5> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//   </e>
#define SPI1_RX_DMA             0
#define SPI1_RX_DMA_NUMBER      1
#define SPI1_RX_DMA_CHANNEL     2
#define SPI1_RX_DMA_PRIORITY    0
#define SPI1_RX_DMA_IT_PRIORITY 2
#define SPI1_RX_DMA_IT_SUB      2

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <3=>3
//     <i>  Selects DMA Channel (only Channel 3 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o4> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o5> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//   </e>
#define SPI1_TX_DMA             0
#define SPI1_TX_DMA_NUMBER      1
#define SPI1_TX_DMA_CHANNEL     3
#define SPI1_TX_DMA_PRIORITY    0
#define SPI1_TX_DMA_IT_PRIORITY 1
#define SPI1_TX_DMA_IT_SUB      4

// </e>

// <e> SPI2 (Serial Peripheral Interface 2)
// <i> SCK/PB13
#define SPI2_ENABLE             0

//   <q> Enable SPI2 NSS  (PB12)
#define SPI2_NSS_ENABLE         0
//   <q> Enable SPI2 MISO (PB14)
#define SPI2_MISO_ENABLE        0
//   <q> Enable SPI2 MOSI (PB15)
#define SPI2_MOSI_ENABLE        0

#define SPI2_SCK_PORT           B
#define SPI2_SCK_PIN            13

#if SPI2_NSS_ENABLE
#define SPI2_NSS_PORT A
#define SPI2_NSS_PIN  12
#endif

#if SPI2_MISO_ENABLE
#define SPI2_MISO_PORT B
#define SPI2_MISO_PIN  14
#endif

#if SPI2_MOSI_ENABLE
#define SPI2_MOSI_PORT B
#define SPI2_MOSI_PIN  15
#endif

//   <e> SPI2 Interrupt
//   <i> Must be enabled when using DMA.
#define SPI2_IT_ENABLE          0
//      <o> SPI2 Interrupt Priority <0-15>
//      <i> The Interrupt Priority of SPI2
#define SPI2_IT_PRIORITY        2
//      <o> SPI2 Interrupt SubPriority <0-15>
//      <i> The Interrupt SubPriority of SPI2
#define SPI2_IT_SUB             3
//   </e>

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o4> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o5> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//   </e>
#define SPI2_RX_DMA             0
#define SPI2_RX_DMA_NUMBER      1
#define SPI2_RX_DMA_CHANNEL     4
#define SPI2_RX_DMA_PRIORITY    0
#define SPI2_RX_DMA_IT_PRIORITY 2
#define SPI2_RX_DMA_IT_SUB      2

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o4> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o5> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//     <o4> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o5> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//   </e>
#define SPI2_TX_DMA             0
#define SPI2_TX_DMA_NUMBER      1
#define SPI2_TX_DMA_CHANNEL     5
#define SPI2_TX_DMA_PRIORITY    0
#define SPI2_TX_DMA_IT_PRIORITY 1
#define SPI2_TX_DMA_IT_SUB      4

// </e>

// <e> SPI3 (Serial Peripheral Interface 3)
#define SPI3_ENABLE             0

//   <o> SPI3/I2S3 IO Remap (NSS->WS, MOSI->SD)
//        <0=>No remap   (NSS/PA15, SCK/PB3,  MISO/PB4,  MOSI/PB5 )
//        <1=>Remap      (NSS/PA4,  SCK/PC10, MISO/PC11, MOSI/PC12)
#define SPI3_IO_REMAP           0

//   <q> Enable SPI3 NSS
#define SPI3_NSS_ENABLE         0
//   <q> Enable SPI3 MISO
#define SPI3_MISO_ENABLE        0
//   <q> Enable SPI3 MOSI
#define SPI3_MOSI_ENABLE        0

#if (SPI3_IO_REMAP == 0)
#define SPI3_AFIO_REMAP() __HAL_AFIO_REMAP_SPI3_ENABLE()
#define SPI3_SCK_PORT     B
#define SPI3_SCK_PIN      3
#if SPI3_NSS_ENABLE
#define SPI3_NSS_PORT A
#define SPI3_NSS_PIN  15
#endif
#if SPI3_MISO_ENABLE
#define SPI3_MISO_PORT B
#define SPI3_MISO_PIN  4
#endif
#if SPI3_MOSI_ENABLE
#define SPI3_MOSI_PORT B
#define SPI3_MOSI_PIN  5
#endif
#elif (SPI3_IO_REMAP == 1)
#define SPI3_AFIO_REMAP() __HAL_AFIO_REMAP_SPI3_DISABLE()
#define SPI3_SCK_PORT     C
#define SPI3_SCK_PIN      10
#if SPI3_NSS_ENABLE
#define SPI3_NSS_PORT A
#define SPI3_NSS_PIN  4
#endif
#if SPI3_MISO_ENABLE
#define SPI3_MISO_PORT C
#define SPI3_MISO_PIN  11
#endif
#if SPI3_MOSI_ENABLE
#define SPI3_MOSI_PORT C
#define SPI3_MOSI_PIN  12
#endif
#else
#error "Invalid SPI3 IO Remap Configuration! "
#endif

//   <e> SPI3 Interrupt
//   <i> Must be enabled when using DMA.
#define SPI3_IT_ENABLE          0
//      <o> SPI3 Interrupt Priority <0-15>
//      <i> The Interrupt Priority of SPI3
#define SPI3_IT_PRIORITY        2
//      <o> SPI3 Interrupt SubPriority <0-15>
//      <i> The Interrupt SubPriority of SPI3
#define SPI3_IT_SUB             3
//   </e>

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Channel <1=>1
//     <i>  Selects DMA Channel (only Channel 1 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o4> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o5> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//   </e>
#define SPI3_RX_DMA             0
#define SPI3_RX_DMA_NUMBER      2
#define SPI3_RX_DMA_CHANNEL     1
#define SPI3_RX_DMA_PRIORITY    0
#define SPI3_RX_DMA_IT_PRIORITY 2
#define SPI3_RX_DMA_IT_SUB      2

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Channel <2=>2
//     <i>  Selects DMA Channel (only Channel 2 can be used)
//     <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o4> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o5> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//   </e>
#define SPI3_TX_DMA             0
#define SPI3_TX_DMA_NUMBER      2
#define SPI3_TX_DMA_CHANNEL     2
#define SPI3_TX_DMA_PRIORITY    0
#define SPI3_TX_DMA_IT_PRIORITY 1
#define SPI3_TX_DMA_IT_SUB      4

// </e>

// <e> CAN1 (Controller Area Network 1)
#define CAN1_ENABLE             1

//   <o> CAN1_RX Pin <0=>PA11 <1=>PB8 <2=>PD0
#define CAN1_RX_PORT_ID         0
#if (CAN1_RX_PORT_ID == 0)
#define CAN1_RX_PORT A
#define CAN1_RX_PIN  GPIO_PIN_11
#elif (CAN1_RX_PORT_ID == 1)
#define CAN1_RX_PORT B
#define CAN1_RX_PIN  GPIO_PIN_8
#elif (CAN1_RX_PORT_ID == 2)
#define CAN1_RX_PORT D
#else
#error "Invalid CAN1_RX Pin Configuration!"
#endif

//   <o> CAN1_TX Pin <0=>PA12 <1=>PB9 <2=>PD1
#define CAN1_TX_PORT_ID 0
#if (CAN1_TX_PORT_ID == 0)
#define CAN1_TX_PORT A
#define CAN1_TX_PIN  GPIO_PIN_12
#elif (CAN1_TX_PORT_ID == 1)
#define CAN1_TX_PORT B
#define CAN1_TX_PIN  GPIO_PIN_9
#elif (CAN1_TX_PORT_ID == 2)
#define CAN1_TX_PORT D
#define CAN1_TX_PIN  GPIO_PIN_1
#else
#error "Invalid CAN1_TX Pin Configuration!"
#endif

//   <e> Enable CAN Transmit Interrupt
#define CAN1_ENABLE_TX_IT    1
//     <o> CAN Transmit Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Transmit
#define CAN1_TX_IT_PRIORITY  2
//     <o> CAN Transmit Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Transmit
#define CAN1_TX_IT_SUB       3
//   </e>

//   <e> Enable CAN Receive FIFO0 Interrupt
#define CAN1_ENABLE_RX0_IT   1
//     <o> CAN Receive FIFO0 Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Receive FIFO0
#define CAN1_RX0_IT_PRIORITY 2
//     <o> CAN Receive FIFO0 Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Receive FIFO0
#define CAN1_RX0_IT_SUB      3
//   </e>

//   <e> Enable CAN Receive FIFO1 Interrupt
#define CAN1_ENABLE_RX1_IT   1
//     <o> CAN Receive FIFO1 Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Receive FIFO1
#define CAN1_RX1_IT_PRIORITY 2
//     <o> CAN Receive FIFO1 Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Receive FIFO1
#define CAN1_RX1_IT_SUB      3
//   </e>

//   <e> Enable CAN Stauts Change or Error (SCE) Interrupt
#define CAN1_ENABLE_SCE_IT   1
//     <o> CAN SCE Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Receive FIFO0
#define CAN1_SCE_IT_PRIORITY 2
//     <o> CAN SCE Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Receive FIFO0
#define CAN1_SCE_IT_SUB      3
//   </e>

// </e>

// <e> CAN2 (Controller Area Network 2)
#define CAN2_ENABLE          0

//   <o> CAN2_RX Pin <0=>PB5 <1=>PB12
#define CAN2_RX_PORT_ID      0
#if (CAN2_RX_PORT_ID == 0)
#define CAN2_RX_PORT B
#define CAN2_RX_PIN  GPIO_PIN_5
#elif (CAN2_RX_PORT_ID == 1)
#define CAN2_RX_PORT B
#define CAN2_RX_PIN  GPIO_PIN_12
#else
#error "Invalid CAN2_RX Pin Configuration!"
#endif

//   <o> CAN2_TX Pin <0=>PB6 <1=>PB13
#define CAN2_TX_PORT_ID 0
#if (CAN2_TX_PORT_ID == 0)
#define CAN2_TX_PORT B
#define CAN2_TX_PIN  GPIO_PIN_6
#elif (CAN2_TX_PORT_ID == 1)
#define CAN2_TX_PORT B
#define CAN2_TX_PIN  GPIO_PIN_13
#else
#error "Invalid CAN2_TX Pin Configuration!"
#endif

//   <e> Enable CAN Transmit Interrupt
#define CAN2_ENABLE_TX_IT    0
//     <o> CAN Transmit Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Transmit
#define CAN2_TX_IT_PRIORITY  2
//     <o> CAN Transmit Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Transmit
#define CAN2_TX_IT_SUB       3
//   </e>

//   <e> Enable CAN Receive FIFO0 Interrupt
#define CAN2_ENABLE_RX0_IT   0
//     <o> CAN Receive FIFO0 Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Receive FIFO0
#define CAN2_RX0_IT_PRIORITY 2
//     <o> CAN Receive FIFO0 Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Receive FIFO0
#define CAN2_RX0_IT_SUB      3
//   </e>

//   <e> Enable CAN Receive FIFO1 Interrupt
#define CAN2_ENABLE_RX1_IT   0
//     <o> CAN Receive FIFO1 Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Receive FIFO1
#define CAN2_RX1_IT_PRIORITY 2
//     <o> CAN Receive FIFO1 Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Receive FIFO1
#define CAN2_RX1_IT_SUB      3
//   </e>

//   <e> Enable CAN Stauts Change or Error (SCE) Interrupt
#define CAN2_ENABLE_SCE_IT   0
//     <o> CAN SCE Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Receive FIFO0
#define CAN2_SCE_IT_PRIORITY 2
//     <o> CAN SCE Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Receive FIFO0
#define CAN2_SCE_IT_SUB      3
//   </e>

// </e>

// <<< end of configuration section >>>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Enable and disable the clock of GPIO. */
#define _CSP_GPIO_PORT(x)           GPIO##x
#define CSP_GPIO_PORT(x)            _CSP_GPIO_PORT(x)
#define _CSP_GPIO_CLK_ENABLE(x)     __HAL_RCC_GPIO##x##_CLK_ENABLE()
#define CSP_GPIO_CLK_ENABLE(x)      _CSP_GPIO_CLK_ENABLE(x)

/* Pasting the DMA Channel. */
#define _CSP_DMA_CHANNEL(x, y)      DMA##x##_Channel##y
#define CSP_DMA_CHANNEL(x, y)       _CSP_DMA_CHANNEL(x, y)

/* Pasting the DMA Channel IRQn and IRQHandler. */
#define _CSP_DMA_CHANNEL(x, y)      DMA##x##_Channel##y
#define CSP_DMA_CHANNEL(x, y)       _CSP_DMA_CHANNEL(x, y)

#define _CSP_DMA_CHANNEL_IRQn(x, y) DMA##x##_Channel##y##_IRQn
#define CSP_DMA_CHANNEL_IRQn(x, y)  _CSP_DMA_CHANNEL_IRQn(x, y)

#define _CSP_DMA_CHANNEL_IRQ(x, y)  DMA##x##_Channel##y##_IRQHandler
#define CSP_DMA_CHANNEL_IRQ(x, y)   _CSP_DMA_CHANNEL_IRQ(x, y)

/* Set DMA Priority */
#define CSP_DMA_PRIORITY(x)         ((x) << DMA_CCR_PL_Pos)

/* Enable and disable the clock of DMA. */
#define _CSP_DMA_CLK_ENABLE(x)      __HAL_RCC_DMA##x##_CLK_ENABLE()
#define CSP_DMA_CLK_ENABLE(x)       _CSP_DMA_CLK_ENABLE(x)

/* CSP memory management functions. */
#define CSP_MALLOC                  malloc
#define CSP_FREE                    free
#define CSP_REALLOC                 realloc
#include <stdlib.h>

/* Devices Family header files.  */
#include "stm32f1xx_hal.h"

#if (USART1_ENABLE || USART2_ENABLE || USART3_ENABLE || UART4_ENABLE ||        \
     UART5_ENABLE)
#include "../UART_STM32F1xx.h"
#endif /* (USART1_ENABLE || USART2_ENABLE || USART3_ENABLE || UART4_ENABLE ||  \
          UART5_ENABLE) */

#if (I2C1_ENABLE || I2C2_ENABLE)
#include "../I2C_STM32F1xx.h"
#endif /* (I2C1_ENABLE || I2C2_ENABLE) */

#if (SPI1_ENABLE || SPI2_ENABLE || SPI3_ENABLE)
#include "../SPI_STM32F1xx.h"
#endif /* (SPI1_ENABLE || SPI2_ENABLE || SPI3_ENABLE) */

#if (CAN1_ENABLE || CAN2_ENABLE)
#include "../CAN_STM32F1xx.h"
#endif /* (CAN1_ENABLE || CAN2_ENABLE) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CSP_CONFIG_H */
