/**
 * @file    SPI_STM32F1xx.c
 * @author  Deadline039
 * @brief   Chip Support Package of SPI on STM32F1xx
 * @version 3.3.3
 * @date    2024-10-22
 */

#include <CSP_Config.h>

#include "SPI_STM32F1xx.h"

/*****************************************************************************
 * @defgroup SPI1 Functions.
 * @{
 */

#if SPI1_ENABLE

SPI_HandleTypeDef spi1_handle = {
    .Instance = SPI1,
    .Init = {.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8,
             .Direction = SPI_DIRECTION_2LINES,
             .TIMode = SPI_TIMODE_DISABLE,
             .CRCCalculation = SPI_CRCCALCULATION_DISABLE,
             .CRCPolynomial = 7,
             .NSS = SPI_NSS_SOFT}};

#if SPI1_RX_DMA
static DMA_HandleTypeDef spi1_dmarx_handle = {
    .Instance = CSP_DMA_CHANNEL(SPI1_RX_DMA_NUMBER, SPI1_RX_DMA_CHANNEL),
    .Init = {.Direction = DMA_PERIPH_TO_MEMORY,
             .PeriphInc = DMA_PINC_DISABLE,
             .MemInc = DMA_MINC_ENABLE,
             .Mode = DMA_NORMAL,
             .Priority = SPI1_RX_DMA_PRIORITY}};
#endif /* SPI1_RX_DMA */

#if SPI1_TX_DMA
static DMA_HandleTypeDef spi1_dmatx_handle = {
    .Instance = CSP_DMA_CHANNEL(SPI1_TX_DMA_NUMBER, SPI1_TX_DMA_CHANNEL),
    .Init = {.Direction = DMA_MEMORY_TO_PERIPH,
             .PeriphInc = DMA_PINC_DISABLE,
             .MemInc = DMA_MINC_ENABLE,
             .Mode = DMA_NORMAL,
             .Priority = SPI1_TX_DMA_PRIORITY}};
#endif /* SPI1_TX_DMA */

/**
 * @brief SPI1 initialization.
 *
 * @param mode SPI mode. `SPI_MODE_MASTER` or `SPI_MODE_SLAVE`
 * @param clk_mode Clock mode.
 * @param data_size Data size. `SPI_DATASIZE_8BIT` or `SPI_DATASIZE_16BIT`
 * @param first_bit `SPI_FIRSTBIT_MSB` or `SPI_FIRSTBIT_LSB`
 * @return SPI init status.
 *  @retval - 0: `SPI_INIT_OK`:       Success.
 *  @retval - 1: `SPI_INIT_FAIL`:     SPI init failed.
 *  @retval - 2: `SPI_INIT_DMA_FAIL`: SPI DMA init failed.
 *  @retval - 3: `SPI_INITED`:        SPI is inited.
 */
uint8_t spi1_init(uint32_t mode, spi_clk_mode_t clk_mode, uint32_t data_size,
                  uint32_t first_bit) {

    if (HAL_SPI_GetState(&spi1_handle) != HAL_SPI_STATE_RESET) {
        return SPI_INITED;
    }

    GPIO_InitTypeDef gpio_init_struct = {.Mode = GPIO_MODE_AF_PP,
                                         .Pull = GPIO_PULLUP,
                                         .Speed = GPIO_SPEED_FREQ_HIGH};
    spi1_handle.Init.Mode = mode;
    spi1_handle.Init.CLKPhase = clk_mode & (1U << 0);
    spi1_handle.Init.CLKPolarity = clk_mode & (1U << 1);
    spi1_handle.Init.DataSize = data_size;
    spi1_handle.Init.FirstBit = first_bit;

    SPI1_AFIO_REMAP();

    CSP_GPIO_CLK_ENABLE(SPI1_SCK_PORT);
    gpio_init_struct.Pin = SPI1_SCK_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(SPI1_SCK_PORT), &gpio_init_struct);

#if SPI1_MISO_ENABLE
    CSP_GPIO_CLK_ENABLE(SPI1_MISO_PORT);
    gpio_init_struct.Pin = SPI1_MISO_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(SPI1_MISO_PORT), &gpio_init_struct);
#endif /* SPI1_MISO_ENABLE */

#if SPI1_MOSI_ENABLE
    CSP_GPIO_CLK_ENABLE(SPI1_MOSI_PORT);
    gpio_init_struct.Pin = SPI1_MOSI_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(SPI1_MOSI_PORT), &gpio_init_struct);
#endif /* SPI1_MOSI_ENABLE */

