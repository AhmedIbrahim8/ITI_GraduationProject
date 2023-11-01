/*[FILE NAME]   : common_macros.h
 *[AUTHOR]      : AHMED IBRAHIM
 *[DATE CREATED]: Sep 29, 2021
 *[DESCRIPTION] : this file contain the common macros which will be used in all applications
 */

#ifndef COMMON_MACROS_H_
/*this line is mandatory to not include the file more than one in the same file
 * */
#define COMMON_MACROS_H_

#define SET_BIT(REG,BIT_NUM)       ((REG)=(REG)|((1<<(BIT_NUM)))) /*To put logic 1 inside bit */

#define CLEAR_BIT(REG,BIT_NUM)     ((REG)=(REG)&(~(1<<(BIT_NUM)))) /*To put logic 0 inside bit */

#define TOGGLE_BIT(REG,BIT_NUM)    ((REG)=( REG )^(1<<(BIT_NUM))) /*To toggle the logic of the bit */

#define BIT_IS_SET(REG,BIT_NUM)    ((REG)&((1<<(BIT_NUM)))) /*To check if the bit is 1 */

#define BIT_IS_CLEAR(REG,BIT_NUM)  (!((REG)&(1<<(BIT_NUM)))) /*To check if the bit is 0 */

#define ROR(REG,BIT_NUM)           ((REG)=(((REG)>>(BIT_NUM))|((REG)<<((8*sizeof((REG)))-(BIT_NUM)))))

#define ROL(REG,BIT_NUM)           ((REG) = (((REG)<<(BIT_NUM) )|((REG)>>((8*sizeof((REG)))-(BIT_NUM)))))

#define GET_BIT(REG,BIT_NUM)       (((REG)&(1<<(BIT_NUM)))>>(BIT_NUM))



#endif /* COMMON_MACROS_H_ */
