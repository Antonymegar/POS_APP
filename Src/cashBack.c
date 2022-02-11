#include <sdk_tplus.h>
#include "Menu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LAYOUT_ID 0x0900


    char pinpadMask[] = "/d/d/d/d";
    char pin[4];
    char Currency[4+1] = "Kshs";
    char saleMask[]= "/d,/d/d/d";
    char sale[4+1];
	char cashBackMask[]="/d,/d/d/d";
	char cashBack[4+1];
	char pin[4];
	char totalAmount[30];
	char cardDetails[400];

	static const char szDate[] = "Date:%.2s/%.2s/%.2s  %.2s:%.2s\n";


void makeCashBack(void) {




	memset(sale, 0, sizeof sale);
	memset(cashBack, 0, sizeof cashBack);
	memset(pinpadMask , 0, sizeof(pinpadMask));
	memset(pin , 0, sizeof(pin));
	memset(totalAmount, 0, sizeof(totalAmount));
	memset(cardDetails, 0, sizeof(cardDetails));





	GL_Dialog_Amount(gGoalGraphicLibInstance, NULL, "Enter Sale Amount", saleMask, sale, sizeof(sale) - 1, Currency, GL_ALIGN_BOTTOM_RIGHT, 1 * GL_TIME_MINUTE);


	GL_Dialog_Amount(gGoalGraphicLibInstance, NULL, "Enter CashBack", cashBackMask, cashBack, sizeof(cashBack) - 1, Currency, GL_ALIGN_BOTTOM_RIGHT, 1 * GL_TIME_MINUTE);

//    printCashBack(myLayout, myline, GL_ENCODING_UTF8, sale, cashBack, totalAmount);

	int  saleAmount = atoi(sale);
	int  cash= atoi(cashBack);

	int total = saleAmount + cash;

    sprintf(totalAmount, "%d", total);


	  waitCard(cardDetails);


	  GL_Dialog_Password(gGoalGraphicLibInstance, "Pin", "Enter Pin:",pinpadMask, pin, sizeof(pin) , GL_TIME_MINUTE);


	  printReciept(sale,cashBack,totalAmount,cardDetails);

}

 void printReciept(char *sale , char * cashBack ,char *totalAmount, char *cardDetails) {



	              Telium_Date_t date;
				  Telium_File_t *hPrinter;
				  hPrinter = Telium_Fopen("PRINTER", "w-*"); // Open printer driver
				     if (hPrinter != NULL)
				     {
				         Telium_Pprintf("       CASHBACK     \n"
				                           "POS EVALUATION\n"
				                           "ANTONY's TAKE \n\n" );
				         Telium_Read_date(&date); // Print date and time
				         Telium_Pprintf(szDate, date.day, date.month, date.year, date.hour, date.minute);
				         Telium_Pprintf("Sale Amount: %s\n", sale);
				         Telium_Pprintf("Cash Back: %s\n", cashBack);
				         Telium_Pprintf("Total Amount: %s\n",totalAmount );
                         Telium_Pprintf("Card Number: %s\n", cardDetails);
				         Telium_Ttestall(PRINTER, 0);

				         Telium_Fclose(hPrinter); // Close printer driver
				     }


}



