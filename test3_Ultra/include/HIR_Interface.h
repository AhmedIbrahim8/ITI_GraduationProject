/*******************************************************************************************/
/*  Module       :   Infrared                                                              */
/*  File Name    :   HIR_Interface.h                                                       */
/*  Description  :   Header File of the HIR Driver Interface                               */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   18/09/2023                                                            */
/*******************************************************************************************/

#ifndef HIR_INTERFACE_H_
#define HIR_INTERFACE_H_

/********************************************************************************************/
/************************************** Masks and Numbers Used  *****************************/
/********************************************************************************************/
#define      HIR_NUMBER_0                                0
#define      HIR_NUMBER_1                                1
#define      HIR_NUMBER_8                                8
#define      HIR_NUMBER_24                               24
#define      HIR_START_TIME_OF_LOGIC_0                   1000
#define      HIR_END_TIME_OF_LOGIC_0                     1500
#define      HIR_START_TIME_OF_LOGIC_1                   2000
#define      HIR_END_TIME_OF_LOGIC_1                     2500

#define      SYSTICK_TIME_START                          320000

#define      HIR_INCREMENT_DATA                          168

#define      HIR_DECREMENT_DATA                          224

#define      HIR_ONE_DATA                                48

#define      HIR_TWO_DATA                                24

#define      HIR_THREE_DATA                              122

#define      HIR_FOUR_DATA                               16
/********************************************************************************************/
/****************************** Extern Shared Global Variables ******************************/
/********************************************************************************************/
extern volatile u8 data;




/********************************************************************************************/
/************************************** APIs Proto-Types ************************************/
/********************************************************************************************/
void GetFrame(void);

void GetData(void);


#endif /* HIR_INTERFACE_H_ */
