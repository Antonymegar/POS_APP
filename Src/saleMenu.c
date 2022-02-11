#include <sdk_tplus.h>
#include "Menu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LAYOUT_ID  0x0900


//Global Variables

char amountMask[] = "/d/d/d,/d/d/d,/d/D";
char pinMask[] = "/d/d/d/d";
char pin[4];
char Curr[4+1] = "Kshs";
char cardDetails[150];
static const char szDate[] = "Date:%.2s/%.2s/%.2s  %.2s:%.2s\n";

 extern void makeSale(void){
 //local variables

	char saleAmountMask[] = "/d,/d/d/d";
	char saleAmount[12];

	memset(saleAmount, 0, sizeof saleAmount);
	memset(pinMask , 0, sizeof(pinMask ));
	memset(pin , 0, sizeof(pin));
    memset(cardDetails, 0, sizeof(cardDetails));


	GL_Dialog_Amount(gGoalGraphicLibInstance, NULL, "Enter Sale Amount", saleAmountMask, saleAmount, sizeof(saleAmount) - 1, Curr, GL_ALIGN_BOTTOM_RIGHT, 1 * GL_TIME_MINUTE);

    int converted= atoi(saleAmount);

    if (converted < 1 || converted > 5000) {
    	GL_Dialog_Message(gGoalGraphicLibInstance, "Invalid Input", "Amount should be more than 1 and less than 5000", GL_ICON_WARNING, GL_BUTTON_VALID_CANCEL, 2 *  GL_TIME_SECOND);
    }

    else {
    	GL_Dialog_Message(gGoalGraphicLibInstance, "Sale Amount", saleAmount , GL_ICON_INFORMATION, GL_BUTTON_NONE, 3 * GL_TIME_SECOND);

		 waitCard(cardDetails);

        GL_Dialog_Password(gGoalGraphicLibInstance, "Pin", "Enter Pin:", pinMask,pin, sizeof(pin), GL_TIME_MINUTE);
    }

      printSales(saleAmount);

}

void printSales( char *saleAmount  ){

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
	       				         Telium_Pprintf("Sale Amount: %s\n", saleAmount);
	       	                     Telium_Pprintf("Card Number: %s\n", cardDetails);
	       				         Telium_Ttestall(PRINTER, 0);

	       				         Telium_Fclose(hPrinter); // Close printer driver
	       				     }


}




