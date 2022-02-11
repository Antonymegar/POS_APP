#include <sdk_tplus.h>
#include "Menu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//Global Variables

    char curr[4+1] = "Kshs";
    char billNumberMask[] = "/d/d/d/d/d/d/d/d";
	char billNumber[8+1];
	char No[4]= "No.";
	char billamountMask[] = "/d/d/d/d/d/d/d/D";
    char billamount[12];
    static const char szDate[] = "Date:%.2s/%.2s/%.2s  %.2s:%.2s\n";



void makeBillPayment( void ){

	   memset(billNumber, 0, sizeof billNumber);
	   memset(billamount, 0, sizeof billamount);


		GL_Dialog_Amount(gGoalGraphicLibInstance, "PayBill", "Enter Pay Bill", billNumberMask , billNumber, sizeof(billNumber) - 1, No, GL_ALIGN_BOTTOM_RIGHT, 1 * GL_TIME_MINUTE);



	    if (strlen(billNumber) < 5 || strlen (billNumber) >8 ) {
	    	GL_Dialog_Message(gGoalGraphicLibInstance, "Invalid Input", "PayBill should  be  between  5 and 8 characters ", GL_ICON_WARNING, GL_BUTTON_VALID_CANCEL, GL_TIME_MINUTE);
	    }


	    else {


	    	      GL_Dialog_Amount(gGoalGraphicLibInstance,"Amount", "Enter Amount", billamountMask, billamount, sizeof(billamount) - 1, curr, GL_ALIGN_BOTTOM_RIGHT, 1 * GL_TIME_MINUTE);
	    		  GL_Dialog_Message(gGoalGraphicLibInstance, "Amount", billamount , GL_ICON_INFORMATION, GL_BUTTON_NONE, 3 * GL_TIME_SECOND);



	    }
	     printBill(billNumber, billamount);

}

void printBill(char *billNumber , char * billamount ){
	              Telium_Date_t date;
				  Telium_File_t *hPrinter;
				  hPrinter = Telium_Fopen("PRINTER", "w-*"); // Open printer driver
				     if (hPrinter != NULL)
				     {
				         Telium_Pprintf("    BILL  \n"
				        		         "POS EVALUATION\n"
				        		        "ANTONY's TAKE \n\n" );
				         Telium_Read_date(&date); // Print date and time
				         Telium_Pprintf(szDate, date.day, date.month, date.year, date.hour, date.minute);
				         Telium_Pprintf("Bill Number: %s\n", billNumber);
				         Telium_Pprintf("Bill Amount: %s\n", billamount);
                         Telium_Ttestall(PRINTER, 0);

				         Telium_Fclose(hPrinter); // Close printer driver
				     }


}