#if SPI1_NSS_ENABLE
    CSP_GPIO_CLK_ENABLE(SPI1_NSS_PORT);
    gpio_init_struct.Pin = SPI1_NSS_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(SPI1_NSS_PORT), &gpio_init_struct);
    if (mode == SPI_MODE_MASTER) {
        spi1_handle.Init.NSS = SPI_NSS_HARD_OUTPUT;
    } else if (mode == SPI_MODE_SLAVE) {
        spi1_handle.Init.NSS = SPI_NSS_HARD_INPUT;
    }
#endif /* SPI1_NSS_ENABLE */

    __HAL_RCC_SPI1_CLK_ENABLE();

#if SPI1_RX_DMA
    if (data_size == SPI_DATASIZE_8BIT) {
        spi1_dmarx_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        spi1_dmarx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    } else if (data_size == SPI_DATASIZE_16BIT) {
        spi1_dmarx_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
        spi1_dmarx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    }

    CSP_DMA_CLK_ENABLE(SPI1_RX_DMA_NUMBER);

    if (HAL_DMA_Init(&spi1_dmarx_handle) != HAL_OK) {
        return SPI_INIT_DMA_FAIL;
    }

    __HAL_LINKDMA(&spi1_handle, hdmarx, spi1_dmarx_handle);

    HAL_NVIC_SetPriority(
        CSP_DMA_CHANNEL_IRQn(SPI1_RX_DMA_NUMBER, SPI1_RX_DMA_CHANNEL),
        SPI1_RX_DMA_IT_PRIORITY, SPI1_RX_DMA_IT_SUB);
    HAL_NVIC_EnableIRQ(
        CSP_DMA_CHANNEL_IRQn(SPI1_RX_DMA_NUMBER, SPI1_RX_DMA_CHANNEL));

#endif /* SPI1_RX_DMA */

#if SPI1_TX_DMA
    if (data_size == SPI_DATASIZE_8BIT) {
        spi1_dmatx_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        spi1_dmatx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    } else if (data_size == SPI_DATASIZE_16BIT) {
        spi1_dmatx_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
        spi1_dmatx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    }

    CSP_DMA_CLK_ENABLE(SPI1_TX_DMA_NUMBER);

    if (HAL_DMA_Init(&spi1_dmatx_handle) != HAL_OK) {
        return SPI_INIT_DMA_FAIL;
    }

    __HAL_LINKDMA(&spi1_handle, hdmatx, spi1_dmatx_handle);

    HAL_NVIC_SetPriority(
        CSP_DMA_CHANNEL_IRQn(SPI1_TX_DMA_NUMBER, SPI1_TX_DMA_CHANNEL),
        SPI1_TX_DMA_IT_PRIORITY, SPI1_TX_DMA_IT_SUB);
    HAL_NVIC_EnableIRQ(
        CSP_DMA_CHANNEL_IRQn(SPI1_TX_DMA_NUMBER, SPI1_TX_DMA_CHANNEL));

#endif /* SPI1_TX_DMA */

#if SPI1_IT_ENABLE
    HAL_NVIC_SetPriority(SPI1_IRQn, SPI1_IT_PRIORITY, SPI1_IT_SUB);
    HAL_NVIC_EnableIRQ(SPI1_IRQn);
#endif /* SPI1_IT_ENABLE */

    if (HAL_SPI_Init(&spi1_handle) != HAL_OK) {
        return SPI_INIT_FAIL;
    }

    return SPI_INIT_OK;
}

#if SPI1_IT_ENABLE

/**
 * @brief SPI1 ISR
 *
 */
void SPI1_IRQHandler(void) {
    HAL_SPI_IRQHandler(&spi1_handle);
}

#endif /* SPI1_IT_ENABLE */

#if SPI1_RX_DMA

/**
 * @brief SPI1 RX DMA ISR
 *
 */
void SPI1_RX_DMA_IRQHandler(void) {
    HAL_DMA_IRQHandler(&spi1_dmarx_handle);
}

#endif /* SPI1_RX_DMA */

#if SPI1_TX_DMA

/**
 * @brief SPI1 TX DMA ISR
 *
 */
void SPI1_TX_DMA_IRQHandler(void) {
    HAL_DMA_IRQHandler(&spi1_dmatx_handle);
}

#endif /* SPI1_TX_DMA */

/**
 * @brief SPI1 deinitialization.
 *
 * @return SPI deinit status.
 *  @retval - 0: `SPI_DEINIT_OK`:       Success.
 *  @retval - 1: `SPI_DEINIT_FAIL`:     SPI deinit failed.
 *  @retval - 2: `SPI_DEINIT_DMA_FAIL`: SPI DMA deinit failed.
 *  @retval - 3: `SPI_NO_INIT`:         SPI is not init.
 */
