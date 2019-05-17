/*#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "logo.h"

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
*/
