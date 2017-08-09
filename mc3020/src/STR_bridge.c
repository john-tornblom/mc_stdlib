/*----------------------------------------------------------------------------
 * File:  STR_bridge.c
 *
 * Description:
 * Methods for bridging to an external entity.
 *
 * External Entity:  String (STR)
 * 
 * Copyright 2017 John Törnblom
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *--------------------------------------------------------------------------*/

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "STR_bridge.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


/*
 * Bridge:  To_Boolean
 */
bool
STR_To_Boolean( c_t p_value[ESCHER_SYS_MAX_STRING_LEN] )
{
  return strncasecmp(p_value, "true", ESCHER_SYS_MAX_STRING_LEN) == 0;
}


/*
 * Bridge:  To_Integer
 */
i_t
STR_To_Integer( c_t p_value[ESCHER_SYS_MAX_STRING_LEN] )
{
  if(strstr(p_value, "x") || strstr(p_value, "X")) {
    return strtol(p_value, NULL, 16);
  } else {
    return atoi(p_value);
  }
}


/*
 * Bridge:  To_Real
 */
r_t
STR_To_Real( c_t p_value[ESCHER_SYS_MAX_STRING_LEN] )
{
  return atof(p_value);
}


/*
 * Bridge:  To_Unique_Id
 */
Escher_UniqueID_t
STR_To_Unique_Id( c_t p_value[ESCHER_SYS_MAX_STRING_LEN] )
{
  unsigned char uuid[16];
  Escher_UniqueID_t value;
  
  sscanf(p_value,
	 "%02hhx%02hhx%02hhx%02hhx-"
	 "%02hhx%02hhx-"
	 "%02hhx%02hhx-"
	 "%02hhx%02hhx-"
	 "%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx",
	 &uuid[15], &uuid[14], &uuid[13], &uuid[12],
	 &uuid[11], &uuid[10],
	 &uuid[9], &uuid[8],
	 &uuid[7], &uuid[6],
	 &uuid[5], &uuid[4], &uuid[3], &uuid[2], &uuid[1], &uuid[0]);

  memcpy(&value, uuid, sizeof(Escher_UniqueID_t));
    
  return value;
}


/*
 * Bridge:  From_Boolean
 */
c_t *
STR_From_Boolean( c_t A0xtumlsret[ESCHER_SYS_MAX_STRING_LEN], const bool p_value )
{
  if(p_value) {
    strncpy(A0xtumlsret, "true", ESCHER_SYS_MAX_STRING_LEN);
  } else {
    strncpy(A0xtumlsret, "false", ESCHER_SYS_MAX_STRING_LEN);
  }
  return A0xtumlsret;
}


/*
 * Bridge:  From_Integer
 */
c_t *
STR_From_Integer( c_t A0xtumlsret[ESCHER_SYS_MAX_STRING_LEN], const i_t p_value )
{
  snprintf(A0xtumlsret, ESCHER_SYS_MAX_STRING_LEN, "%d", p_value);
  return A0xtumlsret;
}


/*
 * Bridge:  From_Real
 */
c_t *
STR_From_Real( c_t A0xtumlsret[ESCHER_SYS_MAX_STRING_LEN], const r_t p_value )
{
  snprintf(A0xtumlsret, ESCHER_SYS_MAX_STRING_LEN, "%f", p_value);
  return A0xtumlsret;
}


/*
 * Bridge:  From_Unique_Id
 */
c_t *
STR_From_Unique_Id( c_t A0xtumlsret[ESCHER_SYS_MAX_STRING_LEN], Escher_UniqueID_t p_value )
{
  unsigned char uuid[16];
 
  memset(uuid, 0, sizeof(uuid));
  memcpy(uuid, &p_value, sizeof(Escher_UniqueID_t));

  snprintf(A0xtumlsret,
	   ESCHER_SYS_MAX_STRING_LEN,
	   "%02hhx%02hhx%02hhx%02hhx-"
	   "%02hhx%02hhx-"
	   "%02hhx%02hhx-"
	   "%02hhx%02hhx-"
	   "%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx",
	   uuid[15], uuid[14], uuid[13], uuid[12],
	   uuid[11], uuid[10],
	   uuid[9], uuid[8],
	   uuid[7], uuid[6],
	   uuid[5], uuid[4], uuid[3], uuid[2], uuid[1], uuid[0]);

  return A0xtumlsret;
}


/*
 * Bridge:  Length
 */
i_t
STR_Length( c_t p_str[ESCHER_SYS_MAX_STRING_LEN] )
{
  return strlen(p_str);
}


/*
 * Bridge:  Index
 */
i_t
STR_Index( const i_t p_start, c_t p_str[ESCHER_SYS_MAX_STRING_LEN], c_t p_sub[ESCHER_SYS_MAX_STRING_LEN] )
{
  char *p = strstr(p_str, p_sub);
  if(!p) {
    return -1;
  } else {
    return p - p_str;
  }
}


/*
 * Bridge:  Replace
 */
c_t *
STR_Replace( c_t A0xtumlsret[ESCHER_SYS_MAX_STRING_LEN], c_t p_new[ESCHER_SYS_MAX_STRING_LEN], c_t p_old[ESCHER_SYS_MAX_STRING_LEN], c_t p_str[ESCHER_SYS_MAX_STRING_LEN] )
{
  char *p;
  int i = 0;

  A0xtumlsret[0] = '\0';

  do {
    if(!(p=strstr(p_str, p_old))) {
      strncat(A0xtumlsret, p_str, MIN(ESCHER_SYS_MAX_STRING_LEN - strlen(A0xtumlsret), strlen(p_str)));
    } else {
      strncat(A0xtumlsret, p_str, MIN(ESCHER_SYS_MAX_STRING_LEN - strlen(A0xtumlsret), p-p_str));
      strncat(A0xtumlsret, p_new, MIN(ESCHER_SYS_MAX_STRING_LEN - strlen(A0xtumlsret), strlen(p_new)));
      p_str = p + strlen(p_old);
    }
  } while (p);

  return A0xtumlsret;
}


/*
 * Bridge:  From_ASCII_Code
 */
c_t *
STR_From_ASCII_Code( c_t A0xtumlsret[ESCHER_SYS_MAX_STRING_LEN], const i_t p_code )
{
  if(p_code >= 0 && p_code <= 127) {
    A0xtumlsret[0] = (char)p_code;
    A0xtumlsret[1] = '\0';
  } else {
    A0xtumlsret[0] = '\0';
  }
  return A0xtumlsret;
}


/*
 * Bridge:  To_ASCII_Code
 */
i_t
STR_To_ASCII_Code( const i_t p_index, c_t p_str[ESCHER_SYS_MAX_STRING_LEN] )
{
  if(p_index >= 0 && p_index <= ESCHER_SYS_MAX_STRING_LEN) {
    return p_str[p_index];
  } else {
    return -1;
  }
}


/*
 * Bridge:  Substring
 */
void
STR_Substring( const i_t p_end, const i_t p_start, c_t p_str[ESCHER_SYS_MAX_STRING_LEN] )
{
  /* Replace/Insert your implementation code here... */
}


/*
 * Bridge:  Contains
 */
bool
STR_Contains( c_t p_str[ESCHER_SYS_MAX_STRING_LEN], c_t p_sub[ESCHER_SYS_MAX_STRING_LEN] )
{
  char* p = strstr(p_str, p_sub);
  return p != NULL;
}