uint8_t spi1_deinit(void) {
    if (HAL_SPI_GetState(&spi1_handle) == HAL_SPI_STATE_RESET) {
        return SPI_NO_INIT;
    }

    __HAL_RCC_SPI1_CLK_DISABLE();

    HAL_GPIO_DeInit(CSP_GPIO_PORT(SPI1_SCK_PORT), SPI1_SCK_PIN);

#if SPI1_MISO_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(SPI1_MISO_PORT), SPI1_MOSI_PIN);
#endif /* SPI1_MISO_ENABLE */

#if SPI1_MOSI_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(SPI1_MOSI_PORT), SPI1_MOSI_PIN);
#endif /* SPI1_MOSI_ENABLE */

#if SPI1_NSS_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(SPI1_NSS_PORT), SPI1_NSS_PIN);
#endif /* SPI1_NSS_ENABLE */

#if SPI1_RX_DMA
    HAL_DMA_Abort(&spi1_dmarx_handle);

    if (HAL_DMA_DeInit(&spi1_dmarx_handle) != HAL_OK) {
        return SPI_DEINIT_DMA_FAIL;
    }

    HAL_NVIC_DisableIRQ(
        CSP_DMA_CHANNEL_IRQn(SPI1_RX_DMA_NUMBER, SPI1_RX_DMA_CHANNEL));
    spi1_handle.hdmarx = NULL;
#endif /* SPI1_RX_DMA */

#if SPI1_TX_DMA
    if (HAL_DMA_DeInit(&spi1_dmatx_handle) != HAL_OK) {
        return SPI_DEINIT_DMA_FAIL;
    }

    HAL_NVIC_DisableIRQ(
        CSP_DMA_CHANNEL_IRQn(SPI1_RX_DMA_NUMBER, SPI1_RX_DMA_CHANNEL));
    spi1_handle.hdmatx = NULL;
#endif /* SPI1_TX_DMA */

#if SPI1_IT_ENABLE
    HAL_NVIC_DisableIRQ(SPI1_IRQn);
#endif /* SPI1_IT_ENABLE */

    if (HAL_SPI_DeInit(&spi1_handle) != HAL_OK) {
        return SPI_DEINIT_FAIL;
    }

    return SPI_DEINIT_OK;
}

#endif /* SPI1_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup SPI2 Functions.
 * @{
 */

#if SPI2_ENABLE

SPI_HandleTypeDef spi2_handle = {
    .Instance = SPI2,
    .Init = {.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8,
             .Direction = SPI_DIRECTION_2LINES,
             .TIMode = SPI_TIMODE_DISABLE,
             .CRCCalculation = SPI_CRCCALCULATION_DISABLE,
             .CRCPolynomial = 7,
             .NSS = SPI_NSS_SOFT}};

#if SPI2_RX_DMA
static DMA_HandleTypeDef spi2_dmarx_handle = {
    .Instance = CSP_DMA_CHANNEL(SPI2_RX_DMA_NUMBER, SPI2_RX_DMA_CHANNEL),
    .Init = {.Direction = DMA_PERIPH_TO_MEMORY,
             .PeriphInc = DMA_PINC_DISABLE,
             .MemInc = DMA_MINC_ENABLE,
             .Mode = DMA_NORMAL,
             .Priority = SPI2_RX_DMA_PRIORITY}};
#endif /* SPI2_RX_DMA */

#if SPI2_TX_DMA
static DMA_HandleTypeDef spi2_dmatx_handle = {
    .Instance = CSP_DMA_CHANNEL(SPI2_TX_DMA_NUMBER, SPI2_TX_DMA_CHANNEL),
    .Init = {.Direction = DMA_MEMORY_TO_PERIPH,
             .PeriphInc = DMA_PINC_DISABLE,
             .MemInc = DMA_MINC_ENABLE,
             .Mode = DMA_NORMAL,
             .Priority = SPI2_TX_DMA_PRIORITY}};
#endif /* SPI2_TX_DMA */

/**
 * @brief SPI2 initialization.
 *
 * @param mode SPI mode. `SPI_MODE_MASTER` or `SPI_MODE_SLAVE`
 * @param clk_mode Clock mode.
 * @param data_size Data size. `SPI_DATASIZE_8BIT` or `SPI_DATASIZE_16BIT`
 * @param first_bit `SPI_FIRSTBIT_MSB` or `SPI_FIRSTBIT_LSB`
 * @return SPI init status.
 *  @retval - 0: `SPI_INIT_OK`:       Success.
 *  @retval - 1: `SPI_INIT_FAIL`:     SPI init failed.
 *  @retval - 2: `SPI_INIT_DMA_FAIL`: SPI DMA init failed.
 *  @retval - 3: `SPI_INITED`:        SPI is inited.
 */
uint8_t spi2_init(uint32_t mode, spi_clk_mode_t clk_mode, uint32_t data_size,
                  uint32_t first_bit) {

    if (HAL_SPI_GetState(&spi2_handle) != HAL_SPI_STATE_RESET) {
        return SPI_INITED;
    }

    GPIO_InitTypeDef gpio_init_struct = {.Mode = GPIO_MODE_AF_PP,
                                         .Pull = GPIO_PULLUP,
                                         .Speed = GPIO_SPEED_FREQ_HIGH};
    spi2_handle.Init.Mode = mode;
    spi2_handle.Init.CLKPhase = clk_mode & (1U << 0);
    spi2_handle.Init.CLKPolarity = clk_mode & (1U << 1);
    spi2_handle.Init.DataSize = data_size;
    spi2_handle.Init.FirstBit = first_bit;

    CSP_GPIO_CLK_ENABLE(SPI2_SCK_PORT);
    gpio_init_struct.Pin = SPI2_SCK_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(SPI2_SCK_PORT), &gpio_init_struct);

#if SPI2_MISO_ENABLE
    CSP_GPIO_CLK_ENABLE(SPI2_MISO_PORT);
    gpio_init_struct.Pin = SPI2_MISO_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(SPI2_MISO_PORT), &gpio_init_struct);
