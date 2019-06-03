//
// Created by marci on 28.05.2019.
//

#include <morse.h>
#include "main.h"
#include "usbd_cdc_if.h"
#include <stdlib.h>
#include <lcd.h>
#include "logo.h"

// htim
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

// Zmienne morsowe
uint8_t stop = 0;
uint16_t val = 0;
char *results; // zapisujemy w tym morsowe litery
char *word;


// Wysyłanie
char dataToSend[40];    // array for date to send
char messageLength = 0; //  length of message

// Odbieranie
char receivedData[2048];        // ara
uint8_t receivedDataFlag = 0;   // Flaga informujaca o odebraniu danych
char temp[40];                  // temporary for sending morse
const char *letter = "* ETIANMSURWDKGOHVF?L?PJBXCYZQ??";    // zeby tlumaczyc morsa

// Kolejne zmienne morsowe
char *morses = "";
uint8_t x = 0x00;
uint8_t y = 0x00;
int b = 0;
int reset = 0;  // reset ekranu, jesli wyswietla sie wynik
int space = 0;  // czy poprzednim znakiem byla spacja

// Zmienne dzwiekowe
uint8_t enableSound = 0;

char *concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void frommorse(const char receive[40], char send[40])
{
    uint8_t let = 1;
    for (int i = 0; i < 4; i++)
    {

        if (receive[i] == 46)
        {
            let = let * 2;
        }
        else if (receive[i] == 45)
        {
            let = let * 2 + 1;
        }
        else
        {
            break;
        }
    }
    char temp_[2];
    temp_[0] = letter[let];
    temp_[1] = '\0';
    strcpy(send, temp_);
}

void tomorse(char letter1, char receive[40])
{
    //char morse[40];
    memset(receive, 0, 40);

    if (letter1 == 'a')
    {
        sprintf(receive, ".-");
    }
    else if (letter1 == 'b')
    {
        sprintf(receive, "-...");
    }
    else if (letter1 == 'c')
    {
        sprintf(receive, "-.-.");
    }
    else if (letter1 == 'd')
    {
        sprintf(receive, "-..");
    }
    else if (letter1 == 'e')
    {
        sprintf(receive, ".");
    }
    else if (letter1 == 'f')
    {
        sprintf(receive, "..-.");
    }
    else if (letter1 == 'g')
    {
        sprintf(receive, "--.");
    }
    else if (letter1 == 'h')
    {
        sprintf(receive, "....");
    }
    else if (letter1 == 'i')
    {
        sprintf(receive, "..");
    }
    else if (letter1 == 'j')
    {
        sprintf(receive, ".---");
    }
    else if (letter1 == 'k')
    {
        sprintf(receive, "-.-");
    }
    else if (letter1 == 'l')
    {
        sprintf(receive, ".-..");
    }
    else if (letter1 == 'm')
    {
        sprintf(receive, "--");
    }
    else if (letter1 == 'n')
    {
        sprintf(receive, "-.");
    }
    else if (letter1 == 'o')
    {
        sprintf(receive, "---");
    }
    else if (letter1 == 'p')
    {
        sprintf(receive, ".--.");
    }
    else if (letter1 == 'q')
    {
        sprintf(receive, "--.-");
    }
    else if (letter1 == 'r')
    {
        sprintf(receive, ".-.");
    }
    else if (letter1 == 's')
    {
        sprintf(receive, "...");
    }
    else if (letter1 == 't')
    {
        sprintf(receive, "-");
    }
    else if (letter1 == 'u')
    {
        sprintf(receive, "..-");
    }
    else if (letter1 == 'v')
    {
        sprintf(receive, "...-");
    }
    else if (letter1 == 'w')
    {
        sprintf(receive, ".--");
    }
    else if (letter1 == 'x')
    {
        sprintf(receive, "-..-");
    }
    else if (letter1 == 'y')
    {
        sprintf(receive, "-.--");
    }
    else if (letter1 == 'z')
    {
        sprintf(receive, "--..");
    }
    else if (letter1 == ' ')
    {
        sprintf(receive, " ");
    }

}

// Funkcje do przerwania TIM4
void display_result()
{
    messageLength = sprintf(dataToSend, "%s to: %s\n\r", morses, word);
    CDC_Transmit_FS((unsigned char *) dataToSend, messageLength);
    morses = "";

    results = concat("wynik to \"", word);
    results = concat(results, "\" ");
    lcd_write(results);
    results = "";
    word = "";
    reset = 1;
    stop = 0;
}

void display_symbol()
{

    if (val > 0)
    {
        b++;
        if (b >= 14)
        {
            y += 1;
            b = 0;
            x = 0;
        }
        else x += 6;

        if (val < 4)space = 0;

        if (val > 4)
        {
            morses = concat(morses, results);
            morses = concat(morses, " ");


            frommorse(results, results);
            word = concat(word, results);
            results = "";
            lcd_write(" ");

            if (space == 1)
            {
                word = concat(word, " ");
                space = 0;
            }
            else
                space = 1;

            if (val > 8)
            { stop = 1; }

            //... . -. -.. -. ..- -.. . ...
            //...---...
        }
        else if (val > 2)
        {
            lcd_write("-");
            results = concat(results, "-");
            enableSound = 3;
        }
        else
        {
            lcd_write(".");
            results = concat(results, ".");
            enableSound = 1;
        }
        val = 0;
    }
}

