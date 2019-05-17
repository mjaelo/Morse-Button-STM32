/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <string.h>
#include "logo.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */



/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */
uint8_t stop = 0;
uint16_t val = 0;
char *results;// zapisujemy w tym morsowe litery
char *wyraz;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */

void spi_send(uint8_t byte) {
    HAL_SPI_Transmit(&hspi1, &byte, 1, HAL_MAX_DELAY);
    //HAL_SPI_Transmit(&hspi1, &byte, 1, HAL_MAX_DELAY);
}

void lcd_reset() {
    HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);
}

void lcd_command(uint8_t cmd) {
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET);
    spi_send(cmd);
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);
}

void lcd_data(const uint8_t *data, int size) {
    lcd_command(0x40 | 0x00);   //Zerowanie Y
    lcd_command(0x80 | 0x00);   //Zerowanie X
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET);
    for (int i = 0; i < size; i++)
    {   spi_send(data[i]);    }
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);
}
void lcd_znak(const uint8_t *data, int size) {

    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET);
    for (int i = 0; i < size; i++) {
        spi_send(data[i]);
    }
    HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);
}


void write(char st[])
 {
  uint16_t n = strlen(st);
  uint16_t x = 0;
     while(x<n)
     {
    	 uint8_t ch[6];
    	 for(int i = 0; i < 6; i++)
    	 {
    		 ch[i]= ASCII[ st[x]-0x20][i];
    	 }
    	 uint16_t s =sizeof(ch);
    	 lcd_znak(ch, s );
    	 x++;
     }
 }


char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}









//Sending
uint8_t DataToSend[40]; // array for date to send
uint8_t MessageCounter = 0; // how many messanges we send
uint8_t MessageLength = 0; //lenght of message
//Reciving
uint8_t ReceivedData[40]; // ara
uint8_t ReceivedDataFlag = 0; // Flaga informujaca o odebraniu danych
const char *letter = "**ETIANMSURWDKGOHVF?L?PJBXCYZQ??";//zeby tlumaczyc morsa
char temp[40];// temporary for sending morse


void frommorse(uint8_t receive[40],uint8_t send[40]){
	uint8_t let=1;
 for(int i=0;i<4;i++){

	 if(receive[i]==46){
		 let=let*2;
	 }

	 else if(receive[i]==45){
		 let=let*2+1;
	 }

	 else {
		 break;
	 }}
 char temp[2];
 temp[0]=letter[let];
 temp[1]='\0';
 strcpy(send, temp);

 }

void tomorse(char letter1,uint8_t  receive[40]){
	//char morse[40];
	memset(receive, 0, 40);

	if(letter1=='a'){
		sprintf(receive, ".-");
		}

	else if(letter1=='b'){
		sprintf(receive, "-...");
	}


	else if(letter1=='c'){
		sprintf(receive, "-.-.");
	}

	else if(letter1=='d'){
		sprintf(receive, "-..");
	}

	else if(letter1=='e'){
		sprintf(receive, ".");
	}

	else if(letter1=='f'){
		sprintf(receive, "..-.");
	}

	else if(letter1=='g'){
		sprintf(receive, "--.");
	}

	else if(letter1=='h'){
		sprintf(receive, "....");
	}

	else if(letter1=='i'){
		sprintf(receive, "..");
	}



	else if(letter1=='j'){
		sprintf(receive, ".---");
	}

	else if(letter1=='k'){
		sprintf(receive, "-.-");
	}

	else if(letter1=='l'){
		sprintf(receive, ".-..");
	}

	else if(letter1=='m'){
		sprintf(receive, "--");
	}

	else if(letter1=='n'){
		sprintf(receive, "-.");
	}

	else if(letter1=='o'){
		sprintf(receive, "---");
	}

	else if(letter1=='p'){
		sprintf(receive, ".--.");
	}

	else if(letter1=='q'){
		sprintf(receive, "--.-");
	}

	else if(letter1=='r'){
		sprintf(receive, ".-.");
	}

	else if(letter1=='s'){
		sprintf(receive, "...");
	}

	else if(letter1=='t'){
		sprintf(receive, "-");
	}

	else if(letter1=='u'){
		sprintf(receive, "..-");
	}

	else if(letter1=='v'){
		sprintf(receive, "...-");
	}

	else if(letter1=='w'){
		sprintf(receive, ".--");
	}

	else if(letter1=='x'){
		sprintf(receive, "-..-");
	}

	else if(letter1=='y'){
		sprintf(receive, "-.--");
	}

	else if(letter1=='z'){
		sprintf(receive, "--..");
	}






}












