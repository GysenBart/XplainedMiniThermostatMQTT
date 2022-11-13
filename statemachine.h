/*
 * statemachine.h
 *
 * Created: 10/05/2022 20:46:16
 *  Author: bart-
 */ 


#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

//defines used in the statemachine
#define ATCHECK				1
#define ATCHECKOK			2
#define ATWIFICONNECT		3
#define ATUSERCONF			4
#define ATMQTTCONNECTION	5
#define ATMQTTSUB			6
#define ATMQTTPUB			7


void AT_statemachine(void);



#endif /* STATEMACHINE_H_ */