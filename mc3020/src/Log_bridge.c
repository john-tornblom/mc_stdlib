/*----------------------------------------------------------------------------
 * File:  Log_bridge.c
 *
 * Description:
 * Methods for bridging to an external entity.
 *
 * External Entity:  Logging (Log)
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

#include "mc_stdlib_testing_sys_types.h"
#include "FS_bridge.h"
#include "Log_bridge.h"
#include "PROC_bridge.h"
#include "STR_bridge.h"
#include "Log_bridge.h"
#include "mc_stdlib_testing_sys_types.h"

#include <stdio.h>


/*
 * Global state for the external entity
 */
static mc_stdlib_testing_Log_Level_t g_level = mc_stdlib_testing_Log_Level_Notice_e;
static i_t                           g_fd    = 2; //stderr


/*
 * Bridge:  Configure
 */
void
Log_Configure( const i_t p_fd, const mc_stdlib_testing_Log_Level_t p_level )
{
  g_fd = p_fd;
  g_level = p_level;
}


/*
 * Bridge:  Fatal
 */
void
Log_Fatal( c_t p_msg[ESCHER_SYS_MAX_STRING_LEN] )
{
  if(g_level >= mc_stdlib_testing_Log_Level_Fatal_e) {
    dprintf(g_fd, "FATAL:%s\n", p_msg);
  }
}


/*
 * Bridge:  Critical
 */
void
Log_Critical( c_t p_msg[ESCHER_SYS_MAX_STRING_LEN] )
{
  if(g_level >= mc_stdlib_testing_Log_Level_Critical_e) {
    dprintf(g_fd, "CRITICAL:%s\n", p_msg);
  }
}


/*
 * Bridge:  Error
 */
void
Log_Error( c_t p_msg[ESCHER_SYS_MAX_STRING_LEN] )
{
  if(g_level >= mc_stdlib_testing_Log_Level_Error_e) {
    dprintf(g_fd, "ERROR:%s\n", p_msg);
  }
}


/*
 * Bridge:  Warning
 */
void
Log_Warning( c_t p_msg[ESCHER_SYS_MAX_STRING_LEN] )
{
  if(g_level >= mc_stdlib_testing_Log_Level_Warning_e) {
    dprintf(g_fd, "WARNING:%s\n", p_msg);
  }
}


/*
 * Bridge:  Notice
 */
void
Log_Notice( c_t p_msg[ESCHER_SYS_MAX_STRING_LEN] )
{
  if(g_level >= mc_stdlib_testing_Log_Level_Notice_e) {
    dprintf(g_fd, "NOTICE:%s\n", p_msg);
  }
}


/*
 * Bridge:  Info
 */
void
Log_Info( c_t p_msg[ESCHER_SYS_MAX_STRING_LEN] )
{
  if(g_level >= mc_stdlib_testing_Log_Level_Info_e) {
    dprintf(g_fd, "INFO:%s\n", p_msg);
  }
}


/*
 * Bridge:  Debug
 */
void
Log_Debug( c_t p_msg[ESCHER_SYS_MAX_STRING_LEN] )
{
  if(g_level >= mc_stdlib_testing_Log_Level_Debug_e) {
    dprintf(g_fd, "DEBUG:%s\n", p_msg);
  }
}