uint8_t x=0x00;uint8_t y=0x00;int b=0;
int reset=0;//reset ekranu, jesli wyswietla sie wynik
int space=0;//czy poprzednim znakiem by³a spacja

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
   	if(htim->Instance == TIM4)
   	{
    	if(HAL_GPIO_ReadPin(GPIOB,Joy_Button_Pin)== 1)
    	{
    		 if(stop==1)
    		{
        		results= concat("wynik to \"",wyraz);
    			results= concat(results,"\" ");
    			write(results);
    			results="";
    			wyraz="";
    			reset=1;
    			stop =0;
    		}
    		else
    		{

    			if(val > 0)
    			{
						b++;
					if(b>=14)    	{y+=1;b=0;x=0x00;}
    			else x+=6;

				if(val<4)space=0;

					if(val>4)
    					{
    					frommorse(results,results);
    					wyraz=concat(wyraz,results);
    					results="";
    					write(" ");

    					if(space==1)
						{wyraz=concat(wyraz," ");space=0;}
						else
						space =1;

    					if(val>8)
    					{stop=1;}

    					//... . -. -.. -. ..- -.. . ...
    					//...---...
    					}

    				else if(val>2)
    				{
    					write("-");
    					results =  concat(results,"-");
    				}
    				else
    				{
    					write(".");
    					results =  concat(results,".");
    				}
    				val=0;
    			}

    		}
    	}
    	else
    	{
    		val++;
    		if(reset==1)
    		    		{
    		    			x=0x00;y=0x00;
    						if(val>0)
    						{
    							lcd_data(morse, sizeof(morse));
    							reset=0;
    							val=0;
    						}
    		    		}
    		    		else
    		if(val > 0)
			{
    		if(val>12)val=0;
    		else if(val>8)
				{
    			write("X");
				}
			else if(val>4)
				{
				write(" ");
				}
				else if(val>2)
				{
					write("-");
				}
				else
				{
					write(".");
				}

			}
    		lcd_command(0x40 | y);   //Zerowanie Y
    		lcd_command(0x80 | x);   //Zerowanie X

    	}
   	}
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM4_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim4);

   HAL_GPIO_WritePin(BL_GPIO_Port, BL_Pin, GPIO_PIN_SET);

    lcd_reset();

   /* lcd_command(0x20 | 0x01);  //Komendy rozszerzone
    lcd_command(0x10 | 0x04);  //Bias System
    lcd_command(0x80 | 0x32);  //Ustawienie kontrastu
    lcd_command(0x20 | 0x00);  //Komendy zwykle
    lcd_command(0x08 | 0x04);  //Konfiguracja wyswietlacza
*/
    lcd_command(0x21);
    lcd_command(0x14);
    lcd_command(0x80 | 0x2f); //Ustawienie kontrastu
    lcd_command(0x20);
    lcd_command(0x0c);

    for(int j = 0; j < 504; j++) lcd_znak(0, 1);//reset ekranu
    lcd_command(0x40 | 0x00);   //Zerowanie Y
    lcd_command(0x80 | 0x00);   //Zerowanie X
    lcd_data(morse, sizeof(morse));
    lcd_command(0x40 | 0x00);   //Zerowanie Y
    lcd_command(0x80 | 0x00);   //Zerowanie X


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

    while (1) {


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 25000-1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 1000-1;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BL_GPIO_Port, BL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, CE_Pin|RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, DC_Pin|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : BL_Pin */
  GPIO_InitStruct.Pin = BL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CE_Pin RST_Pin */
  GPIO_InitStruct.Pin = CE_Pin|RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : DC_Pin PD12 PD13 PD14 
                           PD15 */
  GPIO_InitStruct.Pin = DC_Pin|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : Joy_Button_Pin */
  GPIO_InitStruct.Pin = Joy_Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Joy_Button_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
