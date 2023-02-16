// SPDX-FileCopyrightText: 2022-2023 BlueMicro_nRF52_Arduino_Library contributors (https://github.com/jpconstantineau/BlueMicro_nRF52_Arduino_Library/graphs/contributors)
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef BLUEMICRO_SAMD_H
#define BLUEMICRO_SAMD_H
#include <Arduino.h>
#include <cstdint>
#include <vector>
#include <bluemicro_hid.h>


/**************************************************************************************************************************/
template < size_t N1,  size_t N2>
trigger_keys_t scanMatrix_C2R(trigger_keys_t activeKeys,  const byte (&rows)[N1], const byte (&columns)[N2] )
{
    activeKeys.clear();
    for (int i = 0; i < N2; ++i){
        pinMode((columns[i]), INPUT_PULLUP);
    }

    for (int j = 0; j < N1; ++j){
        // set the current row as OUPUT and LOW
        pinMode(rows[j], OUTPUT);
        digitalWrite(rows[j],LOW); 
        delayMicroseconds(10);     
        for (int i = 0; i < N2; ++i){
            if(!digitalRead((columns[i]))) {
                uint8_t keynumber = (j)*N2 + i;
                activeKeys.push_back(keynumber);
            } 
        }
        pinMode(rows[j], INPUT);                                                   // 'disables' the row that was just scanned
    }

    /*************/ 
    //Scanning done, disabling all columns - needed to save power
    for (int i = 0; i < N2; ++i) {                             
        pinMode(columns[i], INPUT);                                     
    }
    return activeKeys;
}

/**************************************************************************************************************************/
template < size_t N1,  size_t N2>
trigger_keys_t scanMatrix_R2C(trigger_keys_t activeKeys,  const byte (&rows)[N1], const byte (&columns)[N2] )
{
    activeKeys.clear();
    for (int i = 0; i < N2; ++i){
        pinMode((columns[i]), INPUT_PULLDOWN);
    }

    for (int j = 0; j < N1; ++j){
        // set the current row as OUPUT and LOW
        pinMode(rows[j], OUTPUT);
        digitalWrite(rows[j],HIGH);  
        delayMicroseconds(10);    
        for (int i = 0; i < N2; ++i){
            if(digitalRead((columns[i]))) {
                uint8_t keynumber = (j)*N2 + i;
                activeKeys.push_back(keynumber);
            } 
        }
        pinMode(rows[j], INPUT);                                                   // 'disables' the row that was just scanned
    }

    /*************/ 
    //Scanning done, disabling all columns - needed to save power
    for (int i = 0; i < N2; ++i) {                             
        pinMode(columns[i], INPUT);                                     
    }
    return activeKeys;
}


template < size_t N1,  size_t N2>
void sleep_C2R( const byte (&rows)[N1], const byte (&columns)[N2] ) {
 
}

template < size_t N1,  size_t N2>
void sleep_R2C( const byte (&rows)[N1], const byte (&columns)[N2] ) {
  
}



#endif