#endif /* SPI2_MISO_ENABLE */

#if SPI2_MOSI_ENABLE
    CSP_GPIO_CLK_ENABLE(SPI2_MOSI_PORT);
    gpio_init_struct.Pin = SPI2_MOSI_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(SPI2_MOSI_PORT), &gpio_init_struct);
#endif /* SPI2_MOSI_ENABLE */

#if SPI2_NSS_ENABLE
    CSP_GPIO_CLK_ENABLE(SPI2_NSS_PORT);
    gpio_init_struct.Pin = SPI2_NSS_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(SPI2_NSS_PORT), &gpio_init_struct);
    if (mode == SPI_MODE_MASTER) {
        spi2_handle.Init.NSS = SPI_NSS_HARD_OUTPUT;
    } else if (mode == SPI_MODE_SLAVE) {
        spi2_handle.Init.NSS = SPI_NSS_HARD_INPUT;
    }
#endif /* SPI2_NSS_ENABLE */

    __HAL_RCC_SPI2_CLK_ENABLE();

#if SPI2_RX_DMA
    if (data_size == SPI_DATASIZE_8BIT) {
        spi2_dmarx_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        spi2_dmarx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    } else if (data_size == SPI_DATASIZE_16BIT) {
        spi2_dmarx_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
        spi2_dmarx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    }

    CSP_DMA_CLK_ENABLE(SPI2_RX_DMA_NUMBER);

    if (HAL_DMA_Init(&spi2_dmarx_handle) != HAL_OK) {
        return SPI_INIT_DMA_FAIL;
    }

    __HAL_LINKDMA(&spi2_handle, hdmarx, spi2_dmarx_handle);

    HAL_NVIC_SetPriority(
        CSP_DMA_CHANNEL_IRQn(SPI2_RX_DMA_NUMBER, SPI2_RX_DMA_CHANNEL),
        SPI2_RX_DMA_IT_PRIORITY, SPI2_RX_DMA_IT_SUB);
    HAL_NVIC_EnableIRQ(
        CSP_DMA_CHANNEL_IRQn(SPI2_RX_DMA_NUMBER, SPI2_RX_DMA_CHANNEL));

#endif /* SPI2_RX_DMA */

#if SPI2_TX_DMA
    if (data_size == SPI_DATASIZE_8BIT) {
        spi2_dmatx_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        spi2_dmatx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    } else if (data_size == SPI_DATASIZE_16BIT) {
        spi2_dmatx_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
        spi2_dmatx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    }

    CSP_DMA_CLK_ENABLE(SPI2_TX_DMA_NUMBER);

    if (HAL_DMA_Init(&spi2_dmatx_handle) != HAL_OK) {
        return SPI_INIT_DMA_FAIL;
    }

    __HAL_LINKDMA(&spi2_handle, hdmatx, spi2_dmatx_handle);

    HAL_NVIC_SetPriority(
        CSP_DMA_CHANNEL_IRQn(SPI2_TX_DMA_NUMBER, SPI2_TX_DMA_CHANNEL),
        SPI2_TX_DMA_IT_PRIORITY, SPI2_TX_DMA_IT_SUB);
    HAL_NVIC_EnableIRQ(
        CSP_DMA_CHANNEL_IRQn(SPI2_TX_DMA_NUMBER, SPI2_TX_DMA_CHANNEL));

