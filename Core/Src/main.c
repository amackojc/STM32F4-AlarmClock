/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "rtc.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd1602.h"
#include <stdio.h>
#include <stdbool.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

struct time clock, alarm, d;
struct lcd_disp disp;

uint8_t refresh_lcd = 1;
uint8_t counter = 0;
uint8_t alarm_start = 1;
bool state = true;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void set_clock(uint8_t hour, uint8_t minute, uint8_t second, uint8_t day, uint8_t month, uint8_t year){
	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef DateToUpdate = {0};
	sTime.Hours = hour;
	sTime.Minutes = minute;
	sTime.Seconds = second;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;

	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}

	DateToUpdate.WeekDay = RTC_WEEKDAY_SATURDAY;
	if (month == 1){
		DateToUpdate.Month = RTC_MONTH_JANUARY;
	}
	else if (month == 2){
		DateToUpdate.Month = RTC_MONTH_FEBRUARY;
	}
	else if (month == 3){
		DateToUpdate.Month = RTC_MONTH_MARCH;
	}
	else if (month == 4){
		DateToUpdate.Month = RTC_MONTH_APRIL;
	}
	else if (month == 5){
		DateToUpdate.Month = RTC_MONTH_MAY;
	}
	else if (month == 6){
		DateToUpdate.Month = RTC_MONTH_JUNE;
	}
	else if (month == 7){
		DateToUpdate.Month = RTC_MONTH_JULY;
	}
	else if (month == 8){
		DateToUpdate.Month = RTC_MONTH_AUGUST;
	}
	else if (month == 9){
		DateToUpdate.Month = RTC_MONTH_SEPTEMBER;
	}
	else if (month == 10){
		DateToUpdate.Month = RTC_MONTH_OCTOBER;
	}
	else if (month == 11){
		DateToUpdate.Month = RTC_MONTH_NOVEMBER;
	}
	else if (month == 12){
		DateToUpdate.Month = RTC_MONTH_DECEMBER;
	}

	if (day == 1 || day == 8 || day == 15 || day == 22 || day == 29){

		DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
	}
	else if (day == 2 || day == 9 || day == 16 || day == 23 || day == 30){
		DateToUpdate.WeekDay = RTC_WEEKDAY_TUESDAY;
	}
	else if (day == 3 || day == 10 || day == 17 || day == 24){
		DateToUpdate.WeekDay = RTC_WEEKDAY_WEDNESDAY;
	}
	else if (day == 4 || day == 11 || day == 18 || day == 25){
		DateToUpdate.WeekDay = RTC_WEEKDAY_THURSDAY;
	}
	else if (day == 5 || day == 12 || day == 19 || day == 26){
		DateToUpdate.WeekDay = RTC_WEEKDAY_FRIDAY;
	}
	else if (day == 6 || day == 13 || day == 20 || day == 27){
		DateToUpdate.WeekDay = RTC_WEEKDAY_SATURDAY;
	}
	else if (day == 7 || day == 14 || day == 21 || day == 28){
		DateToUpdate.WeekDay = RTC_WEEKDAY_SUNDAY;
	}

	DateToUpdate.Date = day;
	DateToUpdate.Year = year;

	if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}

}
void set_alarm(uint8_t hour, uint8_t minute, uint8_t second, uint8_t day){
	RTC_AlarmTypeDef sAlarm = {0};

	sAlarm.AlarmTime.Hours = hour;
	sAlarm.AlarmTime.Minutes = minute;
	sAlarm.AlarmTime.Seconds = second;
	sAlarm.AlarmTime.SubSeconds = 0;
	sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
	sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
	sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
	sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
	sAlarm.AlarmDateWeekDay = day;
	sAlarm.Alarm = RTC_ALARM_A;
	if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}

}
void get_time(void){
	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};

	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	sprintf((char*)disp.f_line, "%02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
	sprintf((char*)disp.s_line, "%02d:%02d:%d", sDate.Date, sDate.Month, 2020 + sDate.Year);
}
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
  MX_RTC_Init();
  MX_TIM1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  lcd_init(&disp);
  lcd_clear(&disp);
  disp.addr = (0x27 << 1);
  disp.bl = true;
  HAL_GPIO_WritePin (R1_PORT, R1_PIN, GPIO_PIN_SET);  //Pull the R1 low
  HAL_GPIO_WritePin (R2_PORT, R2_PIN, GPIO_PIN_SET);  // Pull the R2 High
  HAL_GPIO_WritePin (R3_PORT, R3_PIN, GPIO_PIN_SET);  // Pull the R3 High
  HAL_GPIO_WritePin (R4_PORT, R4_PIN, GPIO_PIN_RESET);  // Pull the R4 High
  clock.days = 1;
  clock.months = 1;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  while (counter < 2){
	  if (refresh_lcd == 1){
		  sprintf((char*)disp.f_line, "%02d:%02d:%02d Godzina", clock.hours, clock.minutes, clock.seconds);
		  sprintf((char*)disp.s_line, "%02d-%02d-%d  Data", clock.days, clock.months, 2020 + clock.years);
		  lcd_display(&disp);
		  refresh_lcd = 0;
	  }
  }

  while (counter < 4){
	  if (refresh_lcd == 1){
		  alarm.hours = clock.hours + d.hours;
		  alarm.minutes = clock.minutes + d.minutes;
		  alarm.seconds = clock.seconds + d.seconds;
		  alarm.days = clock.days + d.days;
		  alarm.months = clock.months + d.months;
		  alarm.years = clock.years + d.years;
		  sprintf((char*)disp.f_line, "%02d:%02d:%02d   Ustaw", alarm.hours, alarm.minutes, alarm.seconds);
		  sprintf((char*)disp.s_line, "%02d-%02d-%d alarm", alarm.days, alarm.months, 2020 + alarm.years);
		  lcd_display(&disp);
		  refresh_lcd = 0;
	  }
  }
  set_clock(clock.hours, clock.minutes, clock.seconds, clock.days, clock.months, clock.years);
  set_alarm(alarm.hours, alarm.minutes, alarm.seconds, alarm.days);
  while(1){
	  switch (alarm_start){
	  case 1:
		  get_time();
		  lcd_display(&disp);
		  HAL_Delay(950);
		  break;
	  case 0:
		  sprintf((char*)disp.f_line, ALERT_1);
		  sprintf((char*)disp.s_line, ALERT_2);
		  lcd_display(&disp);
		  HAL_Delay(500);
		  lcd_clear(&disp);
		  HAL_Delay(500);
		  HAL_GPIO_TogglePin(LD12_GPIO_Port, LD12_Pin);
		  HAL_GPIO_TogglePin(LD13_GPIO_Port, LD13_Pin);
		  HAL_GPIO_TogglePin(LD14_GPIO_Port, LD14_Pin);
		  HAL_GPIO_TogglePin(LD15_GPIO_Port, LD15_Pin);

		  lcd_clear(&disp);
		  if (alarm_start == 1){
			  HAL_GPIO_WritePin(LD12_GPIO_Port, LD12_Pin, 0);
			  HAL_GPIO_WritePin(LD13_GPIO_Port, LD13_Pin, 0);
			  HAL_GPIO_WritePin(LD14_GPIO_Port, LD14_Pin, 0);
			  HAL_GPIO_WritePin(LD15_GPIO_Port, LD15_Pin, 0);
		  break;
		  }
	  }
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
	alarm_start = 0;

}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	if (GPIO_Pin == PA0_Pin){
		alarm_start = 1;
	}

	if (GPIO_Pin == C4_PIN){
		HAL_TIM_Base_Start_IT(&htim1);
		state = false;

	}

	if (GPIO_Pin == C3_PIN){
		HAL_TIM_Base_Start_IT(&htim1);
		state = false;

	}

	if (GPIO_Pin == C2_PIN){
		HAL_TIM_Base_Start_IT(&htim1);
		state = false;

	}

	if (GPIO_Pin == C1_PIN){
		HAL_TIM_Base_Start_IT(&htim1);
		state = false;
	}
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	UNUSED(htim);
	if(HAL_GPIO_ReadPin(C4_PORT, C4_PIN) == GPIO_PIN_RESET){
		if (counter == 0 || counter == 1){
			if (HAL_GPIO_ReadPin(R4_PORT, R4_PIN) == GPIO_PIN_RESET) {
				if (clock.hours >= 0 && clock.hours < 23) ++clock.hours;
				else clock.hours = 0;
			}
			if (HAL_GPIO_ReadPin(R3_PORT, R3_PIN) == GPIO_PIN_RESET) {
				if (clock.days >= 0 && clock.days < 31) ++clock.days;
				else clock.days = 0;
			}
		}
		else if (counter == 2 || counter == 3){
			if (HAL_GPIO_ReadPin(R4_PORT, R4_PIN) == GPIO_PIN_RESET){
				if (alarm.hours >= 0 && alarm.hours < 23) ++d.hours;
				else d.hours = 0;
			}
			if (HAL_GPIO_ReadPin(R3_PORT, R3_PIN) == GPIO_PIN_RESET){
				if (alarm.days >= 0 && alarm.days < 31) ++d.days;
				else d.days = 0;
			}
		}
		refresh_lcd = 1;
		state = true;
		HAL_TIM_Base_Stop_IT(&htim1);
	}

	if(HAL_GPIO_ReadPin(C3_PORT, C3_PIN) == GPIO_PIN_RESET){
		if (counter == 0 || counter == 1){
			if (HAL_GPIO_ReadPin(R4_PORT, R4_PIN) == GPIO_PIN_RESET){
				if (clock.minutes >= 0 && clock.minutes < 59) ++clock.minutes;
				else clock.minutes = 0;
			}
			if (HAL_GPIO_ReadPin(R3_PORT, R3_PIN) == GPIO_PIN_RESET){
				if (clock.months >= 0 && clock.months < 12) ++clock.months;
				else clock.months = 0;			}
		}
		else if (counter == 2 || counter == 3){
			if (HAL_GPIO_ReadPin(R4_PORT, R4_PIN) == GPIO_PIN_RESET){
				if (alarm.minutes >= 0 && alarm.minutes < 59) ++d.minutes;
				else d.minutes = 0;
			}
			if (HAL_GPIO_ReadPin(R3_PORT, R3_PIN) == GPIO_PIN_RESET){
				if (alarm.months >= 0 && alarm.months < 12) ++d.months;
				else d.months = 0;
			}
		}
		refresh_lcd = 1;
		state = true;
		HAL_TIM_Base_Stop_IT(&htim1);
	}

	if (HAL_GPIO_ReadPin(C2_PORT, C2_PIN) == GPIO_PIN_RESET){
		if (counter == 0 || counter == 1){
			if (HAL_GPIO_ReadPin(R4_PORT, R4_PIN) == GPIO_PIN_RESET){
				if (clock.seconds >= 0 && clock.seconds < 59) ++clock.seconds;
				else clock.seconds = 0;
			}
			if (HAL_GPIO_ReadPin(R3_PORT, R3_PIN) == GPIO_PIN_RESET){
				++clock.years;
			}
		}
		else if (counter == 2 || counter == 3){
			if (HAL_GPIO_ReadPin(R4_PORT, R4_PIN) == GPIO_PIN_RESET){
				if (alarm.seconds >= 0 && alarm.seconds < 59) ++d.seconds;
				else d.seconds = 0;
			}
			if (HAL_GPIO_ReadPin(R3_PORT, R3_PIN) == GPIO_PIN_RESET) {
				++d.years;
			}
		}
		refresh_lcd = 1;
		state = true;
		HAL_TIM_Base_Stop_IT(&htim1);
	}
	if (HAL_GPIO_ReadPin(C1_PORT, C1_PIN) == GPIO_PIN_RESET){
		HAL_GPIO_TogglePin(R4_PORT, R4_PIN);
		HAL_GPIO_TogglePin(R3_PORT, R3_PIN);
		counter++;
		state = true;
		HAL_TIM_Base_Stop_IT(&htim1);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