void change_symbol()
{

    val++;
    if (reset == 1)
    {
        x = 0x00;
        y = 0x00;
        if (val > 0)
        {
            lcd_data(morse, sizeof(morse));
            reset = 0;
            val = 0;
        }
    }
    else if (val > 0)
    {
        if (val > 12)val = 0;
        else if (val > 8)
        {
            lcd_write("X");
        }
        else if (val > 4)
        {
            lcd_write(" ");
        }
        else if (val > 2)
        {
            lcd_write("-");
        }
        else
        {
            lcd_write(".");
        }

    }
    lcd_command(0x40 | y);   // Zerowanie Y
    lcd_command(0x80 | x);   // Zerowanie X
}


// Przerwanie
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        // Generowanie kwadratu
        if (enableSound >= 1)
        {
            HAL_GPIO_TogglePin(Sound_GPIO_Port, Sound_Pin);
        }
        else
        {
            HAL_GPIO_WritePin(Sound_GPIO_Port, Sound_Pin, GPIO_PIN_RESET);
        }
    }
    if (htim->Instance == TIM4)
    {
        if (enableSound > 0)
            enableSound--;

        if (HAL_GPIO_ReadPin(GPIOB, Joy_Button_Pin) == 1)
        {
            if (stop == 1)
            {
                display_result();
            }
            else
            {
                display_symbol();
            }
        }
        else
        {
            change_symbol();
        }
    }
}

void setup()
{
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start_IT(&htim4);

    HAL_GPIO_WritePin(BL_GPIO_Port, BL_Pin, GPIO_PIN_SET);

    lcd_reset();

    // Konfiguracja dźwięku
    lcd_command(0x21);
    lcd_command(0x14);
    lcd_command(0x80 | 0x2f); // Ustawienie kontrastu
    lcd_command(0x20);
    lcd_command(0x0c);

    for (int j = 0; j < 504; j++) lcd_symbol(0, 1); // reset ekranu
    lcd_command(0x40 | 0x00);       // Zerowanie Y
    lcd_command(0x80 | 0x00);       // Zerowanie X
    lcd_data(morse, sizeof(morse)); // Rysowanie logo
    lcd_command(0x40 | 0x00);       // Zerowanie Y
    lcd_command(0x80 | 0x00);       // Zerowanie X
}

void loop()
{
    if (receivedDataFlag == 1)
    {
        lcd_command(0x40 | 0x00);   // Zerowanie Y
        lcd_command(0x80 | 0x00);   // Zerowanie X
        lcd_data(morse, sizeof(morse));

        receivedDataFlag = 0;

        messageLength = sprintf(dataToSend, "odebrano : %s\n\r", receivedData);
        CDC_Transmit_FS((unsigned char *) dataToSend, messageLength);
        lcd_write(receivedData);

        char *re = " to ";
        char tempi[40];
        char tempii[40];
        int k = -1;
        int tryb=1;//0-lacina, 1-morse
        for (int i = 0; i < 1; i++)
        {
        	if (receivedData[i] == '-' || receivedData[i] == '.'||receivedData==' '||receivedData=='\0'||receivedData=='\n')
        	{
        		if(tryb==1)
        		tryb=1;
        	}//97-122
        	else
        	{
        		tryb=0;
        	}
        }

        for (int i = 0; i < 40; i++)
        {
            if (tryb==1)
            {
                if (receivedData[i] != ' ' && i < 39)
                {
                    k++;
                    tempii[k] = receivedData[i];
                }
                else
                {
                    k = -1;
                    frommorse(tempii, tempi);
                    for (int j = 0; j < 40; j++)
                    {
                        tempii[j] = '\0';
                    }
                    re = concat(re, tempi);
                    for (int j = 0; j < 40; j++)
                    {
                        tempi[39] = '\0';
                    }
                }
            }
            else
            {
                tomorse(receivedData[i], tempi);
                re = concat(re, tempi);
                re = concat(re, " ");
            }
        }
        lcd_write(re);

        if (tryb==0)//gdy wynik to morse
        {
        	HAL_Delay(100);
        	int size=strlen(re);
        	for(int i=0;i<size;i++)
        		        {
        		        if(re[i]=='.'){enableSound=1;}
        		        else if(re[i]=='-'){enableSound=3;}
        		        else if(re[i]==' '&& re[i+1]!=' '){HAL_Delay(400);}
        		        while(enableSound>0){HAL_GPIO_TogglePin(Sound_GPIO_Port, Sound_Pin);HAL_Delay(50);}
        		        if(re[i]!=' ')HAL_Delay(200);
        		        }
        }

        if (tryb==1)//gdy dane to morse
                {
                	HAL_Delay(100);
                	int size=strlen(receivedData);
                	for(int i=0;i<size;i++)
                		        {
                		        if(receivedData[i]=='.'){enableSound=1;}
                		        else if(receivedData[i]=='-'){enableSound=3;}
                		        else if(receivedData[i]==' '&& receivedData[i+1]!=' '){HAL_Delay(400);}
                		        while(enableSound>0){HAL_GPIO_TogglePin(Sound_GPIO_Port, Sound_Pin);HAL_Delay(50);}
                		        if(receivedData[i]!=' ')HAL_Delay(200);
                		        }
                }

        for (uint8_t i = 0; i < 40; i++)
        {
            dataToSend[i] = 0;
        }

        reset=1;
    }
}