#endif /* SPI2_TX_DMA */

#if SPI2_IT_ENABLE
    HAL_NVIC_SetPriority(SPI2_IRQn, SPI2_IT_PRIORITY, SPI2_IT_SUB);
    HAL_NVIC_EnableIRQ(SPI2_IRQn);
#endif /* SPI2_IT_ENABLE */

    if (HAL_SPI_Init(&spi2_handle) != HAL_OK) {
        return SPI_INIT_FAIL;
    }

    return SPI_INIT_OK;
}

#if SPI2_IT_ENABLE

/**
 * @brief SPI2 ISR
 *
 */
void SPI2_IRQHandler(void) {
    HAL_SPI_IRQHandler(&spi2_handle);
}

#endif /* SPI2_IT_ENABLE */

#if SPI2_RX_DMA

/**
 * @brief SPI2 RX DMA ISR
 *
 */
void SPI2_RX_DMA_IRQHandler(void) {
    HAL_DMA_IRQHandler(&spi2_dmarx_handle);
}

#endif /* SPI2_RX_DMA */

#if SPI2_TX_DMA

/**
 * @brief SPI2 TX DMA ISR
 *
 */
void SPI2_TX_DMA_IRQHandler(void) {
    HAL_DMA_IRQHandler(&spi2_dmatx_handle);
}

#endif /* SPI2_TX_DMA */

/**
 * @brief SPI2 deinitialization.
 *
 * @return SPI deinit status.
 *  @retval - 0: `SPI_DEINIT_OK`:       Success.
 *  @retval - 1: `SPI_DEINIT_FAIL`:     SPI deinit failed.
 *  @retval - 2: `SPI_DEINIT_DMA_FAIL`: SPI DMA deinit failed.
 *  @retval - 3: `SPI_NO_INIT`:         SPI is not init.
 */
uint8_t spi2_deinit(void) {
    if (HAL_SPI_GetState(&spi2_handle) == HAL_SPI_STATE_RESET) {
        return SPI_NO_INIT;
    }

    __HAL_RCC_SPI2_CLK_DISABLE();

    HAL_GPIO_DeInit(CSP_GPIO_PORT(SPI2_SCK_PORT), SPI2_SCK_PIN);

#if SPI2_MISO_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(SPI2_MISO_PORT), SPI2_MOSI_PIN);
#endif /* SPI2_MISO_ENABLE */

#if SPI2_MOSI_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(SPI2_MOSI_PORT), SPI2_MOSI_PIN);
#endif /* SPI2_MOSI_ENABLE */

#if SPI2_NSS_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(SPI2_NSS_PORT), SPI2_NSS_PIN);
#endif /* SPI2_NSS_ENABLE */

#if SPI2_RX_DMA
    HAL_DMA_Abort(&spi2_dmarx_handle);

    if (HAL_DMA_DeInit(&spi2_dmarx_handle) != HAL_OK) {
        return SPI_DEINIT_DMA_FAIL;
    }

    HAL_NVIC_DisableIRQ(
        CSP_DMA_CHANNEL_IRQn(SPI2_RX_DMA_NUMBER, SPI2_RX_DMA_CHANNEL));
    spi2_handle.hdmarx = NULL;
#endif /* SPI2_RX_DMA */

#if SPI2_TX_DMA
    if (HAL_DMA_DeInit(&spi2_dmatx_handle) != HAL_OK) {
        return SPI_DEINIT_DMA_FAIL;
    }

    HAL_NVIC_DisableIRQ(
        CSP_DMA_CHANNEL_IRQn(SPI2_RX_DMA_NUMBER, SPI2_RX_DMA_CHANNEL));
    spi2_handle.hdmatx = NULL;
#endif /* SPI2_TX_DMA */

#if SPI2_IT_ENABLE
    HAL_NVIC_DisableIRQ(SPI2_IRQn);
#endif /* SPI2_IT_ENABLE */

    if (HAL_SPI_DeInit(&spi2_handle) != HAL_OK) {
        return SPI_DEINIT_FAIL;
    }

    return SPI_DEINIT_OK;
}

