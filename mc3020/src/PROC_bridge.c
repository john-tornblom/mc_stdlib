/*----------------------------------------------------------------------------
 * File:  PROC_bridge.c
 *
 * Description:
 * Methods for bridging to an external entity.
 *
 * External Entity:  Process_Control (PROC)
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
#include "PROC_bridge.h"
#include "mc_stdlib_testing_sys_types.h"

#include <stdlib.h>
#include <string.h>


/*
 * Global state for the external entity
 */
static char** g_argv = NULL;
static size_t g_argc = 0;


/*
 * Parse /proc/self/cmdline into the global state
 */
static void __attribute__((constructor))
parse_command_line() {
   FILE *cmdline = NULL;
   char *arg = NULL;
   size_t size = 0;
   
   // Figure out how many arguments there are
   cmdline = fopen("/proc/self/cmdline", "rb");
   while(getdelim(&arg, &size, 0, cmdline) != -1) {
      g_argc++;

   }
   free(arg);
   fclose(cmdline);

   // Allocate sufficient memory and read the data again
   g_argv = malloc(g_argc * sizeof(char*));
   g_argc = 0;
   arg = NULL;
   size = 0;
   cmdline = fopen("/proc/self/cmdline", "rb");
   while(getdelim(&arg, &size, 0, cmdline) != -1) {
      g_argv[g_argc] = malloc((size + 1) * sizeof(char));
      memcpy(g_argv[g_argc], arg, size);
      g_argv[g_argc][size] = 0;
      g_argc++;

   }
   free(arg);
   fclose(cmdline);
}


/*
 * Bridge:  Get_Env_Var
 */
c_t *
PROC_Get_Env_Var( c_t A0xtumlsret[ESCHER_SYS_MAX_STRING_LEN], c_t p_name[ESCHER_SYS_MAX_STRING_LEN] )
{
  char* value = getenv(p_name);

  if(value) {
    strncpy(A0xtumlsret, value, ESCHER_SYS_MAX_STRING_LEN);
  } else {
    A0xtumlsret[0] = '\0';
  }

  return A0xtumlsret;
}


/*
 * Bridge:  Get_Argument
 */
c_t *
PROC_Get_Argument( c_t A0xtumlsret[ESCHER_SYS_MAX_STRING_LEN], const i_t p_index )
{
  if(p_index < g_argc) {
    strncpy(A0xtumlsret, g_argv[p_index], ESCHER_SYS_MAX_STRING_LEN);
  } else {
    A0xtumlsret[0] = '\0';
  }

  return A0xtumlsret;
}


/*
 * Bridge:  Get_Argument_Count
 */
i_t
PROC_Get_Argument_Count()
{
  return g_argc;
}


/*
 * Bridge:  Exit
 */
void
PROC_Exit( const i_t p_status )
{
  exit(p_status);
}


/*
 * Bridge:  Set_Env_Var
 */
bool
PROC_Set_Env_Var( c_t p_name[ESCHER_SYS_MAX_STRING_LEN], c_t p_value[ESCHER_SYS_MAX_STRING_LEN] )
{
  return setenv(p_name, p_value, 1) == 0;
}


/*
 * Bridge:  Assert
 */
void
PROC_Assert( const bool p_cond, c_t p_msg[ESCHER_SYS_MAX_STRING_LEN] )
{
  if(!p_cond) {
    fprintf(stderr, "%s\n", p_msg);
    abort();
  }
}


/*
 * Bridge:  System
 */
i_t
PROC_System( c_t p_command[ESCHER_SYS_MAX_STRING_LEN] )
{
  return WEXITSTATUS(system(p_command));
}

