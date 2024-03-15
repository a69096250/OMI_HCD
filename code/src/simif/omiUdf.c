/*
 *  File        : omiUdf.c 
 *  Date        : 2020/3/31
 *  Description : OMI User-defined function example
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omiDef.h"

#define FN_BYPASS   1
#define FN_NEG      2
#define FN_ADD      3
#define FN_MULT     4

// omiUDF API function
int omiUdf (double* output, const String strArg, const int numArgs, const double* args)
{
  int status = OMI_OK;
  double retVal = OMI_AUNDEF;

  omiPrint("String Arg: %s\n", strArg);

  if (numArgs == 0)
  {
    status = OMI_ERROR;
  }
  else
  {
    int userFunctionIndex = args[0];
    switch (userFunctionIndex)
    {
    // return arg
    case FN_BYPASS:
      if (numArgs >= 2)
      {
        retVal = args[1];
      }
      break;
    // return -1*arg
    case FN_NEG:
      if (numArgs >= 2)
      {
        retVal = -1*args[1];
      }
      break;
    // return arg1+arg2
    case FN_ADD:
      if (numArgs >= 3)
      {
        retVal = args[1]+args[2];
      }
      break;
    // return arg1*arg2
    case FN_MULT:
      if (numArgs >= 3)
      {
        retVal = args[1]*args[2];
      }
      break;
    default:
      status = OMI_ERROR;
      break;
    }
  }
  *output = retVal;
  
  omiPrint("Ret val: %f\n", retVal);
  if(retVal == OMI_AUNDEF)
    status = OMI_ERROR;
  
  return(status);
}

int omiFreeUdf(void)
{
  int status = OMI_OK;
  return(status);
}