#endif /* SPI2_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup SPI3 Functions.
 * @{
 */

#if SPI3_ENABLE

SPI_HandleTypeDef spi3_handle = {
    .Instance = SPI3,
    .Init = {.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8,
             .Direction = SPI_DIRECTION_2LINES,
             .TIMode = SPI_TIMODE_DISABLE,
             .CRCCalculation = SPI_CRCCALCULATION_DISABLE,
             .CRCPolynomial = 7,
             .NSS = SPI_NSS_SOFT}};

#if SPI3_RX_DMA
static DMA_HandleTypeDef spi3_dmarx_handle = {
    .Instance = CSP_DMA_CHANNEL(SPI3_RX_DMA_NUMBER, SPI3_RX_DMA_CHANNEL),
    .Init = {.Direction = DMA_PERIPH_TO_MEMORY,
             .PeriphInc = DMA_PINC_DISABLE,
             .MemInc = DMA_MINC_ENABLE,
             .Mode = DMA_NORMAL,
             .Priority = SPI3_RX_DMA_PRIORITY}};
#endif /* SPI3_RX_DMA */

#if SPI3_TX_DMA
static DMA_HandleTypeDef spi3_dmatx_handle = {
    .Instance = CSP_DMA_CHANNEL(SPI3_TX_DMA_NUMBER, SPI3_TX_DMA_CHANNEL),
    .Init = {.Direction = DMA_MEMORY_TO_PERIPH,
             .PeriphInc = DMA_PINC_DISABLE,
             .MemInc = DMA_MINC_ENABLE,
             .Mode = DMA_NORMAL,
             .Priority = SPI3_TX_DMA_PRIORITY}};
#endif /* SPI3_TX_DMA */

/**
 * @brief SPI3 initialization.
 *
 * @param mode SPI mode. `SPI_MODE_MASTER` or `SPI_MODE_SLAVE`
 * @param clk_mode Clock mode.
 * @param data_size Data size. `SPI_DATASIZE_8BIT` or `SPI_DATASIZE_16BIT`
 * @param first_bit `SPI_FIRSTBIT_MSB` or `SPI_FIRSTBIT_LSB`
 * @return SPI init status.
 *  @retval - 0: `SPI_INIT_OK`:       Success.
 *  @retval - 1: `SPI_INIT_FAIL`:     SPI init failed.
 *  @retval - 2: `SPI_INIT_DMA_FAIL`: SPI DMA init failed.
 *  @retval - 3: `SPI_INITED`:        SPI is inited.
 */
uint8_t spi3_init(uint32_t mode, spi_clk_mode_t clk_mode, uint32_t data_size,
                  uint32_t first_bit) {

    if (HAL_SPI_GetState(&spi3_handle) != HAL_SPI_STATE_RESET) {
        return SPI_INITED;
    }

    GPIO_InitTypeDef gpio_init_struct = {.Mode = GPIO_MODE_AF_PP,
                                         .Pull = GPIO_PULLUP,
                                         .Speed = GPIO_SPEED_FREQ_HIGH};
    spi3_handle.Init.Mode = mode;
    spi3_handle.Init.CLKPhase = clk_mode & (1U << 0);
    spi3_handle.Init.CLKPolarity = clk_mode & (1U << 1);
    spi3_handle.Init.DataSize = data_size;
    spi3_handle.Init.FirstBit = first_bit;

    SPI3_AFIO_REMAP();

    CSP_GPIO_CLK_ENABLE(SPI3_SCK_PORT);
    gpio_init_struct.Pin = SPI3_SCK_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(SPI3_SCK_PORT), &gpio_init_struct);

#if SPI3_MISO_ENABLE
    CSP_GPIO_CLK_ENABLE(SPI3_MISO_PORT);
    gpio_init_struct.Pin = SPI3_MISO_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(SPI3_MISO_PORT), &gpio_init_struct);
#endif /* SPI3_MISO_ENABLE */

#if SPI3_MOSI_ENABLE
    CSP_GPIO_CLK_ENABLE(SPI3_MOSI_PORT);
    gpio_init_struct.Pin = SPI3_MOSI_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(SPI3_MOSI_PORT), &gpio_init_struct);
#endif /* SPI3_MOSI_ENABLE */

#if SPI3_NSS_ENABLE
    CSP_GPIO_CLK_ENABLE(SPI3_NSS_PORT);
    gpio_init_struct.Pin = SPI3_NSS_PIN;
    HAL_GPIO_Init(CSP_GPIO_PORT(SPI3_NSS_PORT), &gpio_init_struct);
    if (mode == SPI_MODE_MASTER) {
        spi3_handle.Init.NSS = SPI_NSS_HARD_OUTPUT;
    } else if (mode == SPI_MODE_SLAVE) {
        spi3_handle.Init.NSS = SPI_NSS_HARD_INPUT;
    }
#endif /* SPI3_NSS_ENABLE */

    __HAL_RCC_SPI3_CLK_ENABLE();

#if SPI3_RX_DMA
    if (data_size == SPI_DATASIZE_8BIT) {
        spi3_dmarx_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        spi3_dmarx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    } else if (data_size == SPI_DATASIZE_16BIT) {
        spi3_dmarx_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
        spi3_dmarx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    }

    CSP_DMA_CLK_ENABLE(SPI3_RX_DMA_NUMBER);

    if (HAL_DMA_Init(&spi3_dmarx_handle) != HAL_OK) {
        return SPI_INIT_DMA_FAIL;
    }

    __HAL_LINKDMA(&spi3_handle, hdmarx, spi3_dmarx_handle);

    HAL_NVIC_SetPriority(
        CSP_DMA_CHANNEL_IRQn(SPI3_RX_DMA_NUMBER, SPI3_RX_DMA_CHANNEL),
        SPI3_RX_DMA_IT_PRIORITY, SPI3_RX_DMA_IT_SUB);
    HAL_NVIC_EnableIRQ(
        CSP_DMA_CHANNEL_IRQn(SPI3_RX_DMA_NUMBER, SPI3_RX_DMA_CHANNEL));

#endif /* SPI3_RX_DMA */

#if SPI3_TX_DMA
    if (data_size == SPI_DATASIZE_8BIT) {
        spi3_dmatx_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        spi3_dmatx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    } else if (data_size == SPI_DATASIZE_16BIT) {
        spi3_dmatx_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
        spi3_dmatx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    }

    CSP_DMA_CLK_ENABLE(SPI3_TX_DMA_NUMBER);

    if (HAL_DMA_Init(&spi3_dmatx_handle) != HAL_OK) {
        return SPI_INIT_DMA_FAIL;
    }

    __HAL_LINKDMA(&spi3_handle, hdmatx, spi3_dmatx_handle);

    HAL_NVIC_SetPriority(
        CSP_DMA_CHANNEL_IRQn(SPI3_TX_DMA_NUMBER, SPI3_TX_DMA_CHANNEL),
        SPI3_TX_DMA_IT_PRIORITY, SPI3_TX_DMA_IT_SUB);
    HAL_NVIC_EnableIRQ(
        CSP_DMA_CHANNEL_IRQn(SPI3_TX_DMA_NUMBER, SPI3_TX_DMA_CHANNEL));

#endif /* SPI3_TX_DMA */

#if SPI3_IT_ENABLE
    HAL_NVIC_SetPriority(SPI3_IRQn, SPI3_IT_PRIORITY, SPI3_IT_SUB);
    HAL_NVIC_EnableIRQ(SPI3_IRQn);
#endif /* SPI3_IT_ENABLE */

    if (HAL_SPI_Init(&spi3_handle) != HAL_OK) {
        return SPI_INIT_FAIL;
    }

    return SPI_INIT_OK;
}

#if SPI3_IT_ENABLE

/**
 * @brief SPI3 ISR
 *
 */
void SPI3_IRQHandler(void) {
    HAL_SPI_IRQHandler(&spi3_handle);
}

#endif /* SPI3_IT_ENABLE */

#if SPI3_RX_DMA

/**
 * @brief SPI3 RX DMA ISR
 *
 */
void SPI3_RX_DMA_IRQHandler(void) {
    HAL_DMA_IRQHandler(&spi3_dmarx_handle);
}

#endif /* SPI3_RX_DMA */

#if SPI3_TX_DMA

/**
 * @brief SPI3 TX DMA ISR
 *
 */
void SPI3_TX_DMA_IRQHandler(void) {
    HAL_DMA_IRQHandler(&spi3_dmatx_handle);
}

#endif /* SPI3_TX_DMA */

/**
 * @brief SPI3 deinitialization.
 *
 * @return SPI deinit status.
 *  @retval - 0: `SPI_DEINIT_OK`:       Success.
 *  @retval - 1: `SPI_DEINIT_FAIL`:     SPI deinit failed.
 *  @retval - 2: `SPI_DEINIT_DMA_FAIL`: SPI DMA deinit failed.
 *  @retval - 3: `SPI_NO_INIT`:         SPI is not init.
 */
uint8_t spi3_deinit(void) {
    if (HAL_SPI_GetState(&spi3_handle) == HAL_SPI_STATE_RESET) {
        return SPI_NO_INIT;
    }

    __HAL_RCC_SPI3_CLK_DISABLE();

    HAL_GPIO_DeInit(CSP_GPIO_PORT(SPI3_SCK_PORT), SPI3_SCK_PIN);

#if SPI3_MISO_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(SPI3_MISO_PORT), SPI3_MOSI_PIN);
#endif /* SPI3_MISO_ENABLE */

#if SPI3_MOSI_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(SPI3_MOSI_PORT), SPI3_MOSI_PIN);
#endif /* SPI3_MOSI_ENABLE */

#if SPI3_NSS_ENABLE
    HAL_GPIO_DeInit(CSP_GPIO_PORT(SPI3_NSS_PORT), SPI3_NSS_PIN);
#endif /* SPI3_NSS_ENABLE */

#if SPI3_RX_DMA
    HAL_DMA_Abort(&spi3_dmarx_handle);

    if (HAL_DMA_DeInit(&spi3_dmarx_handle) != HAL_OK) {
        return SPI_DEINIT_DMA_FAIL;
    }

    HAL_NVIC_DisableIRQ(
        CSP_DMA_CHANNEL_IRQn(SPI3_RX_DMA_NUMBER, SPI3_RX_DMA_CHANNEL));
    spi3_handle.hdmarx = NULL;
#endif /* SPI3_RX_DMA */

#if SPI3_TX_DMA
    if (HAL_DMA_DeInit(&spi3_dmatx_handle) != HAL_OK) {
        return SPI_DEINIT_DMA_FAIL;
    }

    HAL_NVIC_DisableIRQ(
        CSP_DMA_CHANNEL_IRQn(SPI3_RX_DMA_NUMBER, SPI3_RX_DMA_CHANNEL));
    spi3_handle.hdmatx = NULL;
#endif /* SPI3_TX_DMA */

#if SPI3_IT_ENABLE
    HAL_NVIC_DisableIRQ(SPI3_IRQn);
#endif /* SPI3_IT_ENABLE */

    if (HAL_SPI_DeInit(&spi3_handle) != HAL_OK) {
        return SPI_DEINIT_FAIL;
    }

    return SPI_DEINIT_OK;
}

#endif /* SPI3_ENABLE */

/**
 * @}
 */

/*****************************************************************************
 * @defgroup Public SPI Functions.
 * @{
 */

/**
 * @brief SPI exchange one byte data.
 *
 * @param hspi The handle of SPI
 * @param byte The byte to transmit.
 * @return Received byte.
 */
uint8_t spi_rw_one_byte(SPI_HandleTypeDef *hspi, uint8_t byte) {
    if (HAL_SPI_GetState(hspi) != HAL_SPI_STATE_READY) {
        return 0;
    }

    uint8_t rx_data;
    HAL_SPI_TransmitReceive(hspi, &byte, &rx_data, 1, SPI_RW_TIMEOUT);

    return rx_data;
}

/**
 * @brief SPI exchange two byte data.
 *
 * @param hspi The handle of SPI
 * @param tx_dtata The data to transmit.
 * @return Received data.
 */
uint16_t spi_rw_two_byte(SPI_HandleTypeDef *hspi, uint16_t tx_data) {
    if (HAL_SPI_GetState(hspi) != HAL_SPI_STATE_READY) {
        return 0;
    }

    uint16_t rx_data;
    HAL_SPI_TransmitReceive(hspi, (uint8_t *)&tx_data, (uint8_t *)&rx_data, 2,
                            SPI_RW_TIMEOUT);

    return rx_data;
}

/**
 * @brief Change the speed of SPI.
 *
 * @param hspi The handle of SPI
 * @param speed This parameter can ref `SPI_BaudRate_Prescaler`
 *  @retval - 0: Success.
 *  @retval - 1: SPI is busy now.
 *  @retval - 2: Parameter invalid.
 * @note Default speed is `SPI_BAUDRATEPRESCALER_8`. Only valid in master mode.
 */
uint8_t spi_change_speed(SPI_HandleTypeDef *hspi, uint8_t speed) {
    HAL_SPI_StateTypeDef state = HAL_SPI_GetState(hspi);

    if (state == HAL_SPI_STATE_RESET) {
        hspi->Init.BaudRatePrescaler = speed;
        return 0;
    }

    if (state != HAL_SPI_STATE_READY) {
        return 1;
    }

    if (!IS_SPI_BAUDRATE_PRESCALER(speed)) {
        return 2;
    }

    __HAL_SPI_DISABLE(hspi);

    /* Clear Bit[5:3] to set the rate */
    hspi->Instance->CR1 &= ~((0x7) << 3U);
    /* Set the speed */
    hspi->Instance->CR1 |= speed;

    return 0;
}

/**
 * @}
 */
